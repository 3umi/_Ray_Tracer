/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 02:02:50 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/20 18:14:54 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	parse_sphere(t_data **data, char **info)
{
	t_sphere	*sphere;
	char		**center;
	char		**color;

	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return ;
	sphere->diameter = ft_atod(info[2]);
	sphere->radius = sphere->diameter / 2;
	center = ft_split(info[1], ',');
	if (__2d_len(center) != 3)
		__exit_error("TypeError: Bad information structure\n");
	sphere->center = vect_new(ft_atod(center[0]), ft_atod(center[1]), ft_atod(center[2]));
	color = ft_split(info[3], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	sphere->color = fill_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]));
	check_color(sphere->color);
	object_add_back(&(*data)->object, new_object(SPHERE, sphere));
}

static void	parse_cylinder(t_data **data, char **info)
{
	t_cylinder	*cylinder;
	char		**center;
	char		**normalized;
	char		**color;

	if (__2d_len(info) != 6)
		__exit_error("TypeError: Bad information structure\n");
	cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!cylinder)
		return ;
	cylinder->diameter = ft_atod(info[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atod(info[4]);
	center = ft_split(info[1], ',');
	normalized = ft_split(info[2], ',');
	color = ft_split(info[5], ',');
	if (__2d_len(center) != 3 || __2d_len(normalized) != 3
		|| __2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	cylinder->center = vect_new(ft_atod(center[0]), ft_atod(center[1]), ft_atod(center[2]));
	cylinder->normal = vect_new(ft_atod(normalized[0]), ft_atod(normalized[1]), ft_atod(normalized[2]));
	check_normalized(cylinder->normal);
	cylinder->color = fill_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]));
	check_color(cylinder->color);
	object_add_back(&(*data)->object, new_object(CYLINDER, cylinder));
}

static void	parse_plane(t_data **data, char **info)
{
	t_plane	*plane;
	char	**point;
	char	**normalized;
	char	**color;

	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return ;
	point = ft_split(info[1], ',');
	normalized = ft_split(info[2], ',');
	color = ft_split(info[3], ',');
	if (__2d_len(point) != 3 || __2d_len(normalized) != 3
		|| __2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	plane->point = vect_new(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2]));
	plane->normal = vect_new(ft_atod(normalized[0]), ft_atod(normalized[1]), ft_atod(normalized[2]));
	check_normalized(plane->normal);
	plane->color = fill_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]));
	check_color(plane->color);
	object_add_back(&(*data)->object, new_object(PLANE, plane));
}

void	iterate_line(t_data *data, t_parse *parse, char *line)
{
	int			i;
	char		**info;

	i = 0;
	if (line[i] == '#')
		return ;
	info = ft_split(line, 32);
	check_identifier(info[i], parse);
	if (!ft_strcmp(info[i], "A"))
		parse_ambient_light(data, info);
	else if (!ft_strcmp(info[i], "L"))
		parse_light(data, info);
	else if (!ft_strcmp(info[i], "C"))
		parse_camera(data, info);
	else if (!ft_strcmp(info[i], "sp"))
		parse_sphere(&data, info);
	else if (!ft_strcmp(info[i], "pl"))
		parse_plane(&data, info);
	else if (!ft_strcmp(info[i], "cy"))
		parse_cylinder(&data, info);
}
