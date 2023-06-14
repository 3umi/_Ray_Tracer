/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:38:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/14 15:46:57 by ohalim           ###   ########.fr       */
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
	double		fov;
	t_vect		origin;
	t_vect		normalized;
	t_vect		lower_left_corner;
	t_vect		horizontal;
	t_vect		vertical;
}				t_camera;

t_camera init_camera(t_vect origin, t_vect normalized, double fov);
#endif
