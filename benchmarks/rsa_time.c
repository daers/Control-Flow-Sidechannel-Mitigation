#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
 double delta_us;
 clock_t start, end;
 // find out the size of binary b
 count = (int) (log(b)/log(2)) + 1;

 bb = (int ) malloc(sizeof(int) * count);
 decimal_to_binary(b, bb);

 for (i = count - 1; i >= 0; i--) {
  start = clock();
  d = (d*d) % n;
  if (bb[i] == 1) {
   d = (d*a) % n;
  }
 end = clock();
 delta_us = (((double)end - (double)start) / (double)CLOCKS_PER_SEC);
 printf("bit %d loop time %f\n", bb[i], delta_us);
 }
 return d;
}


int main(){
	int a = modular_exponentiation(123452,765435,93093587);
}