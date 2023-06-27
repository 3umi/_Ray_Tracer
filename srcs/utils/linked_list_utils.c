/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:04 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/26 20:39:41 by belkarto         ###   ########.fr       */
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
	if (new_object->type == SPHERE)
		new_object->object = ft_calloc(sizeof(t_sphere), 1);
	else if (new_object->type == PLANE)
		new_object->object = ft_calloc(sizeof(t_plane), 1);
	else if (new_object->type == CYLINDER)
		new_object->object = ft_calloc(sizeof(t_cylinder), 1);
	if (!new_object->object)
		return (NULL);
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
