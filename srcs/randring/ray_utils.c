/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/09 08:42:53 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdbool.h>

t_ray ray_new(t_camera * cam, double x, double y)
{
	t_ray ray;
	t_vect tmp;
	t_vect tmp2;

	tmp = vect_scale(cam->horizontal, x);
	tmp2 = vect_scale(cam->vertical, y);
	ray.origin = cam->origin;
	ray.direction = vect_add(cam->lower_left_corner, tmp);
	ray.direction = vect_add(ray.direction, tmp2);
	ray.direction = vect_sub(ray.direction, cam->origin);
	return (ray);
}

//ray at is used to determine the point at which the ray hits the sphere
t_vect	ray_hit_point(t_ray *r, double t)
{
	t_vect tmp;

	tmp = vect_scale(r->direction, t);
	tmp = vect_add(r->origin, tmp);
	return (tmp);
}

//hittable list
//linked list for hittable list

bool	hit(t_data *data, t_hitrecod *rec,	t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(data, rec, obj));
	else if (obj->type == PLANE)
		return (hit_plane(data, rec, obj));
	else if (obj->type == CYLINDER)
		return (hit_cylinder(data, rec, obj));
	return (false);
}

bool hittable_list_hit(t_data *data, t_hitrecod *rec)
{
	t_hitrecod	tmp_rec;
	bool		hit_anything;

	hit_anything = false;
	data->r.t_max = INFINITY;
	data->r.t_min = EPSILON;
	tmp_rec.hit_point_distance = data->r.t_max;
	while (data->object)
	{
		if (hit(data, &tmp_rec, data->object))
		{
			hit_anything = true;
			data->r.t_max = tmp_rec.hit_point_distance;
			*rec = tmp_rec;
		}
		data->object = data->object->next;
	}
	data->object = data->head;
	if (hit_anything == true)
		aplly_light(data, rec);
	return (hit_anything);
}
