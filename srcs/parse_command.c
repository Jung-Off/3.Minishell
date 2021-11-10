/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:56:15 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/03 17:59:14 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_redirect(char **input)
{
	int		redirect;

	redirect = NONE;
	if (ft_strncmp(*input, "<<", 2) == 0)
		redirect = DOUBLE;
	else if (**input == '<')
		redirect = SINGLE;
	else if (ft_strncmp(*input, ">>", 2) == 0)
		redirect = DOUBLE;
	else if (**input == '>')
		redirect = SINGLE;
	*input += redirect;
	while (ft_isspace(**input))
		(*input)++;
	if (**input == '\'' || **input == '\"')
	{
		if (pass_quotes(input))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	split_command(char **res, char **cmd_str)
{
	char	*start;

	while (ft_isspace(**cmd_str))
		(*cmd_str)++;
	start = *cmd_str;
	if (**cmd_str == '<' || **cmd_str == '>')
	{
		if (split_redirect(cmd_str))
			return (EXIT_FAILURE);
		(*cmd_str)++;
	}
	while (**cmd_str && **cmd_str != ' ')
	{
		if (**cmd_str == '<' || **cmd_str == '>')
			break ;
		else if (**cmd_str == '\'' || **cmd_str == '\"')
			if (pass_quotes(cmd_str))
				return (EXIT_FAILURE);
		(*cmd_str)++;
	}
	*res = ft_substr(start, 0, *cmd_str - start);
	return (EXIT_SUCCESS);
}

int	parse_command(t_cmd **cmd, char *cmd_str)
{
	char	*res;

	while (*cmd_str)
	{
		if (split_command(&res, &cmd_str))
			return (EXIT_FAILURE);
		if (*res == '<' || *res == '>')
		{
			redir_add_back(&((*cmd)->redirect), create_redir(res));
			free(res);
		}
		else if (*res)
			(*cmd)->argv = cmd_argv_add_back((*cmd)->argv, res);
		else
			free(res);
	}
	return (EXIT_SUCCESS);
}
