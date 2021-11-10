#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
#include <readline/history.h> 

void signalHandler(int sig){
        if(sig==SIGINT){
                printf("this program will stop in 3 seconds..\n");
                sleep(3);
                exit(0);
        }
        
}

void signalHandler2(int sig)
{
        if(sig==SIGQUIT){
                printf("signal SIGQUIT\n");
        }
}

int main(){
        char *str;
        signal(SIGINT, signalHandler);
        signal(SIGQUIT, signalHandler2);
        while(1)
                str = readline(">");
        while(1);
}