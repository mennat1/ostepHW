/*8. Write a program that creates two children, and connects the stan-
dard output of one to the standard input of the other, using the
pipe() system call.
*/

/*The pipe system call is: int pipe(int fds[2]);
	Parameters :
	fd[0] will be the fd(file descriptor) for the 
	read end of pipe.
	fd[1] will be the fd for the write end of pipe.
	Returns :	 0 on Success.
				-1 on error.
	After the pipe system call executes, the array fds[2] contains two file descriptors, 
	fds[0] is for reading from the pipe and fds[1] is for writing to the pipe.
	So, if the pipe is being used for reading, the write file descriptor is closed, and vice-versa.
	Using the respective file descriptor, one can use the read or write system call for 
	reading from or writing to a pipe just like a file.
*/

/*fork(): On  success,  the  PID  of  the  child process is returned in the parent,
 and 0 is returned in the child
 In fork() the total process created is = 2^number of fork().*/


#include<stdio.h>
#include<stdlib.h>	//exit
#include<unistd.h>	//fork
#include<sys/wait.h>
#include<string.h>

int main(int argc, char *argv[]){
	char buffer;
	int pipefd[2];
	int nBytes;
	pid_t rc1, rc2;

	if (pipe(pipefd) == -1){
	    perror("pipe");
	    exit(1);
  	}

  	rc1 = fork();//First fork 

  	if(rc1 < 0){
  		fprintf(stderr, "fork failed\n");
    	exit(EXIT_FAILURE);
  	}else if(rc1 == 0){//Child 1 writes to the pipe
  		printf("1st child writes to the pipe, pid = %d, rc1 = %d, rc2 = %d\n", (int)getpid(), rc1, rc2);
	    close(pipefd[0]); /* Close unused read end */
	    write(pipefd[1], "Hellooooooo!\n", strlen("Hellooooooo!\n"));
		close(pipefd[1]);//To detect EOF
		
  	}else{
  		waitpid(rc1, NULL, 0);
  		rc2 = fork();//Second fork
  		if(rc2 < 0){
	  		fprintf(stderr, "fork failed\n");
	    	exit(EXIT_FAILURE);
  		}else if(rc2 == 0){
			printf("2nd child reading from pipe and writing to STDOUT, pid = %d, rc1 = %d, rc2 = %d\n", (int)getpid(), rc1, rc2);
			close(pipefd[1]);	//Close unused write end
			while((nBytes = read(pipefd[0], &buffer, 1)) > 0){	//Read byte by byte
	    		write(STDOUT_FILENO, &buffer, 1);
	  		}
	  		if(nBytes != 0){
	  			exit(2);
	  		}
	  		write(STDOUT_FILENO, "\n", 1);
	  		close(pipefd[0]);
	  	}
  	}

 }
