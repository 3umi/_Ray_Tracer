/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:14:07 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/16 19:18:02 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include <stdbool.h>

typedef struct s_parse
{
	bool	a;
	bool	c;
	bool	l;
}	t_parse;

//--------------------------Check------------------------------//
void	check_normalized_and_color(t_color color_a, t_color color_b,
			t_vect normal);
int		check_argc(int argc);
void	check_file(char *str);
void	check_identifier(char *identifier, t_parse *parse);

//-----------------------Parsing_c------------------------------//
void	parse_ambient_light(t_data *data, char **info);
void	parse_light(t_data *data, char **info);
void	parse_camera(t_data *data, char **info);

//------------------------Parse_env------------------------------//
void	iterate_line(t_data *data, t_parse *parse, char *line);

//----------------------Parse_data------------------------------//
char	**parse_data(char *info);
t_vect	parse_vect(char **info);
t_color	parse_color(char **info);

//-------------------------Parsing------------------------------//
void	cleanse(t_data *data);
char	*free_2d(char **tab);
void	__parsing(int argc, char **argv, t_data *data);
void	__init(t_data *data);

#endif
