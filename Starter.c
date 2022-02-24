#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#define WSIZE 10

int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      /* initialize the variables */
      char *fn = argv[1];
      FILE *fp = fopen(fn, "r");
      pid_t pid, pid_main;
      unsigned char buf[256];
      int i, status, ret1, ret2, ret3, p[2], pipe_ret;
      char *f_reader = "reader";
      char *f_lucas = "lucas";
      char *f_hexagonal = "hexagonal";
      char *f_harmonic = "harmonic";
      char *f_b;
      char f_buf[256], max_prime[256], pipe_wfd[256], pipe_tot[WSIZE];

      /* make sure the file opens */
      if (fp == NULL) {
         printf("[Generator]: File open error %s\n", fn);
         return 1;
      }

      /* make sure the pipe creates */
      if (pipe(p) < 0) {
         exit(1);
      }

      /* convert the pipe write end to char */
      sprintf(pipe_wfd, "%d", p[1]);

      char *pipe_args[] = {"reader", fn, pipe_wfd, NULL};
      pid = fork();
      if (pid == 0) {
         /* child: exec Reader.c */
         f_b = buf;
         execv(f_reader, pipe_args);
      } else {
         /* parent: wait for Reader.c */
         wait(&status);
      }
      close(p[1]);
      read(p[0], pipe_tot, WSIZE);
      close(p[1]);
      pipe_ret = atoi(pipe_tot);

      /* note: algorithm referenced from "https://www.w3resource.com/cpp-exercises/for-loop/cpp-for-loop-exercise-8.php" */
      int m, n, o = 0;
      for (n = pipe_ret - 1; n >= 1; n--) {
         for (m = 2; m < n; m++) {
            if (n % m == 0)
               o++;
         }
         if (o == 0) {
            if (n == 1) {
               printf("no prime number less than 2\n");
               break;
            }
            break;
         }
         o = 0;
      }
      sprintf(max_prime, "%d", n); 
 
      /* get the pid of the main process for printing */
      pid_main = getpid();

      printf("[Starter][%d]: Contents read from the read end pipe: %d\n", pid_main, pipe_ret);

      const int SIZE = 32;
      const char* LUCAS_NAME = "SHM_Lucas";
      
      int shm_fd;
      void* ptr;

      shm_fd = shm_open(LUCAS_NAME, O_CREAT | O_RDWR, 0666);
 
      ftruncate(shm_fd, SIZE);
       
      printf("[Starter][%d]: Created Shared memory %s with FD: %d\n", pid_main, LUCAS_NAME, shm_fd);      

      pid = fork();

      if (pid == 0) {
         /* child: exec Lucas.c */
         execlp(f_lucas, f_lucas, LUCAS_NAME, max_prime, NULL);
      } else {
         /* parent: wait for Lucas.c */
         wait(&status);
         if (WIFEXITED(status)) {
            printf("[Starter] [%d]: Lucas last number: %d\n", pid_main, WEXITSTATUS(status));
            ret1 = WEXITSTATUS(status);
            sprintf(f_buf, "%d", WEXITSTATUS(status));
         }
      }

      ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
      printf("[Starter] [%d]: Lucas last number: %s\n", pid_main, (char*)ptr);
      shm_unlink(LUCAS_NAME);

      return(0);

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
               ret1 = WEXITSTATUS(status);
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
               ret2 = WEXITSTATUS(status);
               sprintf(f_buf, "%d", WEXITSTATUS(status));
            }
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
