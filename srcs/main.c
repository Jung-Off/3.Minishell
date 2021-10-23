
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

// void echo_f(char *command /*2차원 배열*/)
// {
// 	//2차원 배열로 들어올 것으로 생각을 하였을 때

// 	if ()

// }

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
		// free(env[i]); >> 빨리 없애버리고 싶었으나 명령어가 안들어오면 free된 것이라고 함
		add_slash = ft_strjoin(env_path, "/");
		free(env_path);
		env_path = ft_strjoin(add_slash, command_split);

		//printf("env_path :%s\n", env_path);
		if(stat(env_path, &buf) == 0)
		{
			//printf("여기가 출력이 안되는데 함수가 실행이 되네?");
			printf("%s", env_path);
			return (env_path);
		}
		++i;
	}
	printf("not invalid command\n");
	return (0);
}

int exe(t_cmd_lst *cmd_lst, char **env)
{
	char *env_path;

	env_path = exe_parse(env, cmd_lst->cmd[0]);

	if (env_path == 0)
	{
		printf("명령어가 없어서 함수 나가는중\n");
		return (1);
	}
	//printf("env_path : %s\n", env_path);

	//int i = 0;

	// while (command_split[i])
	// {
	// 	printf("%s\n", command_split[i]);
	// 	++i;
	// }
	execve(env_path, cmd_lst->cmd, NULL);

	//옵션이 실행이 안되었으면 free해주기
	//printf("command_unvalid_option\n");
	return (1);
}




void exe_function(t_cmd_lst *cmd_lst, char **env)
{

	while (cmd_lst)
	{
		exe(cmd_lst ,env);
		cmd_lst = cmd_lst->next;	
	}
	
	//여기서 파이프 라인 구현

}


void parent_child(t_cmd_lst *cmd_lst, char **env)
{
	pid_t pid;
	int status;


	pid = fork(); // 이함수 안쓰면 waitpid == -1 로 해서 error
	if (pid == 0)
	{
		//printf(" --------자식\n");
		exe_function(cmd_lst, env);
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
	
}

int pipe_count(t_cmd_lst *cmd)
{
	int i = 0;

	while (cmd)
	{
		cmd = cmd->next;
		++i;
	}
	i = i - 1;
	return i;
}

void dup_fds(int fds[], int i)
{
	
	if (i == 0)
	{		//pipe	std	
			//in    out
		
		dup2(fds[1], 1);
	
		close(fds[3]);
		close(fds[2]);
		close(fds[1]);
		close(fds[0]);
	}
	else
	{

		dup2(fds[2], 0);
		
		close(fds[3]);
		close(fds[2]);
		close(fds[1]);
		close(fds[0]);
	}
	
	
}

void pipe_link(t_cmd_lst *cmd_lst, int idx)
{
	int fds[4];


	printf("fds[%d]", fds[0]);
	printf("fds[%d]", fds[1]);
	printf("pipe_count %d\n", pipe_count(cmd_lst));

	int i = 0;
	while(i < 2)
	{
		pipe(&fds[i * 2]);
		++i;
	}
	dup_fds(fds, idx);

	printf("after fds[%d]", fds[0]);
	printf("after fds[%d]", fds[1]);
	printf("\n");
}

void exe_main(t_cmd_lst *cmd_lst, char **env)
{
	int i = 0;

	while(cmd_lst)
	{
		if(cmd_lst->next != NULL)
		{	
			pipe_link(cmd_lst, i);
			//"|로 연결이 되어져 있다는 것"
			//아마 여기서 파이프 연결
		}
		parent_child(cmd_lst, env);
		cmd_lst = cmd_lst->next;
	}
}

int main()
{
	char **env;	
	char *command;
	t_cmd_lst *cmd_lst;


	welcome_text();
	env = find_envp_path();

	while(1)
	{
		command = readline("minishell-1.0$ ");

		//ctrl + c 를 누르면 새로운 행이 만들어지도록 어떻게 만들가
		if (command)
		{
			printf("%s", command);
			if (split_line(&cmd_lst, command))
				return (EXIT_FAILURE);
			if (parse(cmd_lst))
				return (EXIT_FAILURE);
			exe_main(cmd_lst, env);
			//이런식으로 갈겨도 되는거 맞음?
			cmd_lst = NULL;
			//free(cmd_lst);
		}
		add_history(command);
		//env free;
		free(command);
	}
	return 0;
}
