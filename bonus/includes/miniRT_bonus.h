/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:06:56 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 22:29:12 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# define WIN_W 1024
# define SUCCESS_RETURN 0
# define FAILURE_RETURN 1
# define EPSILON 1e-6
# define MAX_DEPTH 50

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "../libs/linux/mlx.h"
# include "../libs/libft/libft.h"
# include "vectors_bonus.h"
# include "camera_bonus.h"
# include "image_bonus.h"
# include "colors_bonus.h"
# include "ray_bonus.h"
# include "lighting_bonus.h"
# include "objects_bonus.h"
# include "error_bonus.h"
# include "linked_list_utils_bonus.h"
# include "char_utils_bonus.h"
# include "data_bonus.h"
# include "hited_bonus.h"
# include "parsing_bonus.h"
# include "key_hook_bonus.h"
# include "matrix_bonus.h"

void		rerander(t_data *data);
bool		hit_plane(t_data *r, t_hitrecod *rec, t_object *obj);
t_color		ray_color(t_data *data);
t_color		ambient_light(t_data *data, t_color color);
void		aplly_light(t_data *data, t_hitrecod *rec);
t_ray		calculate_ray(t_data *data, int x, int y);
t_qua_sol	calc_quadratic_sphere(t_ray r, t_sphere *sp);

#endif
