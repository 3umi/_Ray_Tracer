/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:56:35 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/24 08:01:07 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !del || !f)
		return (NULL);
	new = NULL;
	tmp = lst;
	while (tmp)
	{
		ft_lstadd_back(&new, ft_lstnew(f(tmp->content)));
		if (!new)
			ft_lstclear(&new, (*del));
		tmp = tmp->next;
	}
	return (new);
}
