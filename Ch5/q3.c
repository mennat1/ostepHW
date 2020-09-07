/*Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?
*/

/*if the process that calls wait() has no child processes to wait for,
then it immediately returns -1, indicating an error. In that event, errno will be set to ECHILD.*/

/*Yes, you can using signals*/

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
		printf("Hello1\n");
		printf("Hello2\n");
	}else{	//Parent process
		//wait(NULL);
		printf("Goodbye1\n");
		printf("Goodbye2\n");
	}
	return 0;
}
