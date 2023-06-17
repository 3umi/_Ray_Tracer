/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:05:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/17 01:55:49 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
}
