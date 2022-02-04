#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main( int argc, char *argv[] )  {
   if( argc == 2 ) {
      /* set the variables */
      int arg = atoi(argv[1]);
      double i;
      double b_0 = 0.00;
      pid_t pid = getpid();

      /* loop through the sequence and stop at the nth sum */
      for (i = 1; i <= arg; i++)
         b_0 = b_0 + 1/i;

      /* print the requested sum of the series */
      printf("[HarmonicSeries] [%d]: The sum of the first %d numbers of the Harmonic series is %f\n", pid, arg, b_0);
      
      /* return the sum */
      return b_0;
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
