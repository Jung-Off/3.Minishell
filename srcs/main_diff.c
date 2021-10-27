
#include "../includes/minishell.h"

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

int exe_just(t_cmd_lst *cmd_lst, char **env)
{
	char *env_path;
	int status;
	pid_t pid;

	env_path = exe_parse(env, cmd_lst->cmd[0]);
	//printf("%s", env_path);
	if (env_path == 0)
	{
		printf("명령어가 없어서 함수 나가는중\n");
		return (1);
	}

	pid = fork(); // 이함수 안쓰면 waitpid == -1 로 해서 error
	if (pid == 0)
	{
		//printf(" --------자식\n");
			execve(env_path, cmd_lst->cmd, NULL);
	}
	else
	{
		pid_t waitpid;

		waitpid = wait(&status);
		//printf("==========부모\n");
		if (waitpid == - 1)
		{
			printf("Error");
		}
		else
		{
			if (WIFEXITED(status)) //자식이 정상적으로 종료 되었다면
			{
			//printf("wait : 자식 프로세스 정상종료 %d\n", WEXITSTATUS(status)); 
			//정상종료 WIFEXITED일때만 exit()를 호출하기 위한 인자나 return 값이 설정되고 종료된 자식의 반환코드의 최하위 8비트를 평가한다.
			}
			else if (WIFSIGNALED(status)) //자식 프로세스가 어떤 신호 때문에 종료 되었다면 참				{
			{
			//printf("wait : 자식 프로세스 비정상 종료 %d\n", WTERMSIG(status)); // 자식 프로세스를 종료하도록 한 신호의 번호를 반환
			}
		}
	}	
	return (1);
}


//////////////////////////

void open_fd(t_cmd_lst *cmd_lst, int idx, int cnt)
{
	// pipe(cmd_lst->fd);
	// if (idx < cnt)
	// 	pipe(cmd_lst->next->fd);

	//다음파이프도 만들어주어야하는것 아닌가

	if (idx < cnt)
		dup2(cmd_lst->fd[0], 0);
	// if (idx > 0)
		// dup2 (cmd_lst->next->fd[1], 1);
}

void close_fd(t_cmd_lst *cmd_lst)
{
	close(cmd_lst->fd[0]);
	close(cmd_lst->fd[1]);

	// close(cmd_lst->next->fd[0]);
	// close(cmd_lst->next->fd[1]);
}

int count_cmd(t_cmd_lst *cmd_lst)
{
	int i;

	i = 0;
	while(cmd_lst)
	{
		++i;
		cmd_lst = cmd_lst->next;
	}
	return (i);
}

void exe_pipe(t_cmd_lst *cmd_lst, char **env)
{
	char *env_path;
	int status;
	pid_t pid;

	env_path = exe_parse(env, cmd_lst->cmd[0]);
	//printf("%s", env_path);
	if (env_path == 0)
	{
		printf("명령어가 없어서 함수 나가는중\n");
		return ;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(env_path, cmd_lst->cmd, NULL);
	}
	else
	{
		pid_t waitpid;
		waitpid = wait(&status);
	}
}

void exe_main(t_cmd_lst *cmd_lst, char **env)
{
	int idx = 0;
	int cnt;

	// cnt = count_cmd(cmd_lst);

	if (cmd_lst->next == NULL)
	{	
		exe_just(cmd_lst, env);
		return ;	
	}
	// while (cmd_lst)
	// {
		// pid_t pid = fork();
		int fd_input = 0;
		int fd_output = 0;
		int prev_fd;

		// dup2(fd_input, 0);
		fd_output = dup(1);
		fd_input = dup(0);
	
		pipe(cmd_lst->fd);
		// printf("%s\n",*(cmd_lst->cmd));
		
		dup2(cmd_lst->fd[1], 1);
		exe_just(cmd_lst, env);
		// cmd_lst->next->fd[1] = cmd_lst->fd[1];
		
		cmd_lst->next->fd[0] = cmd_lst->fd[0];
		// close(cmd_lst->fd[0]);
		// close(cmd_lst->fd[1]);
		cmd_lst = cmd_lst->next;
		dup2(cmd_lst->fd[0], 0);
		// dup2(0,fd_input);
		
		dup2(fd_output,1);

		// dup2(1,fd_output);
		close(cmd_lst->fd[0]);
		close(cmd_lst->fd[1]);
		// dup2(0,fd_input);
		// write(cmd_lst->fd[1], ft_itoa(cmd_lst->fd[1]), ft_strlen(ft_itoa(cmd_lst->fd[1])));
		// printf("%s\n",*(cmd_lst->cmd));
		exe_just(cmd_lst, env);




		// printf("1\n");
		// open_fd(cmd_lst, idx, 2);//dup
		// printf("2\n");
		// close_fd(cmd_lst);//fd close
		// exe_pipe(cmd_lst, env);
	// 	 cmd_lst = cmd_lst -> next;
	// }

	
}

int main()
{
	char **env;	
	char *command;
	t_cmd_lst *cmd_lst;

	welcome_text();
	env = find_envp_path();

	cmd_lst = NULL;
	while(1)
	{
		command = readline("minishell-1.0$ ");
		//printf("----%d---\n", command[0]);
		//printf("----%d---\n", command);
		//ctrl + c 를 누르면 새로운 행이 만들어지도록 어떻게 만들가
		//if (command && ft_strlen(command) > 0)
		if (command && ft_strlen(command) > 0) 
		//멍청아!!!!!!!!! *command >> ls | pwd 이렇게 하면 버그/ command >> enter 주소가 있음단독으로는 안됨 ..
		//ft_strlen(command) > 0 && command 이조합도 안됨
		{
			//printf("%s", command);
			if (split_line(&cmd_lst, command))
				return (EXIT_FAILURE);
			if (parse(cmd_lst))
				return (EXIT_FAILURE);

			exe_main(cmd_lst, env);
			//이런식으로 갈겨도 되는거 맞음?
			cmd_lst = NULL;
			free(cmd_lst);
		}
		add_history(command);
		//env free;
		free(command);
	}
	return 0;
}
