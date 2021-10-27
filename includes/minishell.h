#ifndef MINISHELL_H
# define MINISHELL_H

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

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0


# define NONE 0
# define SINGLE 1
# define DOUBLE 2

# define QUOTE "\0\'\""

typedef int		t_bool;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd_lst
{
	char				**cmd;
	int					fd[2];
	struct s_redirect	*in;
	struct s_redirect	*out;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

// error.c
int			error_handler(char *err_msg);

// main.c

// parse.c
int			parse_redirect(t_cmd_lst *lst, int del);
int			parse(t_cmd_lst *lst);

// split.c
int			split_quotes(char **input);
int			split_redirect(char **input);
int			split_space(char **res, char **input);
int			split_command(t_cmd_lst **new, char *input);
int			split_line(t_cmd_lst **cmd_lst, char *input);

// utils_cmd_lst.c
void		cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new);
t_cmd_lst	*cmd_lst_new(void);
char		**add_cmd(char **old_cmd, char *input);
char		**del_cmd(char **old_cmd, int del);

// utils_redirect.c
void		redirect_add_back(t_redirect **lst, t_redirect *new);
t_redirect	*redirect_new(void);

#endif