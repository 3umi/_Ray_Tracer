/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:14:07 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:17:38 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include <stdbool.h>

typedef struct s_parse
{
	bool	A;
	bool	C;
	bool	L;
}	t_parse;

//----------------------Parsing_b------------------------------//
void	check_color(t_color color);
void	check_normalized(t_vect normal);
int		check_argc(int argc);
void	check_file(char *str);
void	check_identifier(char *identifier, t_parse *parse);

//----------------------Parsing_c------------------------------//
void	parse_ambient_light(t_data *data, char **info);
void	parse_light(t_data *data, char **info);
void	parse_camera(t_data *data, char **info);

//----------------------Parsing_d------------------------------//
void	iterate_line(t_data *data, t_parse *parse, char *line);

//----------------------Parsing------------------------------//
void	cleanse(t_data *data);
char	*free_2d(char **tab);
void	__parsing(int argc, char **argv, t_data *data);
void	__init(t_data *data);

#endif
