/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:38:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/14 08:53:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct	s_camera
{
	double		aspect_ratio;
	double		viewport_width;
	double		viewport_height;
	double		focal_length;
	t_vect		origin;
	t_vect		lower_left_corner;
	t_vect		horizontal;
	t_vect		vertical;
	t_vect		u;
	t_vect		v;
	t_vect		w;
}				t_camera;

t_camera init_camera(t_vect origin, t_vect normalized, double fov);
#endif
