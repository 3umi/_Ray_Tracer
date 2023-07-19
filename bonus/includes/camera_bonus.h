/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:04 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:15:27 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_BONUS_H
# define CAMERA_BONUS_H

# define LOCKED 1
# define UNLOCKED 0

typedef struct s_camera
{
	double		aspect_ratio;
	double		viewport_width;
	double		viewport_height;
	double		focal_length;
	double		fov;
	double		fov_rad;
	t_vect		origin;
	t_vect		lookat;
	t_vect		normalized;
	t_vect		lower_left_corner;
	t_vect		horizontal;
	t_vect		vertical;
	t_vect		u;
	t_vect		v;
	t_vect		w;
	bool		view_lock;
	bool		origin_lock;
}				t_camera;

// t_camera init_camera(t_vect origin, t_vect normalized, double fov);
// t_camera		init_camera(double fov, double aspect_ratio);

void	init_camera(t_camera *camera);
#endif
