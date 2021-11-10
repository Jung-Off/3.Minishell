/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:32:13 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/03 18:37:53 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <readline/history.h>

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define NONE 0
# define SINGLE 1
# define DOUBLE 2

# define REDIRECT_INPUT_SINGLE 1
# define REDIRECT_INPUT_DOUBLE 2
# define REDIRECT_OUTPUT_SINGLE 3
# define REDIRECT_OUTPUT_DOUBLE 4

# define QUOTE "\0\'\""

typedef int		t_bool;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				**argv;
	int 				fd[2];
	struct s_redirect	*redirect;
	struct s_cmd		*next;
}						t_cmd;

// error.c
int			error_handler(char *err_msg);
t_bool		error_check(t_cmd *cmd);

// parse_command.c
int			split_redirect(char **input);
int			split_command(char **res, char **cmd_str);
int			parse_command(t_cmd **cmd, char *cmd_str);

// parse_line.c
int			pass_quotes(char **input);
int			split_line(char **cmd, char **line);
int			parse_line(t_cmd **cmd_lst, char *line, char **envp);

// replace.c
int			replace(t_cmd *cmd, char **envp);

// utils_cmd.c
t_cmd		*create_cmd(void);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
char		**cmd_argv_add_back(char **old_cmd, char *input);
void		cmd_clear(t_cmd **lst);

// utils_redir.c
t_redirect	*create_redir(char *line);
void		redir_add_back(t_redirect **lst, t_redirect *new);
void		redir_clear(t_redirect **lst);

#endif
