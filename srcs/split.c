#include "minishell.h"

int	split_quotes(char **input)
{
	int	quote;

	quote = NONE;
	if (**input == '\"' && (*input)++)
		quote = DOUBLE;
	else if (**input == '\'' && (*input)++)
		quote = SINGLE;
	while (**input != QUOTE[quote])
	{
		if (!**input)
			return (error_handler("unclosed quote"));
		(*input)++;
	}
	return (EXIT_SUCCESS);
}

int	split_redirect(char **input)
{
	int	redirect;

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
		if (split_quotes(input))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	split_space(char **res, char **input)
{
	char	*start;

	while (ft_isspace(**input))
		(*input)++;
	if (!**input)
		return (EXIT_SUCCESS);
	start = *input;
	if (**input == '<' || **input == '>')
	{
		if (split_redirect(input))
			return (EXIT_FAILURE);
		(*input)++;
	}
	while (**input && !ft_isspace(**input))
	{
		if (**input == '<' || **input == '>')
			break ;
		else if (**input == '\'' || **input == '\"')
			if (split_quotes(input))
				return (EXIT_FAILURE);
		(*input)++;
	}
	*res = ft_substr(start, 0, *input - start);
	return (EXIT_SUCCESS);
}

int	split_command(t_cmd_lst **new, char *input)
{
	char	*split_res;

	*new = cmd_lst_new();
	if (!*new)
		return (error_handler("malloc failed in cmd_lst_new()"));
	while (*input)
	{
		split_res = NULL;
		if (split_space(&split_res, &input))
			return (EXIT_FAILURE);
		(*new)->cmd = add_cmd((*new)->cmd, split_res);
		if (!((*new)->cmd))
			return (error_handler("malloc failed in add_cmd()"));
	}
	return (EXIT_SUCCESS);
}

int	split_line(t_cmd_lst **cmd_lst, char *input)
{
	t_cmd_lst	*new;
	char		**cmd_arr;
	int			i;

	new = NULL;
	cmd_arr = ft_split(input, '|');
	i = 0;
	while (cmd_arr[i])
	{
		if (split_command(&new, cmd_arr[i++]))
			return (EXIT_FAILURE);
		cmd_lst_add_back(cmd_lst, new);
	}
	free(cmd_arr);
	return (EXIT_SUCCESS);
}