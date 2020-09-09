/*2. Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?
*/
//Undefined writing behavior. (Random execution)

#include<stdio.h>
#include<stdlib.h>	//exit
#include<unistd.h>	//fork
#include<sys/wait.h>
#include<fcntl.h> //open
#include <assert.h> 
#include <string.h>

int main(int argc, char *argv[]){
	int fd = open("./q2file", O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
	assert(fd > -1);
	int rc = fork();
	printf("PID = %d\n", (int) getpid());
	if(rc < 0){	//Fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rc == 0){ //Child process
		printf("Hello from the child process, PID = %d, fd = %d\n", (int) getpid(), fd);
		write(fd, "Hello1 from the child process\n", strlen("Hello1 from the child process\n"));
		write(fd, "Hello2 from the child process\n", strlen("Hello2 from the child process\n"));
	}else{	//Parent process
		//int rc_wait = wait(NULL);
		printf("Hello from the parent process, PID = %d, fd = %d\n", (int) getpid(), fd);
		write(fd, "Hello1 from the parent process\n", strlen("Hello1 from the parent process\n"));
		write(fd, "Hello2 from the parent process\n", strlen("Hello2 from the parent process\n"));

	}
	printf("From %d, Closing fd\n", (int) getpid());
	close(fd);
	return 0;
}
