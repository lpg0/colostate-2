#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      /* initialize the variables */
      char *fn = argv[1];
      FILE *fp = fopen(fn, "r");
      pid_t pid, pid_main;
      unsigned char buf[256];
      int i, status;
      char *f_lucas = "lucas";
      char *f_hexagonal = "hexagonal";
      char *f_harmonic = "harmonic";
      char *f_b;
      char f_buf[256];
      
      /* make sure the file opens */
      if (fp == NULL)
      {
         printf("[Generator]: File open error %s\n", fn);
         return 1;
      }

      /* get the pid of the main process for printing */
      pid_main = getpid();

      /* loop through the lines of the file */
      while (fgets(buf, (unsigned) 256, fp)) {
         /* fork: make child to run Lucas.c */
         pid = fork();
         if (pid == 0) {
            /* child: exec Lucas.c */
            f_b = buf;
            execlp(f_lucas, f_lucas, f_b, NULL);
         } else {
            /* parent: wait for Lucas.c */
            printf("[Generator] [%d]: Waiting for the child process %d\n", pid_main, pid);
            wait(&status);
            if (WIFEXITED(status)) {
               printf("[Generator] [%d]: The child process %d returned %d\n", pid_main, pid, WEXITSTATUS(status));
               sprintf(f_buf, "%d", WEXITSTATUS(status));
            }
         }
         /* fork: make child to run HexagonalSeries.c */
         pid = fork();
         if (pid == 0) {
            /* child: exec HexagonalSeries.c */
            execlp(f_hexagonal, f_hexagonal, f_buf, NULL);
         } else {
            /* parent: wait for HexagonalSeries.c */
            printf("[Generator] [%d]: Waiting for the child process %d\n", pid_main, pid);
            wait(&status);
            if (WIFEXITED(status)) {
               printf("[Generator] [%d]: The child process %d returned %d\n", pid_main, pid, WEXITSTATUS(status));         
               sprintf(f_buf, "%d", WEXITSTATUS(status));
            }
         }
         /* fork: make child to run HarmonicSeries.c */
         pid = fork();
         if (pid == 0) {
            /* child: exec HarmonicSeries.c */
            execlp(f_harmonic, f_harmonic, f_buf, NULL);
         } else {
            /* parent: wait for HarmonicSeries.c */
            printf("[Generator] [%d]: Waiting for the child process %d\n", pid_main, pid);
            wait(&status);
            if (WIFEXITED(status)) {
               printf("[Generator] [%d]: The child process %d returned %d\n", pid_main, pid, WEXITSTATUS(status));
               sprintf(f_buf, "%d", WEXITSTATUS(status));
            }
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
