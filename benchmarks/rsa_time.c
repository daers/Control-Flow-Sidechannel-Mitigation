#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <chrono>

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
 using namespace std::chrono;
 // find out the size of binary b
 count = (int) (log(b)/log(2)) + 1;

 bb = (int*) malloc(sizeof(int) * count);
 decimal_to_binary(b, bb);

 high_resolution_clock::time_point t1, t2; // = high_resolution_clock::now(); 

 for (i = count - 1; i >= 0; i--) {
   if (bb[i] == 1) {
     t1 = high_resolution_clock::now();
     d = (d * a);
     t2 = high_resolution_clock::now();
   } else {
     t1 = high_resolution_clock::now();
     d = (d * d);
     t2 = high_resolution_clock::now();
   }
   duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
   std::cout << "bb[i] = " << bb[i] << ", chrono: " << time_span.count() << "\n";
   d %= n;
 }
 return d;
}


int main(){
	int a = modular_exponentiation(7654351, 65280, 93093587);
}
