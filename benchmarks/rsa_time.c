#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void decimal_to_binary(int op1, int aOp[]){
    int result, i = 0;
    do{
        result = op1 % 2;
        op1 /= 2;
        aOp[i] = result;
        i++;
    }while(op1 > 0);
}

int modular_exponentiation(int a, int b, int n){
 int *bb;
 int count = 0, d = 1, i;
 struct timespec end, start;
 // find out the size of binary b
 count = (int) (log(b)/log(2)) + 1;
 
 bb = (int *) malloc(sizeof(int*) * count);
 decimal_to_binary(b, bb);
 
 for (i = count - 1; i >= 0; i--) {
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  d = (d*d) % n;
  if (bb[i] == 1) {
   d = (d*a) % n;
  }
 clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
 printf("bit %d loop time %ld\n", bb[i], delta_us);
 }
 return d;
}


int main(){
	int a = modular_exponentiation(123452,765435,93093587);
}
