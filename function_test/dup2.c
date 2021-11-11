#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

# include <readline/readline.h>
#include <readline/history.h>

int main()
{
    int fd[2];
    int status;
    char *ls[] = {"ls", NULL};
    char *grep[] = {"grep", "a", NULL};
    int child[2];

// execve("/bin/ls", ls, NULL);
    int i = 0;
    pipe(fd);

    int out = dup(STDOUT_FILENO);
    int in = dup(STDIN_FILENO);
    while(1)
    {
        char *str = readline(">");
        child[i] = fork();
        if(child[i] == 0)
        {
            if (i == 0)
            {
                dup2(fd[1], 1);
                execve("/bin/ls", ls, NULL);
            }     
            if (i == 1)
            {
                dup2(fd[0], 0);
                dup2(out, 1);
                execve("/usr/bin/grep", grep, NULL);
            }
            dup2(in, 0);
            
        }
        else
            waitpid(child[i], &status, 0);
        i++;
    }
}