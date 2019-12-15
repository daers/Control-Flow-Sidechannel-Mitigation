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
#include "stats_counter.h"


#pragma intrinsic(__rdtscp)

float STATS[2][1000];

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
  long int count = 64, d = 1, i;
  // Declare and initialize a stats_counter object for bookeeping.
  // struct stats_counter sc; SC_init(&sc);
  bb = (long int*) malloc(sizeof(long int) * count);
  decimal_to_binary(b, bb);

  for (i = count - 1; i >= 0; i--) {
    d = (d * d) % n;
    if (bb[i] == 1) {
        a = (d * a) % n;
    } else {
        d = d;
    }
  }
  return a;
}


int main(){
  int tempChar;
  FILE* fileptr = fopen("modexp_data.txt", "r");
  if (!fileptr) {
  	printf("Failed to open file. exiting with error.\n");
	exit(1);
  }
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

  fclose(fileptr);
}
