/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:47:01 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/15 12:17:47 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

//left lower corner 
// origin - horizontal/2 - vertical/2 - focal_length
t_camera init_camera(t_vect lookfrom, t_vect lookat, t_vect vup, double fov, double aspect_ratio)
{
	t_camera cam;
	double h;
	t_vect tmp;

	fov = fov * M_PI / 180;
	h = tan(fov / 2);
	cam.aspect_ratio = aspect_ratio;
	cam.viewport_height = 2.0 * h;
	cam.viewport_width = cam.aspect_ratio * cam.viewport_height;
	cam.focal_length = 1.0;

	cam.w = vect_unit(vect_sub(lookfrom, lookat));
	cam.u = vect_unit(vect_cross(vup, cam.w));
	cam.v = vect_cross(cam.w, cam.u);
	cam.origin = lookfrom;
	cam.horizontal = vect_scale(cam.u, cam.viewport_width);
	cam.vertical = vect_scale(cam.v, cam.viewport_height);
	tmp = vect_scale(cam.w, cam.focal_length);
	tmp = vect_sub(cam.origin, tmp);
	tmp = vect_sub(tmp, vect_scale(cam.horizontal, 0.5));
	tmp = vect_sub(tmp, vect_scale(cam.vertical, 0.5));
	cam.lower_left_corner = tmp;
	return (cam);
}
/* cam.origin = vect_new(0, 0, 0);
   cam.horizontal = vect_new(cam.viewport_width, 0, 0);
   cam.vertical = vect_new(0, cam.viewport_height, 0);
   tmp = vect_sub(cam.origin, vect_scale(cam.horizontal, 0.5));
   tmp = vect_sub(tmp, vect_scale(cam.vertical, 0.5));
   tmp = vect_sub(tmp, vect_new(0, 0, cam.focal_length));
   cam.lower_left_corner = tmp; */
// cam.lower_left_corner = vect_sub(cam.origin, vect_scale(cam.horizontal, 0.5));
/* t_camera cam;
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
   return (cam); */
