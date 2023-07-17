/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:54:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/17 23:56:43 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	parse_ambient_light(t_data *data, char **info)
{
	if (__2d_len(info) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light = ft_calloc(sizeof(t_amb_light), 1);
	if (!data->lighting->amb_light)
		return ;
	data->lighting->amb_light->ratio = ft_atod(info[1]);
	if (!(data->lighting->amb_light->ratio >= 0.0
			&& data->lighting->amb_light->ratio <= 1.0))
		__exit_error("ValueError: Required 'A' ratio range is [0.0 ; 1.0]\n");
	data->lighting->amb_light->color = parse_color(parse_data(info[2]));
	check_color(data->lighting->amb_light->color);
}

void	parse_light(t_data *data, char **info)
{
	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light = ft_calloc(sizeof(t_light), 1);
	if (!data->lighting->light)
		return ;
	data->lighting->light->ratio = ft_atod(info[2]);
	if (!(data->lighting->light->ratio >= 0.0
			&& data->lighting->light->ratio <= 1.0))
		__exit_error("ValueError: Required 'L' ratio range is [0.0 ; 1.0]\n");
	data->lighting->light->point = parse_vect(parse_data(info[1]));
	data->lighting->light->color = parse_color(parse_data(info[3]));
	check_color(data->lighting->light->color);
}

void	parse_camera(t_data *data, char **info)
{
	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	data->camera = ft_calloc(sizeof(t_camera), 1);
	if (!data->camera)
		return ;
	data->camera->fov = ft_atod(info[3]);
	if (!(data->camera->fov >= 0 && data->camera->fov <= 180))
		__exit_error("TypeError: Required 'C' FOV range is [0 ; 180]\n");
	data->camera->normalized = parse_vect(parse_data(info[2]));
	check_normalized(data->camera->normalized);
	data->camera->origin = parse_vect(parse_data(info[1]));
}
