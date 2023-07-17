/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 02:02:50 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/17 16:55:07 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
	int			info_len;

	info_len = __2d_len(info);
	if (info_len != 4 && info_len != 5)
		__exit_error("TypeError: Bad information structure\n");
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return ;
	sphere->radius = ft_atod(info[2]) / 2;
	sphere->center = parse_vect(parse_data(info[1]));
	sphere->color_a = parse_color(parse_data(info[3]));
	if (info_len == 5)
		sphere->color_b = parse_color(parse_data(info[4]));
	else
		sphere->color_b = sphere->color_a;
	check_normalized_and_color(sphere->color_a, sphere->color_b,
		vect_new(0, 0, 0));
	object_add_back(&(*data)->object, new_object(SPHERE, sphere));
}

static void	parse_cylinder(t_data **data, char **info)
{
	t_cylinder	*cylinder;
	int			info_len;

	info_len = __2d_len(info);
	if (info_len != 6 && info_len != 7)
		__exit_error("TypeError: Bad information structure\n");
	cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!cylinder)
		return ;
	cylinder->radius = ft_atod(info[3]) / 2;
	cylinder->height = ft_atod(info[4]);
	cylinder->center = parse_vect(parse_data(info[1]));
	cylinder->normal = parse_vect(parse_data(info[2]));
	cylinder->color_a = parse_color(parse_data(info[5]));
	if (info_len == 7)
		cylinder->color_b = parse_color(parse_data(info[6]));
	else
		cylinder->color_b = cylinder->color_a;
	printf("%f %f %f\n", cylinder->color_a.r, cylinder->color_a.g, cylinder->color_a.b);
	printf("%s\n", info[5]);

	check_normalized_and_color(cylinder->color_a, cylinder->color_b,
		cylinder->normal);
	object_add_back(&(*data)->object, new_object(CYLINDER, cylinder));
}

static void	parse_plane(t_data **data, char **info)
{
	t_plane	*plane;
	int		info_len;

	info_len = __2d_len(info);
	if (info_len != 4 && info_len != 5)
		__exit_error("TypeError: Bad information structure\n");
	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return ;
	plane->point = parse_vect(parse_data(info[1]));
	plane->normal = parse_vect(parse_data(info[2]));
	plane->color_a = parse_color(parse_data(info[3]));
	if (info_len == 5)
		plane->color_b = parse_color(parse_data(info[4]));
	else
		plane->color_b = plane->color_a;
	check_normalized_and_color(plane->color_a, plane->color_b, plane->normal);
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
