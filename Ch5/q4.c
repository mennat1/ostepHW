/*4. Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?
*/



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
	int rc = fork();
	if(rc < 0){	//Fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	}else if(rc == 0){	//Child process
		//char *myargs[2];
		//myargs[0] = strdup("ls");	// program(the file being executed): ls (list)
		//myargs[1] = NULL;	// mark end of array
		char *myargs[] = {"ls", NULL};
		execvp(myargs[0], myargs); // runs ls
	}else{	//Parent process
		int rc_wait = wait(NULL);
	}
	return 0;
}
