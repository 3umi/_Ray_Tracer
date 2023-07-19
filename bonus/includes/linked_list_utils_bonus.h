/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:14:27 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/18 01:21:31 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_UTILS_BONUS_H
# define LINKED_LIST_UTILS_BONUS_H

t_object	*new_object(t_type type, void *object);
void		object_add_back(t_object **object_head, t_object *new_object);

t_light		*new_light(t_light *light);
void		light_add_back(t_light **light_head, t_light *new_light);

#endif
