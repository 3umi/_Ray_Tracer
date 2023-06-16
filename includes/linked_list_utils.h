/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:40 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/15 16:40:18 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_UTILS_H
# define LINKED_LIST_UTILS_H

t_object	*new_object(t_type type);
void		object_add_back(t_object **object_head, t_object *new_object);

#endif