/*6. Write a slight modification of the previous program, this time us-
ing waitpid() instead of wait(). When would waitpid() be
useful?
*/

/*Either of wait or waitpid can be used to remove zombies(a process that has terminated,
but whose parent has not yet waited for it)
wait (and waitpid in it's blocking form) temporarily suspends the execution of a parent process
while a child process is running. Once the child has finished, the waiting parent is restarted.
*/

/*We know if more than one child processes are terminated,
then wait() reaps any arbitrarily child process but if we want to reap any specific child process, 
we use waitpid() function.*/

/*pid_t wait(int *statloc); returns process ID if OK, or -1 on error 

  pid_t waitpid(pid_t pid, int *statloc, int options);
    		returns process ID : if OK,
             0         : if non-blocking option && no zombies around
            -1        : on error
    
*/

/*waitpid can be either blocking or non-blocking:
If options is 0, then it is blocking
If options is WNOHANG, then is it non-blocking*/

/*waitpid is more flexible:
If pid == -1, it waits for any child process. In this respect, waitpid is equivalent to wait
If pid > 0, it waits for the child whose process ID equals pid
If pid == 0, it waits for any child whose process group ID equals that of the calling process
If pid < -1, it waits for any child whose process group ID equals that absolute value of pid
*/

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
		waitpid(-1, NULL, 0);
		printf("Goodbye\n");
	}
	return 0;
}
