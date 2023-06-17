/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:05:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/17 01:44:22 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	__2d_len(char **tab)
{
	int	len;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len++])
		;
	return (len - 1);
}

static t_color	fill_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

static int	check_argc(int argc)
{
	return (argc < 2);
}

static void	check_file(char *str)
{
	char	*check_str;
	int		check_file;

	check_str = ft_strrchr(str, 't');
	if (!check_str || ft_strncmp(check_str - 2, ".rt", 4) != 0
		|| ft_strlen(str) < 4)
		__exit_error("ValueError: File not valid.\n");
	check_file = open(str, O_RDONLY);
	if (check_file == -1)
	{
		ft_putstr_fd("FileError: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		__exit_error("\n");
	}
	close(check_file);
}

static char	*read_file(char *str)
{
	int		file;
	char	*read;
	char	*buff;

	file = open(str, O_RDONLY);
	buff = NULL;
	while (1)
	{
		read = get_next_line(file);
		if (!read)
			break ;
		buff = ft_strjoin_gnl(buff, read);
		free(read);
	}
	free(read);
	return (buff);
}

static void	check_identifier(char *identifier, t_parse *parse)
{
	if (ft_strcmp(identifier, "A") != 0 && ft_strcmp(identifier, "C") != 0
		&& ft_strcmp(identifier, "L") != 0 && ft_strcmp(identifier, "sp") != 0
		&& ft_strcmp(identifier, "pl") != 0 && ft_strcmp(identifier, "cy") != 0)
		__exit_error("TypeError: Unkown identifier type.\n");
	if ((!ft_strcmp(identifier, "A") && parse->A)
		|| (!ft_strcmp(identifier, "C") && parse->C)
		|| (!ft_strcmp(identifier, "L") && parse->L))
		__exit_error("TypeError: Identifier type redefinition.\n");
	if (!ft_strcmp(identifier, "A"))
		parse->A = 1;
	else if (!ft_strcmp(identifier, "C"))
		parse->C = 1;
	else if (!ft_strcmp(identifier, "L"))
		parse->L = 1;
}

static void	parse_ambient_light(t_data *data, char **info)
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

static void	parse_light(t_data *data, char **info)
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

static void	parse_camera(t_data *data, char **info)
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

static void	iterate_line(t_data *data, t_parse *parse, char *line)
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

static void	print_data(t_data *data)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	printf("\n++++++++++++++++++++++++Ambient_light+++++++++++++++++++++++++\n");
	printf("Ratio	: %f\n", data->lighting->amb_light->ratio);
	printf("Color.r : %f, Color.g : %f, Color.b : %f\n", data->lighting->amb_light->color.r, data->lighting->amb_light->color.g, data->lighting->amb_light->color.b);
	printf("\n++++++++++++++++++++++++++++Camera++++++++++++++++++++++++++++\n");
	printf("Point.x : %f, Point.y : %f, Point.z : %f\n", data->camera->origin.x, data->camera->origin.y, data->camera->origin.z);
	printf("Normal.x: %f, Normal.y: %f, Normal.z: %f\n", data->camera->normalized.x, data->camera->normalized.y, data->camera->normalized.z);
	printf("FOV	: %f\n", data->camera->fov);
	printf("\n++++++++++++++++++++++++++++Light++++++++++++++++++++++++++++\n");
	printf("Point.x : %f, Point.y : %f, Point.z : %f\n", data->lighting->light->point.x, data->lighting->light->point.y, data->lighting->light->point.z);
	printf("Ratio	: %f\n", data->lighting->light->ratio);
	printf("Color.r : %f, Color.g : %f, Color.b : %f\n", data->lighting->light->color.r, data->lighting->light->color.g, data->lighting->light->color.b);
	while (data->object)
	{
		if (data->object->type == SPHERE)
		{
			printf("\n++++++++++++++++++++++++SPHERE+++++++++++++++++++++++++\n");
			sphere = data->object->object;
			printf("Diameter: %f\n", sphere->diameter);
			printf("Radius: %f\n", sphere->radius);
			printf("Center.x : %f, Center.y : %f, Center.z : %f\n", sphere->center.x, sphere->center.y, sphere->center.z);
			printf("Color.r : %f, Color.g : %f, Color.b : %f\n", sphere->color.r, sphere->color.g, sphere->color.b);
		}
		if (data->object->type == PLANE)
		{
			printf("\n++++++++++++++++++++++++PLANE+++++++++++++++++++++++++\n");	
			plane = data->object->object;
			printf("Normal.x: %f, Normal.y: %f, Normal.z: %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
			printf("Point.x : %f, Point.y : %f, Point.z : %f\n", plane->point.x, plane->point.y, plane->point.z);
			printf("Color.r : %f, Color.g : %f, Color.b : %f\n", plane->color.r, plane->color.g, plane->color.b);
		}
		if (data->object->type == CYLINDER)
		{
			printf("\n++++++++++++++++++++++CYLINDER+++++++++++++++++++++++\n");
			cylinder = data->object->object;
			printf("Center.x : %f, Center.y : %f, Center.z : %f\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
			printf("Normal.x: %f, Normal.y: %f, Normal.z: %f\n", cylinder->normal.x, cylinder->normal.y, cylinder->normal.z);
			printf("Diameter: %f\n", cylinder->diameter);
			printf("Radius: %f\n", cylinder->radius);
			printf("Height: %f\n", cylinder->height);
			printf("Color.r : %f, Color.g : %f, Color.b : %f\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
		}
		data->object = data->object->next;
	}
}

static void	fill_data(t_data **data, char *str)
{
	int		i;
	char	*buff;
	char	**line;
	t_parse	parse;

	i = 0;
	parse.A = 0;
	parse.C = 0;
	parse.L = 0;
	(*data) = ft_calloc(sizeof(t_data), 1);
	if (!(*data))
		return ;
	(*data)->lighting = ft_calloc(sizeof(t_lighting), 1);
	if (!(*data)->lighting)
		return ;
	buff = read_file(str);
	if (!buff)
		__exit_error("FileError: File empty.\n");
	line = ft_split(buff, '\n');
	if (!line[i])
		__exit_error("FileError: File empty.\n");
	while (line[i])
		iterate_line(*data, &parse, line[i++]);
	if (!parse.A || !parse.C || !parse.L)
		__exit_error("ValueError: An identifier type is missing.\n");
}

void	__parsing(int argc, char **argv, t_data *data)
{
	if (check_argc(argc))
		__exit_error("TypeError: Not enough arguments.\n");
	check_file(argv[1]);
	fill_data(&data, argv[1]);
	print_data(data);
}
