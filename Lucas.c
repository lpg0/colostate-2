#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char *argv[] )  {
   if( argc == 3 ) {
      /* init variables */
      int arg = atoi(argv[2]) - 1;
      int a_0 = 2;
      int b_0 = 1;
      int tot = 0;
      int i = 0;
      int t = 0;
      pid_t pid = getpid();

      /* the size (in bytes) of shared memory object */
      const int SIZE = 32;
 
      /* name of the shared memory object */
      const char* NAME = argv[1];
 
      /* shared memory file descriptor */
      int shm_fd;
 
      /* pointer to shared memory object */
      void* ptr;

      /* open the shared memory object */
      shm_fd = shm_open(NAME, O_RDWR, 0666);
      ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

      printf("[Lucas][%d]: The first %d numbers of the Lucas series are:\n", pid, arg+1);
      printf("2 ");

      /* if only 1 return the first number */
      if (arg == 0) {
         printf("\n");
         return a_0;
      }

      printf("1 ");

      /* loop through the sequence and add the total until you get to nth number */
      for (i = 2; i <= arg; i++)
      {
         tot = a_0 + b_0;
         a_0 = b_0;
         b_0 = tot;
         t += b_0;
         printf("%d ", b_0);
      }

      printf("\n");

      /* add back the total from skipping the first two numbers and reset the arg for convenience */
      t += 3;
      arg += 1;

      /* print the requested info */
      printf("[Lucas] [%d]: The nth number in the Lucas series is: %d\n", pid, b_0);
      printf("[Lucas] [%d]: The sum of the first %d numbers of the Lucas series is: %d\n", pid, arg, t);

      char nth_ptr[SIZE], tot_ptr[SIZE];
      sprintf(nth_ptr, "%d", b_0);
      sprintf(tot_ptr, "%d", t);

      /* return the requested info */
      if (t > 50) {
         sprintf(ptr, "%s", nth_ptr);
         ptr += strlen(nth_ptr);
         return b_0;
      } else {
         sprintf(ptr, "%s", tot_ptr);
         ptr += strlen(tot_ptr);
         return t;
      }
   }
   else if( argc > 3 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
