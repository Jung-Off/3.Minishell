#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "./libft/libft.h"



void echo_f(char *command)
{
	int i = 0;

	while(i++ < 5)
		command++;

	printf("%s", command);
}

void exe(char *command, char **env)
{
	if (ft_strnstr(command, "echo", 4))
		echo_f(command);
	else if(ft_strnstr(command, "exit", 4))
	{
		printf("exit\n");
		exit(0);
	}

	//exe_command(command);
}

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);

}

char **init_env(int ac, char **argv, char **envp)
{
	char **env_tmp;

	int i = 0;
	(void)ac;

	while(envp[i])
	{
		if(ft_strnstr(envp[i], "PATH=", 5))
		{
			env_tmp = ft_split(&envp[i][5], ':');
		}
	}
	return (env_tmp);
}

int main(int ac, char *argv[], char **envp)
{

	
	char *command;
	char **env;

	
	printf("fdafdsafs");
	env = init_env(ac, argv, envp);


	int i = 0;
	while(env[i])
	{
		printf("%s", env[i++]);
	}


	return (0);
}
