/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:47:01 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/14 12:32:03 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

//left lower corner 
// origin - horizontal/2 - vertical/2 - focal_length
t_camera init_camera(t_vect origin, t_vect normalized, double fov)
{
	t_camera cam;
	t_vect tmp;

	(void)normalized;
	fov = fov * M_PI / 180;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.origin = origin;
	cam.focal_length = 2.0;
	cam.viewport_width = 2 * tan(fov / 2) * cam.focal_length;
	cam.viewport_height = cam.viewport_width / cam.aspect_ratio;
	cam.horizontal = vect_new(cam.viewport_width, 0, 0);
	cam.vertical = vect_new(0, cam.viewport_height, 0);
	tmp = vect_sub(cam.origin, vect_scale(cam.horizontal, normalized.x));
	tmp = vect_sub(tmp, vect_scale(cam.vertical, normalized.y));
	tmp = vect_sub(tmp, vect_new(0, 0, normalized.z));
	cam.lower_left_corner = tmp;
	return (cam);
}
