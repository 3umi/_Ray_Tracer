/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:54:26 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/17 02:04:16 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_ambient_light(t_data *data, char **info)
{
	char	**color;

	if (__2d_len(info) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light = ft_calloc(sizeof(t_amb_light), 1);
	if (!data->lighting->amb_light)
		return ;
	data->lighting->amb_light->ratio = strtod(info[1], NULL);
	color = ft_split(info[2], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light->color = fill_color(strtod(color[0], NULL), strtod(color[1], NULL), strtod(color[2], NULL));
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
	data->lighting->light->ratio = strtod(info[2], NULL);
	point = ft_split(info[1], ',');
	if (__2d_len(point) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light->point = vect_new(strtod(point[0], NULL), strtod(point[1], NULL), strtod(point[2], NULL));
	color = ft_split(info[3], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light->color = fill_color(strtod(color[0], NULL), strtod(color[1], NULL), strtod(color[2], NULL));
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
	data->camera->fov = strtod(info[3], NULL);
	origin = ft_split(info[1], ',');
	if (__2d_len(origin) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->camera->origin = vect_new(strtod(origin[0], NULL), strtod(origin[1], NULL), strtod(origin[2], NULL));
	normalized = ft_split(info[2], ',');
	if (__2d_len(normalized) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->camera->normalized = vect_new(strtod(normalized[0], NULL), strtod(normalized[1], NULL), strtod(normalized[2], NULL));
}
