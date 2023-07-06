/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:04 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/06 18:47:16 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object	*new_object(t_type type, void *object)
{
	t_object	*new_object;

	new_object = ft_calloc(sizeof(t_object), 1);
	if (!new_object)
		return (NULL);
	new_object->type = type;
	new_object->object = object;
	new_object->next = NULL;
	return (new_object);
}

void	object_add_back(t_object **object_head, t_object *new_object)
{
	t_object	*tmp;

	tmp = *object_head;
	if (tmp == NULL)
	{
		*object_head = new_object;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_object;
	}
}
