#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char *argv[] )  {
   if( argc == 3 ) {
      /* initialize the variables */
      int arg = atoi(argv[2]);
      int i;
      int b_0 = 0;
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

      /* memory map the shared memory object */
      ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

      /* read from the shared memory object */
      /* printf("%s", (char*)ptr); */

      printf("[HexagonalSeries][%d]: The first %d numbers of the Lucas series are:\n", pid, arg);

      /* loop to the nth number and collect the sum */
      for (i = 1; i <= arg; i++) {
         b_0 = i*(2*i - 1);
         t = t + b_0;
         printf("%d ", b_0);
      }

      printf("\n");
  
      /* print the requested info */
      printf("[HexagonalSeries] [%d]: The sum of the first %d Hexagonal numbers is: %d\n", pid, arg, t);
      printf("[HexagonalSeries] [%d]: The nth number in the Hexagonal series is %d\n", pid, b_0);

      char nth_ptr[SIZE], tot_ptr[SIZE];
      sprintf(nth_ptr, "%d", b_0);
      sprintf(tot_ptr, "%d", t);
          
      /* return the requested info */
      if (t > 100) { 
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
