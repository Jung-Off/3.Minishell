#include "minishell.h"

int	parse_redirect(t_cmd_lst *lst, int del)
{
	t_redirect	**redirect_lst;
	t_redirect	*new;
	int			i;

	redirect_lst = NULL;
	new = redirect_new();
	if (*lst->cmd[del] == '<')
		redirect_lst = &(lst->in);
	else if (*lst->cmd[del] == '>')
		redirect_lst = &(lst->out);
	if (ft_strncmp(lst->cmd[del], "<<", 2) == 0)
		new->type = DOUBLE;
	else if (*lst->cmd[del] == '<')
		new->type = SINGLE;
	else if (ft_strncmp(lst->cmd[del], ">>", 2) == 0)
		new->type = DOUBLE;
	else if (*lst->cmd[del] == '>')
		new->type = SINGLE;
	i = new->type;
	while (ft_isspace(lst->cmd[del][i]))
		i++;
	new->file = ft_substr(&(lst->cmd[del][i]), 0,
			ft_strlen(&(lst->cmd[del][i])));
	redirect_add_back(redirect_lst, new);
//	printf("!!!! (%s), (%s)\n", lst->cmd[del], new->file);
	lst->cmd = del_cmd(lst->cmd, del);
	printf("--- %d %s ---\n", lst->in->type, lst->in->file);
//	printf("--- %d %s ---\n", lst->out->type, lst->out->file);
	return (EXIT_SUCCESS);
}

int	parse(t_cmd_lst *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (*lst->cmd[i] == '<' || *lst->cmd[i] == '>')
			{
				parse_redirect(lst, i);
				continue ;
			}
			i++;
		}
		printf("\n");
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}