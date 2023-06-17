/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 02:02:50 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/17 02:05:34 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
	sphere->diameter = strtod(info[2], NULL);
	sphere->radius = sphere->diameter / 2;
	center = ft_split(info[1], ',');
	if (__2d_len(center) != 3)
		__exit_error("TypeError: Bad information structure\n");
	sphere->center = vect_new(strtod(center[0], NULL), strtod(center[1], NULL), strtod(center[2], NULL));
	color = ft_split(info[3], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	sphere->color = fill_color(strtod(color[0], NULL), strtod(color[1], NULL), strtod(color[2], NULL));
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
	cylinder->diameter = strtod(info[3], NULL);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = strtod(info[4], NULL);
	center = ft_split(info[1], ',');
	normalized = ft_split(info[2], ',');
	color = ft_split(info[5], ',');
	if (__2d_len(center) != 3 || __2d_len(normalized) != 3
		|| __2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	cylinder->center = vect_new(strtod(center[0], NULL), strtod(center[1], NULL), strtod(center[2], NULL));
	cylinder->normal = vect_new(strtod(normalized[0], NULL), strtod(normalized[1], NULL), strtod(normalized[2], NULL));
	cylinder->color = fill_color(strtod(color[0], NULL), strtod(color[1], NULL), strtod(color[2], NULL));
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
	plane->point = vect_new(strtod(point[0], NULL), strtod(point[1], NULL), strtod(point[2], NULL));
	plane->normal = vect_new(strtod(normalized[0], NULL), strtod(normalized[1], NULL), strtod(normalized[2], NULL));
	plane->color = fill_color(strtod(color[0], NULL), strtod(color[1], NULL), strtod(color[2], NULL));
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
