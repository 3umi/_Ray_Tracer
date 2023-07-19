/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:14 by brahim            #+#    #+#             */
/*   Updated: 2023/07/19 21:59:53 by ohalim           ###   ########.fr       */
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
# include "objects.h"
# include "error.h"
# include "errno.h"
# include "linked_list_utils.h"
# include "char_utils.h"
# include "lighting.h"
# include "data.h"
# include "hited.h"
# include "parsing.h"
# include "key_hook.h"
# include "matrix.h"

void		rerander(t_data *data);
void		aplly_light(t_data *data, t_hitrecod *rec);
void		initialize_rotated_ray(t_ray *rotated_ray, t_ray r, t_mat4 mat);

bool		hit_plane(t_data *r, t_hitrecod *rec, t_object *obj);
bool		get_closet_hit(t_ray r, t_hitrecod *rec, t_cylinder *cy,
				t_qua_sol solution);
bool		does_t(t_ray r, double t, t_cylinder *cy);
bool		sphere_shadow(t_ray r, t_sphere *sphere);
bool		cylinder_shadow(t_ray r, t_cylinder *cy);
bool		intesect_shadow(t_ray r, t_object *obj);

t_color		ray_color(t_data *data);
t_color		ambient_light(t_data *data, t_color color);
t_color		ambient_light(t_data *data, t_color color);
t_color		_color_clap(t_color color);

t_qua_sol	calc_quadratic_sphere(t_ray r, t_sphere *sp);
t_qua_sol	calculate_quadratic_cylinder(t_ray r, t_cylinder *cy);

t_vect		calculate_normal(t_hitrecod *rec, t_cylinder *cy,
				t_mat4 mat, double y);

t_ray		calculate_ray(t_data *data, int x, int y);
#endif
