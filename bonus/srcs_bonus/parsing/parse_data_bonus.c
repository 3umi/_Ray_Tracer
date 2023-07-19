/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:14:50 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/16 19:15:32 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

char	**parse_data(char *info)
{
	char	**data;

	data = ft_split(info, ',');
	if (__2d_len(data) != 3)
		__exit_error("TypeError: Bad information structure\n");
	return (data);
}

t_vect	parse_vect(char **info)
{
	t_vect	vect;

	vect = vect_new(ft_atod(info[0]), ft_atod(info[1]),
			ft_atod(info[2]));
	free_2d (info);
	return (vect);
}

t_color	parse_color(char **info)
{
	t_color	color;

	color = fill_color(ft_atod(info[0]), ft_atod(info[1]),
			ft_atod(info[2]));
	free_2d (info);
	return (color);
}
