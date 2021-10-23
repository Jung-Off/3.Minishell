#include "minishell.h"

void	redirect_add_back(t_redirect **lst, t_redirect *new)
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

t_redirect	*redirect_new(void)
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->type = NONE;
	new->file = NULL;
	new->next = NULL;
	return (new);
}