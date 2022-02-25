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
      double b_0 = 1.00, t = 0.00;
      pid_t pid = getpid();

      /* the size (in bytes) of shared memory object */
      const int SIZE = 32;

      /* name of the shared memory object */
      const char* NAME = argv[1];

      /* shared memory file descriptor */
      int shm_fd;
      void* ptr;

      shm_fd = shm_open(NAME, O_RDWR, 0666);
      ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

      printf("[HarmonicSeries][%d]: The first %d numbers of the Harmonic series are:\n", pid, arg);

      /* loop through the sequence and stop at the nth sum */
      printf("%f ", b_0);
      double k;
      for (i = 2; i <= arg; i++) {
         k = (double)1 / i;
         b_0 = b_0 + k;
         printf("%f ", k);
      }

      printf("\n");

      /* print the requested sum of the series */
      printf("[HarmonicSeries] [%d]: The %dth value in the Harmonic series: %f\n", pid, arg, k);
      printf("[HarmonicSeries] [%d]: The sum of the first %d numbers of the Harmonic series is %f\n", pid, arg, b_0);
      
      char nth_ptr[SIZE];
      sprintf(nth_ptr, "%f", b_0);
          
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
