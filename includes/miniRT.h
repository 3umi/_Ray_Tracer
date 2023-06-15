/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:14 by brahim            #+#    #+#             */
/*   Updated: 2023/06/15 23:44:39 by brahim           ###   ########.fr       */
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
# include "ray.h"
# include "objects.h"
# include "hited.h"
# include "lighting.h"
# include "error.h"
# include "errno.h"

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
}				t_data;

void		rerander(t_data *data);

# include "parsing.h"
# include "key_hook.h"

#endif
