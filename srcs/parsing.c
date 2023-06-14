/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:05:10 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/14 17:02:04 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
	check_str = get_next_line(check_file);
	if (!check_str || *check_str == '\n')
		__exit_error("FileError: File empty.\n");
	free (check_str);
	close(check_file);
}

static char	*read_file(char *str)
{
	int		file;
	char	*read;
	char	*buff;

	file = open(str, O_RDONLY);
	while (1)
	{
		read = get_next_line(file);
		if (!read)
			break;
		// if (strncmp(read, "\n", 2) != 0)
		buff = ft_strjoin(buff, read);
		free(read);
	}
	free(read);
	return (buff);
}

static void	fill_data(t_data *data, char *str)
{
	(void)data;
	char *buff;

	buff = read_file(str);
	printf("%s\n", buff);
}

void	__parsing(int argc, char **argv, t_data *data)
{
	(void)data;
	if (check_argc(argc))
		__exit_error("TypeError: Not enough arguments.\n");
	check_file(argv[1]);
	fill_data(data, argv[1]);
}
