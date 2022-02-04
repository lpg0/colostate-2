#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main( int argc, char *argv[] )  {
   if( argc == 2 ) {
      /* init variables */
      int arg = atoi(argv[1]) - 1;
      int a_0 = 2;
      int b_0 = 1;
      int tot = 0;
      int i = 0;
      int t = 0;
      pid_t pid = getpid();

      /* if only 1 return the first number */
      if (arg == 0)
         return a_0;

      /* loop through the sequence and add the total until you get to nth number */
      for (i = 2; i <= arg; i++)
      {
         tot = a_0 + b_0;
         a_0 = b_0;
         b_0 = tot;
         t += b_0;
      }

      /* add back the total from skipping the first two numbers and reset the arg for convenience */
      t += 3;
      arg += 1;

      /* print the requested info */
      printf("[Lucas] [%d]: The sum of the first %d numbers of the Lucas series is %d\n", pid, arg, t);
      printf("[Lucas] [%d]: The nth number in the Lucas series is %d\n", pid, b_0);
      
      /* return the requested info */
      if (t > 50) {
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
