/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:05:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/16 02:31:35 by ohalim           ###   ########.fr       */
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

static int	check_argc(int argc)
{
	printf("Posay.\n");
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
	// free(check_str);
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
			break;
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
			&& ft_strcmp(identifier, "pl")  != 0 && ft_strcmp(identifier, "cy") != 0)
			__exit_error("TypeError: Unkown identifier type.\n");
	if ((!ft_strcmp(identifier, "A") && parse->A) || (!ft_strcmp(identifier, "C") && parse->C) 
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
	char **color;

	if (__2d_len(info) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light = ft_calloc(sizeof(t_amb_light), 1);
	if (!data->lighting->amb_light)
		return ;
	data->lighting->amb_light->ratio = ft_atoi(info[1]); // Need another 'atoi' for double.
	color = ft_split(info[2], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->amb_light->color.r = ft_atoi(color[0]);
	data->lighting->amb_light->color.g = ft_atoi(color[1]);
	data->lighting->amb_light->color.b = ft_atoi(color[2]);
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
	data->lighting->light->ratio = ft_atoi(info[2]);
	point = ft_split(info[1], ',');
	if (__2d_len(point) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light->point.x = ft_atoi(point[0]);
	data->lighting->light->point.y = ft_atoi(point[1]);
	data->lighting->light->point.z = ft_atoi(point[2]);
	color = ft_split(info[3], ',');
	if (__2d_len(color) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->lighting->light->color.r = ft_atoi(color[0]);
	data->lighting->light->color.g = ft_atoi(color[0]);
	data->lighting->light->color.b = ft_atoi(color[0]);
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
	data->camera->fov = ft_atoi(info[3]);
	origin = ft_split(info[1], ',');
	if (__2d_len(origin) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->camera->origin.x = ft_atoi(origin[0]);
	data->camera->origin.y = ft_atoi(origin[1]);
	data->camera->origin.z = ft_atoi(origin[2]);
	normalized = ft_split(info[2], ',');
	if (__2d_len(normalized) != 3)
		__exit_error("TypeError: Bad information structure\n");
	data->camera->normalized.x = ft_atoi(normalized[0]);
	data->camera->normalized.y = ft_atoi(normalized[1]);
	data->camera->normalized.z = ft_atoi(normalized[2]);
}

static void	parse_sphere(t_data *data, char **info)
{
	t_sphere	*sphere;

	if (__2d_len(info) != 4)
		__exit_error("TypeError: Bad information structure\n");
	object_add_back(&data->object, new_object(SPHERE));
	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return ;
	data->object->object = sphere;
}

static void	iterate_line(t_data *data, t_parse *parse, char *line)
{
	int			i;
	char		**info;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return ;
	i = 0;
	info = ft_split(line, 32);
	check_identifier(info[i], parse);
	data->lighting = ft_calloc(sizeof(t_lighting), 1);
	if (!data->lighting)
		return ;
	if (!ft_strcmp(info[i], "A"))
		parse_ambient_light(data, info);
	else if (!ft_strcmp(info[i], "L"))
		parse_light(data, info);
	else if (!ft_strcmp(info[i], "C"))
		parse_camera(data, info);
	else if (!ft_strcmp(info[i], "sp"))
		parse_sphere(data, info);
	// else if (!ft_strcmp(info[i], "pl"))
	// 	parse_plane(data, info);
	// else if (!ft_strcmp(info[i], "cy"))
	// 	parse_cylinder(data, info);
}

static void	fill_data(t_data *data, char *str)
{
	(void)data;
	int		i;
	char	*buff;
	char	**line;
	t_parse	parse;

	i = 0;
	parse.A = 0;
	parse.C = 0;
	parse.L = 0;
	buff = read_file(str);
	if (!buff)
		__exit_error("FileError: File empty.\n");
	line = ft_split(buff, '\n');
	if (!line[i])
		__exit_error("FileError: File empty.\n");
	while (line[i])
		iterate_line(data, &parse, line[i++]);
}

void	__parsing(int argc, char **argv, t_data *data)
{
	(void)data;
	if (check_argc(argc))
		__exit_error("TypeError: Not enough arguments.\n");
	check_file(argv[1]);
	fill_data(data, argv[1]);
}
