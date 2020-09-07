/*7. Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?
*/

#include<stdio.h>
#include<stdlib.h>	//exit
#include<unistd.h>	//fork
#include<sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	int rc = fork();
	if(rc < 0){	//Fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rc == 0){ //Child process
		close(STDOUT_FILENO);
		int res = printf("Hello\n");
	    fprintf(stderr, "%d\n", res);
	    res = fflush(stdout);
	    /*This line will output -1 Bad file descriptor,
 		which shows that the attempt to write out to stdout failed, as expected. */
	    fprintf(stderr, "%d %s\n", res, strerror(errno));
	}else{	//Parent process
		wait(NULL);
	}
	return 0;
}

