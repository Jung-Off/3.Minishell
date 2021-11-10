/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:12:22 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/04 11:47:33 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = (char **)malloc(sizeof(char *));
	if (!new->argv)
		return (NULL);
	new->argv[0] = NULL;
	new->redirect = NULL;
	new->next = NULL;
	return (new);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

char	**cmd_argv_add_back(char **old_cmd, char *input)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (old_cmd[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (old_cmd[i])
	{
		new[i] = old_cmd[i];
		i++;
	}
	new[i++] = input;
	new[i] = NULL;
	free(old_cmd);
	return (new);
}

void	cmd_clear(t_cmd **lst)
{
	t_cmd	*p;
	t_cmd	*tmp;
	char	**argv_p;

	p = *lst;
	while (p)
	{
		tmp = p->next;
		argv_p = p->argv;
		while (*p->argv)
			free(*p->argv++);
		free(argv_p);
		redir_clear(&(p->redirect));
		free(p);
		p = tmp;
	}
	*lst = NULL;
}
