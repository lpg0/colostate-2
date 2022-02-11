Generator.c: Runs the main function of the problem as descried in the homework. See comments in the code for full description.

Lucas.c: Runs the Lucas series calculation given the input value. See comments in the code for full description.

HexagonalSeries.c: Runs the Hexagonal series calculation given the input value. See comments in the code for full description.

HarmonicSeries.c: Runs the Harmonic series calculation given the input value. See comments in the code for full description.

Makefile: Runs make build to make four executables and cleans all of them.

Notes: After make, run ./generator README.txt to run the program.

richmond:~/hw2$ ./generator README.txt
[Generator] [3304922]: Waiting for the child process 3304923
[Lucas] [3304923]: The sum of the first 3 numbers of the Lucas series is 6
[Lucas] [3304923]: The nth number in the Lucas series is 3
[Generator] [3304922]: The child process 3304923 returned 6
[Generator] [3304922]: Waiting for the child process 3304924
[HexagonalSeries] [3304924]: The sum of the first 6 Hexagonal numbers is: 161
[HexagonalSeries] [3304924]: The nth number in the Hexagonal series is 66
[Generator] [3304922]: The child process 3304924 returned 6
[Generator] [3304922]: Waiting for the child process 3304925
[HarmonicSeries] [3304925]: The sum of the first 6 numbers of the Harmonic series is 2.450000
[Generator] [3304922]: The child process 3304925 returned 2
[Generator] [3304922]: The Lucas child process returned 6
[Generator] [3304922]: The Hexagonal child process is 6
[Generator] [3304922]: The sum of the first n Harmonic numbers is 2
[Generator] [3304922]: Waiting for the child process 3304926
[Lucas] [3304926]: The sum of the first 10 numbers of the Lucas series is 198
[Lucas] [3304926]: The nth number in the Lucas series is 76
[Generator] [3304922]: The child process 3304926 returned 10
[Generator] [3304922]: Waiting for the child process 3304927
[HexagonalSeries] [3304927]: The sum of the first 10 Hexagonal numbers is: 715
[HexagonalSeries] [3304927]: The nth number in the Hexagonal series is 190
[Generator] [3304922]: The child process 3304927 returned 10
[Generator] [3304922]: Waiting for the child process 3304928
[HarmonicSeries] [3304928]: The sum of the first 10 numbers of the Harmonic series is 2.928968
[Generator] [3304922]: The child process 3304928 returned 2
[Generator] [3304922]: The Lucas child process returned 10
[Generator] [3304922]: The Hexagonal child process is 10
[Generator] [3304922]: The sum of the first n Harmonic numbers is 2

1. What is the return value for the fork() in a child process?
   If correctly forked, it will return 0.
2. Give a reason for the fork() to fail?
   Maybe a process error, if there is a memory limit that restrains the number of processes able to be generated.
3. How many of the least significant bits of the status does WEXITSTATUS return?
   8.
4. Which header file must be included to use the WEXITSTATUS.
   sys/wait.h.
5. In this program, are we doing a sequential processing or a concurrent processing with respect to the child processes? Sequential processing is when only one of the child processes is running at one time, and concurrent processing is when more than one child process can be running at the same time.
   Sequential.
6. Is it possible to have any anomalies in the output from child process and the output from parent process. Provide a reason for that possible situation. (2 points)
   No, since it is sequential, we should be waiting for each process to finish before the next runs.
