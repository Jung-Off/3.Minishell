
#include "../includes/minishell.h"

void	cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*p;

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

t_cmd_lst	*cmd_lst_new(void)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!new)
		return (NULL);
	new->cmd = (char **)malloc(sizeof(char *));
	if (!new->cmd)
		return (NULL);
	new->cmd[0] = NULL;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return (new);
}

char	**add_cmd(char **old_cmd, char *input)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (old_cmd[size])
		size++;
	size++;
	new = (char **)malloc(sizeof(char *) * (size + 1));
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

char	**del_cmd(char **old_cmd, int del)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (old_cmd[size])
		size++;
	new = (char **)malloc(sizeof(char *) * size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < del)
	{
		new[i] = old_cmd[i];
		i++;
	}
	while (old_cmd[i + 1])
	{
		new[i] = old_cmd[i + 1];
		i++;
	}
	new[i] = NULL;
	return (new);
}