/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:54:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/26 23:22:36 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_ambient_light(t_data *data, char **info)
{
	char	**color;

	if (__2d_len(info) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light = ft_calloc(sizeof(t_amb_light), 1);
	if (!data->lighting->amb_light)
		return ;
	data->lighting->amb_light->ratio = ft_atod(info[1]);
	if (!(data->lighting->amb_light->ratio >= 0.0
		&& data->lighting->amb_light->ratio <= 1.0))
		__exit_error("ValueError: Required 'A' ratio range is [0.0 ; 1.0]\n");
	color = ft_split(info[2], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light->color = fill_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]));
	check_color(data->lighting->amb_light->color);
}

void	parse_light(t_data *data, char **info)
{
	char	**point;
	char	**color;

	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light = ft_calloc(sizeof(t_light), 1);
	if (!data->lighting->light)
		return ;
	data->lighting->light->ratio = ft_atod(info[2]);
	if (!(data->lighting->light->ratio >= 0.0
		&& data->lighting->light->ratio <= 1.0))
		__exit_error("ValueError: Required 'L' ratio range is [0.0 ; 1.0]\n");
	point = ft_split(info[1], ',');
	if (__2d_len(point) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light->point = vect_new(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2]));
	color = ft_split(info[3], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light->color = fill_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]));
	check_color(data->lighting->light->color);
}

void	parse_camera(t_data *data, char **info)
{
	char	**origin;
	char	**normalized;

	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	data->camera = ft_calloc(sizeof(t_camera), 1);
	if (!data->camera)
		return ;
	data->camera->fov = ft_atod(info[3]);
	if (!(data->camera->fov >= 0 && data->camera->fov <= 180))
		__exit_error("TypeError: Required 'C' FOV range is [0 ; 180]\n");
	origin = ft_split(info[1], ',');
	if (__2d_len(origin) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->camera->origin = vect_new(ft_atod(origin[0]), ft_atod(origin[1]), ft_atod(origin[2]));
	normalized = ft_split(info[2], ',');
	if (__2d_len(normalized) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->camera->normalized = vect_new(ft_atod(normalized[0]), ft_atod(normalized[1]), ft_atod(normalized[2]));
	check_normalized(data->camera->normalized);
}
