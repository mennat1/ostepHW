/*1. Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to some-
thing (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?*/

#include<stdio.h>
#include<stdlib.h>	//exit
#include<unistd.h>	//fork
#include<sys/wait.h>

int main(int argc, char *argv[]){
	int x = 100;
	printf("Initial x = %d\n", x);
	int rc = fork();
	if(rc < 0){	//Fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rc == 0){ //Child process
		printf("Hello from the child process, PID = %d\n", (int) getpid());
		printf("Hello from the child process, x = %d\n", x);
		x = 200;
		printf("**Hello from the child process, new x = %d\n", x);
	}else{	//Parent process
		//wait(NULL);
		printf("Hello from the parent process, PID = %d\n", (int) getpid());
		printf("Hello from the parent process, x = %d\n", x);
		x = 400;
		printf("**Hello from the parent process, new x = %d\n", x);
	}
	printf("From %d, x = %d\n", (int) getpid(), x);
	return 0;
}
