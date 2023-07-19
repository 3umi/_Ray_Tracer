/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:04 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/18 01:20:40 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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

t_light	*new_light(t_light *light)
{
	t_light	*new_light;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		return (NULL);
	new_light->angle = light->angle;
	new_light->color = light->color;
	new_light->normalized = light->normalized;
	new_light->point = light->point;
	new_light->ratio = light->ratio;
	new_light->next = NULL;
	return (new_light);
}

void	light_add_back(t_light **light_head, t_light *new_light)
{
	t_light	*tmp;

	tmp = *light_head;
	if (tmp == NULL)
	{
		*light_head = new_light;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
	}
}
