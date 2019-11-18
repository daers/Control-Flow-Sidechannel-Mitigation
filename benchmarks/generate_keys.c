// Generate the data for the modular exponentiation file.
// TSV following the format m d p q.
// First line of file is the number of rows of data in the file.
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

int COUNT = 0;

long int gcd(long int a, long int b){
	if (b == 0)
      return a;
   return gcd(b, a % b);
}

long int lcm(long int a, long int b){
	return (a*b)/gcd(a, b);
}


// C function for extended Euclidean Algorithm
long int gcdExtended(long int a, long int b, long int *x, long int *y)
{
  // Base Case
  if (a == 0)
  {
	  *x = 0, *y = 1;
	  return b;
  }

  long int x1, y1; // To store results of recursive call
  long int gcd = gcdExtended(b%a, a, &x1, &y1);

  // Update x and y using results of recursive
  // call
  *x = y1 - (b/a) * x1;
  *y = x1;

  return gcd;
}

// Function to find modulo inverse of a
long int modInverse(long int a, long int m)
{
    long int x, y;
    long int g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        printf("Inverse doesn't exist");
    else
    {
        // m is added to handle negative x
        return (x%m + m) % m;
    }
}


int main(){
  FILE *fileptr;

  fileptr = fopen("modexp_data.txt", "w+");

  long int primes[32] = {314606891, 334214459, 817504253, 838041641, 334214467,353868013, 838041647, 858599503, 353868019, 373587883, 858599509, 879190747, 373587911, 393342739, 879190841, 899809343, 393342743, 413158511, 899809363, 920419813, 413158523, 433024223, 920419823, 941083981, 433024253, 452930459, 941083987, 961748927, 452930477, 472882027, 961748941, 982451653};
  long int values[4][1000];

  int countValues = 0;
  
  for (int i = 0; i < 1000; ++i){
    long int p = primes[rand() % 32];
    long int q = primes[rand() % 32];

    if(p == q){
      printf("P == Q. problem in iter %d. skipping\n", i);
      continue;
    }

    long int lamda = lcm(p-1, q-1);
    
    if (gcd(lamda, 65537) != 1){
      printf("You fucked up in iter %d", i);
    }

    long int m = rand();    
    long int d = modInverse(65537, lamda);
    
    values[0][countVals] = m;
    values[1][countVals] = d;
    values[2][countVals] = p;
    values[3][countVals] = q;

    ++countVals;
  }

  fprintf(fileptr, "%d\n", countVals);

  for (int i = 0; i < countVals; ++i){
    fprintf(fileptr, "%ld\t%ld\t%ld\t%ld\n", values[0][i], values[1][i], values[2][i], values[3][i]);
  }
  
  fclose(fileptr);

}
