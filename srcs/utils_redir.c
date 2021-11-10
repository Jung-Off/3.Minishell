/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:10:00 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/04 11:35:09 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*create_redir(char *line)
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	if (ft_strncmp(line, "<<", 2) == 0)
		new->type = REDIRECT_INPUT_DOUBLE;
	else if (ft_strncmp(line, ">>", 2) == 0)
		new->type = REDIRECT_OUTPUT_DOUBLE;
	else if (*line == '<')
		new->type = REDIRECT_INPUT_SINGLE;
	else if (*line == '>')
		new->type = REDIRECT_OUTPUT_DOUBLE;
	if (new->type % 2 == 0)
		line += 2;
	else
		line += 1;
	while (ft_isspace(*line))
		line++;
	new->file = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void	redir_add_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*p;

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

void	redir_clear(t_redirect **lst)
{
	t_redirect	*p;
	t_redirect	*tmp;

	p = *lst;
	while (p)
	{
		tmp = p->next;
		free(p->file);
		free(p);
		p = tmp;
	}
	*lst = NULL;
}
