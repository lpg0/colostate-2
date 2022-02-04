#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main( int argc, char *argv[] )  {
   if( argc == 2 ) {
      /* initialize the variables */
      int arg = atoi(argv[1]);
      int i;
      int b_0 = 0;
      int t = 0;
      pid_t pid = getpid();

      /* loop to the nth number and collect the sum */
      for (i = 1; i <= arg; i++) {
         b_0 = i*(2*i - 1);
         t = t + b_0;
      }
  
      /* print the requested info */
      printf("[HexagonalSeries] [%d]: The sum of the first %d Hexagonal numbers is: %d\n", pid, arg, t);
      printf("[HexagonalSeries] [%d]: The nth number in the Hexagonal series is %d\n", pid, b_0);

      /* return the requested info */
      if (b_0 > 100) {
         return arg;
      } else {
         return t;
      }
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
