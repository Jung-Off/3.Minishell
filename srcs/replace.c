/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:40:11 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/03 18:24:48 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

int	add_char(char **str, char ch)
{
	char	*ch_str;
	char	*new;

	ch_str = (char *)malloc(2);
	ch_str[0] = ch;
	ch_str[1] = 0;
	new = sh_strjoin(*str, ch_str);
	free(*str);
	free(ch_str);
	*str = new;
	return (EXIT_SUCCESS);
}

int	get_env(char **res, char *str, char **envp, int *idx)
{
	int		key_size;
	char	*key;
	char	*val;
	char	*join;

	if (*str == '?' && (*idx)++)
	{
		val = "($?)";
		join = sh_strjoin(*res, val);
		free(*res);
		*res = join;
		return (EXIT_SUCCESS);
	}
	key_size = 0;
	while (str[key_size] && str[key_size] != '\"' && str[key_size] != '\''
		&& str[key_size] != ' ' && str[key_size] != '$')
		key_size++;
	key = ft_substr(str, 0, key_size);
	val = NULL;
	while (*envp)
	{
		if (key_size == 0)
			val = "$";
		else if (ft_strncmp(*envp, key, ft_strlen(key)) == 0)
			val = getenv(*envp);
		envp++;
	}
	join = sh_strjoin(*res, val);
	free(*res);
	*res = join;
	*idx += key_size;
	free(key);
	return (EXIT_SUCCESS);
}

int	replace_env(char **str, char **envp)
{
	int		i;
	int		quote;
	char	*new_str;

	i = 0;
	quote = NONE;
	new_str = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"' && quote == NONE)
			quote = DOUBLE;
		else if ((*str)[i] == '\'' && quote == NONE)
			quote = SINGLE;
		else if ((*str)[i] == QUOTE[quote])
			quote = NONE;
		else if ((*str)[i] == '$' && quote != SINGLE)
			get_env(&new_str, &((*str)[i + 1]), envp, &i);
		else if ((*str)[i] != QUOTE[quote])
			add_char(&new_str, (*str)[i]);
		i++;
	}
	free(*str);
	*str = new_str;
	return (EXIT_SUCCESS);
}

int	replace(t_cmd *cmd, char **envp)
{
	char		**p;
	t_redirect	*rp;

	p = cmd->argv;
	while (*p)
	{
		replace_env(p, envp);
		p++;
	}
	rp = cmd->redirect;
	while (rp)
	{
		replace_env(&(rp->file), envp);
		rp = rp->next;
	}
	return (EXIT_SUCCESS);
}
