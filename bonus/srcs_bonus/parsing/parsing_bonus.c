/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:05:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/15 17:33:00 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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

static void	initialize(t_parse *parse, int *i)
{
	parse->a = 0;
	parse->c = 0;
	parse->l = 0;
	*(i) = -1;
}

static void	fill_data(t_data **data, char *str)
{
	int		i;
	char	*buff;
	char	**line;
	t_parse	parse;

	initialize(&parse, &i);
	(*data)->lighting = ft_calloc(sizeof(t_lighting), 1);
	if (!(*data)->lighting)
		return ;
	(*data)->object = NULL;
	buff = read_file(str);
	if (!buff)
		__exit_error("FileError: File empty.\n");
	line = ft_split(buff, '\n');
	if (!line[0])
		__exit_error("FileError: File empty.\n");
	while (line[++i])
	{
		iterate_line(*data, &parse, line[i]);
		free(line[i]);
	}
	if (!parse.a || !parse.c || !parse.l)
		__exit_error("ValueError: An identifier type is missing.\n");
	free(buff);
	free(line);
}

void	__parsing(int argc, char **argv, t_data *data)
{
	if (check_argc(argc))
		__exit_error("TypeError: Two arguments are required.\n");
	check_file(argv[1]);
	fill_data(&data, argv[1]);
}
