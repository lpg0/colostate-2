#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      char *fn = argv[1];
      FILE *fp = fopen(fn, "r");
      pid_t pid, pid_main, pid_wait;
      unsigned char buf[256];
      int i;
      int ret;

      if (fp == NULL)
      {
         printf("[Generator]: File open error %s\n", fn);
         return 1;
      }

      pid_main = getpid();

      while (fgets(buf, (unsigned) 256, fp)) {
         printf("[Generator] [%d]: %s\n", pid_main, buf);
         /* fork: make child to run Lucas.c */
         pid = fork();
         if (pid == 0) {
            /* child: exec Lucas.c */
         } else {
            /* parent: wait for Lucas.c */
            printf("[Generator] [%d]: Waiting for the child process %d\n", pid_main, pid);
            pid_wait = waitpid(pid, &status);
            if (WIFEXITED(ret)) {
               printf("[Generator] [%d]: Lucas exited, status %d\n", pid_main, WEXITSTATUS(ret));
            }
         }
         /* fork: make child to run HexagonalSeries.c */
         pid = fork();
         if (pid = 0) {
            /* child: exec HexagonalSeries.c */
         } else {
            /* parent: wait for HexagonalSeries.c */
            printf("[Generator] [%d]: Waiting for the child process %d", pid_main, pid);
         }
         /* fork: make child to run HarmonicSeries.c */
         pid = fork();
         if (pid == 0) {
            /* child: exec HarmonicSeries.c */
         } else {
            /* parent: wait for HarmonicSeries.c */
            printf("[Generator] [%d]: Waiting for the child process %d", pid_main, pid);
         }
         /* loop for every line */
      }

      fclose(fp);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
