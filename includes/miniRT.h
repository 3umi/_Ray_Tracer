/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:14 by brahim            #+#    #+#             */
/*   Updated: 2023/06/22 18:13:59 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "vectors.h"
# include "camera.h"
# include "image.h"
# include "colors.h"
# include "ray.h"
# include "objects.h"
# include "hited.h"
# include "lighting.h"
# include "error.h"
# include "errno.h"
# include "linked_list_utils.h"
# include "char_utils.h"

# define WIN_W 800
# define WIN_H 400
# define SUCCESS_RETURN 0
# define FAILURE_RETURN 1

typedef struct	s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_object		*object;
	t_camera		*camera;
	t_lighting		*lighting;
	t_img			img;
	int			depth;
}				t_data;

void		rerander(t_data *data);

# include "parsing.h"
# include "key_hook.h"

bool	hit_sphere(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj);
bool	hit_plane(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj);
#endif
