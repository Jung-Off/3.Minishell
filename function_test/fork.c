#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
 #include <fcntl.h>

int main() {

    int fd[2];
    pipe(fd);
		write(fd[1], "hello", 6);
		dup2(fd[1], 1);
		// exe_just(cmd, env);
	char * str = NULL;
			open(fd[1], str, strlen(str));
		write(1, str, strlen(str));
     
    return 0;
}