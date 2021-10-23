/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:43:38 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 16:16:28 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*new;
	t_list	*head;

	if (!lst || !f || !del)
		return (0);
	p = lst;
	head = 0;
	while (p)
	{
		new = ft_lstnew(f(p->content));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, new);
		p = p->next;
	}
	return (head);
}
