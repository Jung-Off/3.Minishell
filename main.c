#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include "./libft/libft.h"

void welcome_text(void)
{
	printf("\nThis is Minishell welcome\n");
}

char	**find_envp_path()
{
	char	**envp_path;
	char 	*path;

   	path = getenv("PATH");
	if(path == NULL)
		printf("Failed to get path\n");
	envp_path = ft_split(path, ':');

	return (envp_path);
}

void echo_f(char *command)
{
	int i = 0;

	while(i++ < 5)
		command++;

	printf("%s", command);
}

void exe_command(char *command, char **env)
{
	
}

void exe(char *command, char **env)
{
	// if (ft_strnstr(command, "echo", 4))
	// 	echo_f(command);
	// else if(ft_strnstr(command, "exit", 4))
	// {
	// 	printf("exit\n");
	// 	exit(0);
	// }

	
	//구현 안해도 되는 것들 수행하기 위함
	exe_command(command, env);
}

int main()
{
	char **env;	
	char *command;

	welcome_text();
	env = find_envp_path();
	//환경 변수 완료

	while(1)
	{
		command = readline("minishell-1.0$ ");

		//ctrl + c 를 누르면 새로운 행이 만들어지도록 어떻게 만들가
		if (command)
			exe(command, env);
		add_history(command);

		//env free;
		free(command);
	}
	return 0;
}
