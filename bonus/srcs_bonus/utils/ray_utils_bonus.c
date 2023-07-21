/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:54:27 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:17:03 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

t_ray	calculate_ray(t_data *data, int x, int y)
{
	data->img.u = (x + ((double)data->img.samples_count / 10))
		/ (data->img.width - 1);
	data->img.v = (data->img.height - y + (double)data->img.samples_count / 10)
		/ (data->img.height - 1);
	return (ray_new(data->camera, data->img.u, data->img.v));
}

t_ray	ray_new(t_camera *cam, double x, double y)
{
	t_ray	ray;
	t_vect	tmp;
	t_vect	tmp2;

	tmp = vect_scale(cam->horizontal, x);
	tmp2 = vect_scale(cam->vertical, y);
	ray.origin = cam->origin;
	ray.direction = vect_add(cam->lower_left_corner, tmp);
	ray.direction = vect_add(ray.direction, tmp2);
	ray.direction = vect_sub(ray.direction, cam->origin);
	return (ray);
}

t_vect	ray_hit_point(t_ray *r, double t)
{
	t_vect	tmp;

	tmp = vect_scale(r->direction, t);
	tmp = vect_add(r->origin, tmp);
	return (tmp);
}

// ray color is function that takes a ray send from camera to a pixel in 
// the screen and return the color of the pixel after the ray hit the object
// in the scene
t_color	ray_color(t_data *data)
{
	t_hitrecod	rec;

	if (hittable_list_hit(data, &rec))
		return (rec.color);
	return (fill_color(20, 20, 20));
}
