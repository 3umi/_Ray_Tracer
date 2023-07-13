/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:14 by brahim            #+#    #+#             */
/*   Updated: 2023/07/13 22:29:49 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
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
# include "../libs/linux/mlx.h"
# include "../libs/libft/libft.h"
# include "vectors.h"
# include "camera.h"
# include "image.h"
# include "colors.h"
# include "ray.h"
# include "lighting.h"
# include "objects.h"
# include "error.h"
# include "errno.h"
# include "linked_list_utils.h"
# include "char_utils.h"
# include "data.h"
# include "hited.h"
# include "parsing.h"
# include "key_hook.h"
# include "matrix.h"

void		rerander(t_data *data);
bool		hit_plane(t_data *r, t_hitrecod *rec, t_object *obj);
t_color		ray_color(t_data *data);
t_color		ambient_light(t_data *data, t_color color);
void		aplly_light(t_data *data, t_hitrecod *rec);
t_ray		calculate_ray(t_data *data, int x, int y);
t_qua_sol	calc_quadratic_sphere(t_ray r, t_sphere *sp);

#endif
