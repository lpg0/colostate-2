#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main( int argc, char *argv[] )  {
   if( argc == 2 ) {
      int arg = atoi(argv[1]) - 1;
      int a_0 = 2;
      int b_0 = 1;
      int tot = 0;
      int i = 0;
      int t = 0;
      pid_t pid = getpid();

      if (arg == 0)
         return a_0;

      for (i = 2; i <= arg; i++)
      {
         tot = a_0 + b_0;
         a_0 = b_0;
         b_0 = tot;
         t += b_0;
      }
      t += 3;
      arg += 1;
      printf("[Lucas] [%d]: The sum of the first %d numbers of the Lucas series is %d\n", pid, arg, t);
      printf("[Lucas] [%d]: The nth number in the Lucas series is %d\n", pid, b_0);
      return b_0;
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
