// Need for clock_gettime()
// Have to be at the begining of the file
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <x86intrin.h>

#pragma intrinsic(__rdtscp)

float STATS[2][1000];
int COUNT = 0;

// Use the preprocessor so we know definitively that these are placed inline
#define RDTSC_START()            \
	__asm__ volatile("CPUID\n\t" \
	                 "RDTSC\n\t" \
	                 "mov %%edx, %0\n\t" \
	                 "mov %%eax, %1\n\t" \
	                 : "=r" (start_hi), "=r" (start_lo) \
	                 :: "%rax", "%rbx", "%rcx", "%rdx");

#define RDTSC_STOP()              \
	__asm__ volatile("RDTSCP\n\t" \
	                 "mov %%edx, %0\n\t" \
	                 "mov %%eax, %1\n\t" \
	                 "CPUID\n\t" \
	                 : "=r" (end_hi), "=r" (end_lo) \
	                 :: "%rax", "%rbx", "%rcx", "%rdx");

// Returns the elapsed time given the high and low bits of the start and stop time.
uint64_t elapsed(uint32_t start_hi, uint32_t start_lo,
                 uint32_t end_hi,   uint32_t end_lo) {
	uint64_t start = (((uint64_t)start_hi) << 32) | start_lo;
	uint64_t end   = (((uint64_t)end_hi)   << 32) | end_lo;
	return end - start;
}

void decimal_to_binary(long int op1, long int aOp[]){
    int i = 0;
    do {
        aOp[i++] = op1 % 2;
	op1 >>= 1;
    } while (op1);
}

long int modular_exponentiation(long int a, long int b, long int n){
  long int *bb;
  long int count = 0, d = 1, i;
  uint32_t start_hi = 0, start_lo = 0, end_hi = 0, end_lo = 0;
  // find out the size of binary b
  count = 64;

  bb = (long int*) malloc(sizeof(long int) * count);
  decimal_to_binary(b, bb);

  long times[2][count];
  for (int i = 0; i < 2; ++i) {
  	for (int j = 0; j < count; ++j) {
		times[i][j] = 0;
	}
  }

  uint64_t s, e;
  unsigned null;
  for (i = count - 1; i >= 0; i--) {
    RDTSC_START();
    d = (d * d) % n;
    if (bb[i]) {
      d = (d * a) % n;
    }
    RDTSC_STOP();
    uint64_t e = elapsed(start_hi, start_lo, end_hi, end_lo);
    //printf("%ld: %lu\n", bb[i], e);
    times[bb[i]][i] = e;
  }

  long total = 0;
  int bits = 0;
  float avgs[2], vars[2];
  for (int j = 0; j < 2; ++j) {
    bits = 0, total = 0;
    for (int i = 0; i < count; ++i) {
  	  if (times[j][i]) {
		  ++bits;
	  	  total += times[j][i];
	  }
    }
    float avg = (float)total / (float)bits;
    avgs[j] = avg;
  }
  for (int j = 0; j < 2; ++j) {
    vars[j] = 0;
    bits = 0;
    for (int i = 0; i < count; ++i) {
  	  if (times[j][i]) {
	  	float diff = (float)times[j][i] - avgs[j];
		vars[j] += (diff * diff);
	  	++bits;
	  }
    }
    vars[j] /= (float)bits;
  }
  for (int j = 0; j < 2; ++j) {
  	printf("avg. timing for %d-bit: %f, std. dev: %f\n", j, avgs[j], sqrt(vars[j]));
	STATS[j][COUNT] = avgs[j];
  }
  COUNT++;
  return d;
}


int main(){
  FILE *fileptr;
  int tempChar;
  fileptr = fopen("modexp_data.txt", "r");
  long int d, m, p, q;
  // long int values[4][1000];

	for (int i = 0; i < 1000; ++i){
    // Read m, d, p, q from file
		fscanf(fileptr, "%ld", &d);
    fscanf(fileptr, "%ld", &m);
    fscanf(fileptr, "%ld", &p);
		fscanf(fileptr, "%ld", &q);

		long int a = modular_exponentiation(m, d, p * q);
	}

	printf("\n\nPRINTING OVERALL STATS");
	printf("\n\nAverage difference between 0 bit and 1 bit\n");
	for (int i = 0; i < COUNT; ++i) {
    printf("%f\n", STATS[1][i] - STATS[0][i]);
  }

  fclose(fileptr);
}
