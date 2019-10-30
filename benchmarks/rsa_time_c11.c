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


void dec_to_bin(int n, int bin[]) {
  int mask = (1 << 16);
  while (mask) {
      *bin++ = (mask & n) ? 1 : 0;
      mask >>= 1;
  }
}

void decimal_to_binary(int op1, int aOp[]){
    int i = 0;
    do {
        aOp[i++] = op1 % 2;
	op1 >>= 1;
    } while (op1);
}

int modular_exponentiation(int a, int b, int n){
  int *bb;
  int count = 0, d = 1, i;
  uint32_t start_hi = 0, start_lo = 0, end_hi = 0, end_lo = 0;
  // find out the size of binary b
  count = (int) (log(b)/log(2)) + 1;

  bb = (int*) malloc(sizeof(int) * count);
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
    printf("%d: %lu\n", bb[i], e);
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
  }
  return d;
}


int main(){
	int arr[16];
	int b = (1 << 10) - 1;
	dec_to_bin(b, arr);
	for (int i = 0; i < 16; ++i) {
	    printf("%d ", arr[i]);
	}
	printf("\n");
	int a = modular_exponentiation(7654351, 261632, 93093587);
	a = modular_exponentiation(987654351, 12345678, 93093587);

}
