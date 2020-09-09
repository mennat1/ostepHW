/*5. Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?
*/


/*wait() returns process ID of the terminated child process.
If more than one child processes are terminated than wait() reap any arbitrarily child 
and return a process ID of that child process.
When wait() returns they also define exit status (which tells our, a process why terminated) 
via pointer, If status are not NULL.
If any process has no child process then wait() returns immediately “-1”.*/

#include<stdio.h>
#include<stdlib.h>	//exit
#include<unistd.h>	//fork
#include<sys/wait.h>

int main(int argc, char *argv[]){
	int rc = fork();
	if(rc < 0){	//Fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rc == 0){ //Child process
		//wait(NULL);
		printf("Hello\n");
	}else{	//Parent process
		wait(NULL);
		printf("Goodbye\n");
	}
	return 0;
}
