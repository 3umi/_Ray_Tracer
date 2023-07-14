/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:55:19 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/14 20:35:37 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	check_normalized_and_color(t_color color, t_vect normal)
{
	if (!(color.r >= 0 && color.r <= 255 && color.g >= 0 && color.g <= 255
			&& color.b >= 0 && color.b <= 255))
		__exit_error("ValueError: Required R,G,B range is [0 ; 255]\n");
	if (!(normal.x >= -1 && normal.x <= 1 && normal.y >= -1 && normal.y <= 1
			&& normal.z >= -1 && normal.z <= 1))
		__exit_error("ValueError: Required normal vertor range is [-1 ; 1]\n");
}

int	check_argc(int argc)
{
	return (argc != 2);
}

void	check_file(char *str)
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

void	check_identifier(char *identifier, t_parse *parse)
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
