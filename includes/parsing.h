/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:52:28 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/17 10:48:19 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>

typedef struct	s_parse
{
	bool	A;
	bool	C;
	bool	L;
}	t_parse;

//----------------------Parsing_b------------------------------//
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
void	__parsing(int argc, char **argv, t_data *data);
void	__init(t_data *data);

#endif
