#define _GNU_SOURCE
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h> //read
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#define MILLION 1000000

/*int sched_setaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
A process's CPU affinity mask determines the set of CPUs on which it is eligible to run.
sched_setaffinity() sets the CPU affinity mask of the process whose ID is pid to the value
specified by mask. If pid is zero, then the calling process is used. 
The argument cpusetsize is the length (in bytes) of the data pointed to by mask.
Normally this argument would be specified as sizeof(cpu_set_t).
On success, sched_setaffinity() return 0. On error, -1 is returned*/

int main(int argc, char *argv[]){
	//Measure System call 
	 int fd = open("./1.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	 struct timeval start, end;
	 int nloops = MILLION;
	 long total_us = 0, syscall_us = 0;
	 double avg_us = 0;
	 for(int i = 0; i < nloops; i++){
	 	gettimeofday(&start, NULL);
	 	read(fd, NULL, 0);
	 	gettimeofday(&end, NULL);
	 	//printf("end.tv_sec = %lo, end.tv_usec = %lo\nstart.tv_sec = %lo, start.tv_usec = %lo\n", end.tv_sec,end.tv_usec, start.tv_sec, start.tv_usec);
	 	//sc_us = (((end.tv_sec * MILLION) + end.tv_usec) - ((start.tv_sec * MILLION) + start.tv_usec));
	 	syscall_us = MILLION * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
	 	//printf("syscall_us= %lo\n", syscall_us);
	 	total_us += syscall_us;
	 	//printf("total_us = %lo\n", total_us);
	 }
	 avg_us = (double)total_us/nloops;
	 printf("Avg time for a system call = %f microseconds\n", avg_us);
	 printf("*****************\n");
	 //Measure context switch
	 cpu_set_t set;
	 CPU_ZERO(&set);
	 CPU_SET(0, &set);

	 double ctxtswitch_us = 0;
	 int pipe1[2];
	 int pipe2[2];

	 if (pipe(pipe1) == -1){
	    perror("pipe");
	    exit(1);
  	}
  	if (pipe(pipe2) == -1){
	    perror("pipe");
	    exit(1);
  	}

	 int rv = fork();
	 if(rv < 0){//Fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rv == 0){//Child process reads from pipe1 and writes to pipe2
		//printf("Child process\n");
		if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(EXIT_FAILURE);
        }
		for(int i = 0; i < nloops; i++){
			//Read from pipe1
			//close(pipe1[1]);
			read(pipe1[0], NULL, 0);

			//Write to pipe2
			//close(pipe2[0]);
			write(pipe2[1], NULL, 0);
		}
	}else if(rv > 0){//Parent process writes to pipe1 and reads from pipe2
		//printf("Parent process\n");
		if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(EXIT_FAILURE);
        }

		gettimeofday(&start, NULL);
		for (int i = 0; i < nloops; i++){
			//Write to pipe1
			//close(pipe1[0]);
			write(pipe1[1], NULL, 0);

			//Read from pipe2
			//close(pipe2[1]);
			read(pipe2[0], NULL, 0);
		}
		gettimeofday(&end, NULL);
		ctxtswitch_us = (double)(MILLION * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)) / nloops;
		printf("Avg time for a context switch= %f microseconds\n", ctxtswitch_us);
	}
	

}