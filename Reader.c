#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WSIZE 16

int main( int argc, char *argv[] )  {

   if( argc == 3 ) {
      /* initialize the variables */
      char *fn = argv[1];
      char *pipe_wfd = argv[2];
      FILE *fp = fopen(fn, "r");
      unsigned char buf[256];
      int cur, tot, pipe_ref;
      char pipe_tot[WSIZE]; 
      
      /* copy the pipe ref into int */
      pipe_ref = atoi(pipe_wfd);

      /* make sure the file opens */
      if (fp == NULL)
      {
         printf("[Generator]: File open error %s\n", fn);
         return 1;
      }

      /* loop through the lines of the file */
      while (fgets(buf, (unsigned) 256, fp)) {
         cur = atoi(buf);
         tot = tot + cur;
      }
      
      /* convert int to char total */
      sprintf(pipe_tot, "%d", tot);

      /* write to the pipe */
      write(pipe_ref, pipe_tot, WSIZE);

      /* test output */
      /* printf("total: %s, pipe ref: %d\n", pipe_tot, pipe_ref); */
   }
   else if( argc > 3 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("Two arguments expected.\n");
   }
}
