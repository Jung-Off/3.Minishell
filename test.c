#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include "./libft/libft.h"
#include "dirent.h"
#include <sys/stat.h>


int main()
{
    int fd[2];

    pid_t pid = fork();
    pipe(fd);

    char **ls = {"ls", NULL};
    char **wc = {"wc", NULL};

    if (pid == 0)
    {
        // dup2(fd[0], STDIN_FILENO);
        // close(fd[0]);
        // close(fd[1]);
        execve("/bin/ls", ls, NULL);
    }
    else
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve("/usr/bin/wc", wc, NULL);
    }
   
}