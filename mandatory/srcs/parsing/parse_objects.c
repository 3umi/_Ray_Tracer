/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 02:02:50 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/14 20:44:18 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	*free_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

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
	sphere->center = vect_new(ft_atod(center[0]),
			ft_atod(center[1]), ft_atod(center[2]));
	free_2d(center);
	color = ft_split(info[3], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	sphere->color = fill_color(ft_atod(color[0]),
			ft_atod(color[1]), ft_atod(color[2]));
	check_normalized_and_color(sphere->color, vect_new(0, 0, 0));
	free_2d(color);
	object_add_back(&(*data)->object, new_object(SPHERE, sphere));
}

// static void	parse_cylinder(t_data **data, char **info)
// {
// 	t_cylinder	*cylinder;
// 	char		**c;
// 	char		**n;
// 	char		**c;

// 	if (__2d_len(info) != 6)
// 		__exit_error("TypeError: Bad information structure\n");
// 	cylinder = ft_calloc(sizeof(t_cylinder), 1);
// 	if (!cylinder)
// 		return ;
// 	cylinder->radius = ft_atod(info[3]) / 2;
// 	cylinder->height = ft_atod(info[4]);
// 	c = ft_split(info[1], ',');
// 	n = ft_split(info[2], ',');
// 	c = ft_split(info[5], ',');
// 	if (__2d_len(c) != 3 || __2d_len(n) != 3 || __2d_len(c) != 3)
// 		__exit_error("TypeError: Bad information structure\n");
// 	cylinder->center = vect_new(ft_atod(c[0]), ft_atod(c[1]), ft_atod(c[2]));
// 	cylinder->normal = vect_new(ft_atod(n[0]), ft_atod(n[1]), ft_atod(n[2]));
// 	cylinder->color = fill_color(ft_atod(c[0]), ft_atod(c[1]), ft_atod(c[2]));
// 	check_normalized_and_color(cylinder->color, cylinder->normal);
// 	free_2d(c);
// 	free_2d(n);
// 	free_2d(c);
// 	object_add_back(&(*data)->object, new_object(CYLINDER, cylinder));
// }

static void	parse_cylinder(t_data **data, char **info)
{
	t_cylinder	*cylinder;
	char		**cn;
	char		**n;
	char		**c;

	if (__2d_len(info) != 6)
		__exit_error("TypeError: Bad information structure\n");
	cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!cylinder)
		return ;
	cylinder->radius = ft_atod(info[3]) / 2;
	cylinder->height = ft_atod(info[4]);
	cn = ft_split(info[1], ',');
	n = ft_split(info[2], ',');
	c = ft_split(info[5], ',');
	if (__2d_len(cn) != 3 || __2d_len(n) != 3 || __2d_len(c) != 3)
		__exit_error("TypeError: Bad information structure\n");
	cylinder->center = vect_new(ft_atod(cn[0]), ft_atod(cn[1]), ft_atod(cn[2]));
	cylinder->normal = vect_new(ft_atod(n[0]), ft_atod(n[1]), ft_atod(n[2]));
	cylinder->color = fill_color(ft_atod(c[0]), ft_atod(c[1]), ft_atod(c[2]));
	check_normalized_and_color(cylinder->color, cylinder->normal);
	free_2d(cn);
	free_2d(n);
	free_2d(c);
	object_add_back(&(*data)->object, new_object(CYLINDER, cylinder));
}

static void	parse_plane(t_data **data, char **info)
{
	t_plane	*plane;
	char	**p;
	char	**n;
	char	**c;

	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return ;
	p = ft_split(info[1], ',');
	n = ft_split(info[2], ',');
	c = ft_split(info[3], ',');
	if (__2d_len(p) != 3 || __2d_len(n) != 3
		|| __2d_len(c) != 3)
		__exit_error("TypeError: Bad information structure\n");
	plane->point = vect_new(ft_atod(p[0]), ft_atod(p[1]), ft_atod(p[2]));
	plane->normal = vect_new(ft_atod(n[0]), ft_atod(n[1]), ft_atod(n[2]));
	plane->color = fill_color(ft_atod(c[0]), ft_atod(c[1]), ft_atod(c[2]));
	check_normalized_and_color(plane->color, plane->normal);
	free_2d(p);
	free_2d(n);
	free_2d(c);
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
	free_2d(info);
}
