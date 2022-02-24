#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char *argv[] )  {
   if( argc == 3 ) {
      /* set the variables */
      int arg = atoi(argv[2]);
      double i;
      double b_0 = 0.00, t = 0.00;
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

      printf("[HarmonicSeries][%d]: The first %d numbers of the Lucas series are:\n", pid, arg);

      /* loop through the sequence and stop at the nth sum */
      for (i = 2; i <= arg; i++) {
         b_0 += (double)1 / i;
         t = t + b_0;
         printf("%d ", b_0);
      }

      printf("\n");

      /* print the requested sum of the series */
      printf("[HarmonicSeries] [%d]: The sum of the first %d numbers of the Harmonic series is %f\n", pid, arg, b_0);
      
      char nth_ptr[SIZE];
      sprintf(nth_ptr, "%d", b_0);
          
      /* return the requested info */
      sprintf(ptr, "%s", nth_ptr);
      ptr += strlen(nth_ptr);
      return b_0;
   }
   else if( argc > 3 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
