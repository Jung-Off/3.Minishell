# include <unistd.h>
# include <stdlib.h> //getenv
# include <stdio.h> //readline
# include <signal.h> //signal, kill
# include <term.h> // tget~
# include <termios.h> // tcget~
# include <dirent.h> // ~dir
# include <sys/stat.h> // ~stat
# include <sys/wait.h>
# include <readline/readline.h>

void dup_fds(int fds[], int i)
{
	
	if (i == 1)
	{	
		dup2(fds[1], 1);
        // close(fds[5]);
        // close(fds[4]);
		close(fds[3]);
		close(fds[2]);
		close(fds[1]);
		close(fds[0]);
	}
	else if(i == 2)
	{
		dup2(fds[2], 0);
        // dup2(fds[3], 1);
		// close(fds[5]);
        // close(fds[4]);
		close(fds[3]);
		close(fds[2]);
		close(fds[1]);
		close(fds[0]);
	}
    // else
    // {
    //     dup2(fds[4], 0);
    //     close(fds[5]);
    //     close(fds[4]);
	// 	close(fds[3]);
	// 	close(fds[2]);
	// 	close(fds[1]);
	// 	close(fds[0]);
    // }
}

void pipe_link(int idx)
{
    int fds[4];

    int i = 0;
    while(i < 2)
    {
        pipe(&fds[i * 2]);
        ++i;
    }

    dup_fds(fds, idx);
}

void exe_command(char *argv, int i)
{
    pid_t pid;

    int status;

    char *ls[] = {"ls", NULL};
    char *pwd[] = {"pwd", NULL};
    // char *cat[] = {"cat", "test.txt", NULL};

    //printf("--------%d---------\n", i);
     pid = fork();
    if (pid == 0) 
    {
        //printf("--------brother %d---------\n", i);
        // if (i == 0)
        //     exit(0);
        pipe_link(i);
        if (i == 1)
        {
            execve("/bin/pwd", pwd, NULL);
            //execve("/bin/ls", ls, NULL);
        }
        if (i == 2)
        {   
            execve("/bin/ls", ls, NULL);
            //execve("/bin/pwd", pwd, NULL);
        }
        // if (i == 3)
        // {   
        //     execve("/bin/cat", cat, NULL);
        //     //execve("/bin/pwd", pwd, NULL);
        // }
    } 
    else if(pid > 0)
    {
        wait(&status);
        // printf("i m father %d\n", i);
        // ++i;
    }

}

int main(int ac, char *argv[])
{
    int i = 1;

    while(*argv)
    {
        //pipe_link();
        exe_command(*argv, i);
        argv++;
        
        //printf("number %d     %s\n", i, *argv);
        
        ++i;
    }
    return 0;
}
