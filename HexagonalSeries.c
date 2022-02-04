#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )  {
   if( argc == 2 ) {
      int arg = atoi(argv[1]);
      int i;
      int b_0 = 0;
      int t = 0;

      for (i = 1; i <= arg; i++) {
         b_0 = i*(2*i - 1);
         t = t + b_0;
      }

      printf("[HexagonalSeries] [pid]: The sum of the first %d Hexagonal numbers is: %d\n", arg, t);
      printf("[HexagonalSeries] [pid]: The nth number in the Hexagonal series is %d\n", b_0);

      return b_0;
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
