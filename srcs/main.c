/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:00:58 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/04 11:51:42 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_print(t_cmd *cmd, char *line)
{
	int	i;

	printf("%s\n", line);
	printf("--------------------\n");
	i = 1;
	while (cmd)
	{
		printf("%d\n", i++);
		while (*cmd->argv)
			printf("[%s]\n", *cmd->argv++);
		printf("redirect\n");
		while (cmd->redirect)
		{
			printf("[%d %s]\n", cmd->redirect->type, cmd->redirect->file);
			cmd->redirect = cmd->redirect->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
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


void print_cmd(t_cmd *cmd)
{
	while(cmd)
	{
		printf("%s\n", *(cmd->argv));
		cmd = cmd->next;
	}
}

char *exe_parse(char **env, char *command_split)
{
	int i;
	char *env_path;
	//char *command_path;
	char *add_slash;

	struct stat buf;

	i = 0;
	while(env[i])
	{
		env_path = ft_strdup(env[i]);
		//free(env[i]); //>> 빨리 없애버리고 싶었으나 명령어가 안들어오면 free된 것이라고 함
		add_slash = ft_strjoin(env_path, "/");
		free(env_path);
		env_path = ft_strjoin(add_slash, command_split);

		//printf("env_path :%s\n", env_path);
		if(stat(env_path, &buf) == 0)
		{
			//printf("여기가 출력이 안되는데 함수가 실행이 되네?");
			//printf("%s", env_path);
			return (env_path);
		}
		++i;
	}
	printf("not invalid command\n");
	return (0);
}

int cmd_num(t_cmd *cmd)
{
	int i = 0;
	
	while(cmd)
	{
		cmd = cmd->next;
		++i;
	}
	return (i);
}

int exe_just(t_cmd *cmd_lst, char **env)
{
	char *env_path;
	int status;
	pid_t pid;
	static int i;

	env_path = exe_parse(env, cmd_lst->argv[0]);
	if (env_path == 0)
	{
		printf("명령어가 없어서 함수 나가는중\n");
		return (1);
	}

	pid = fork(); // 이함수 안쓰면 waitpid == -1 로 해서 error
		
	if (pid == 0)
	{
		// printf("pid %d", pid[i]);
		i++;	
		//printf(" --------자식\n");
			execve(env_path, cmd_lst->argv, NULL);
	}
	else
	{
		printf("pid %d", pid);
		waitpid(pid, &status, 0);
	}
	
	return (1);
}

void exe_multi(t_cmd *cmd, char **env)
{
	char *env_path;
	env_path = exe_parse(env, cmd->argv[0]);
	

	dup2(cmd->fd[1], 1);
	exe_just(cmd, env);

}

void exe_main(t_cmd *cmd, char **env)
{
	if (cmd->next == NULL)
	{
		exe_just(cmd, env);
		return ;
	}

	exe_multi(cmd, env);
	
}

int exit_function(char *line)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{	
		//printf("%s\n", line);
		free(line);
		exit (1);
	}
	return (0);
}

///////////////////////

void newline_function(int sig)
{
	if (sig == SIGINT) //신호 무시하기
	{
		//  printf("minishell-1.0$");
		write(STDOUT_FILENO, "\n", 1);
		 if (rl_on_new_line() == -1)
		 	exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
		//^c 이부분 제거하기
	}
}

void no_action(int sig)
{
	if(sig == SIGQUIT)
	{
		printf("minishell-1.0$   \b\b\b ");
		//^\이부부분 제거하기
		return;
	}
}
// 이런식으로 termcap을 이용해서 더 작성할 수 있다!

int	main(int argc, char **argv, char **envp)
{
	char	*line = "  ec\"ho\">>out -n< $USER \'$dfsdf \'$$123  | grep -r";
//	char	*line = "cat <<$USER";

	t_cmd	*cmd;
	char **env;

	(void)argc;
	(void)argv;
	cmd = NULL;

	env = find_envp_path();

	signal(SIGINT, newline_function);
	signal(SIGQUIT, no_action);
	while(1)
	{
		line = readline("minishell-1.0$ ");
		exit_function(line);
		if(line)
		{
			if (parse_line(&cmd, line, envp))
				return (EXIT_FAILURE);
			if (ft_strlen(line) > 0)
			{
				exe_main(cmd, env);
				add_history(line);
			}
		}
		free(line);
		line = NULL;
		cmd_clear(&cmd);
	}
	return (EXIT_SUCCESS);
}
