/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 06:51:03 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/24 06:17:17 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = *lst;
	tmp1 = *lst;
	if (tmp == NULL || !del)
		return ;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		ft_lstdelone(tmp1, del);
		tmp1 = tmp;
	}
	*lst = NULL;
}
