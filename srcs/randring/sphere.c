/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:45:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/26 05:47:15 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdlib.h>

t_color	vec_to_color(t_vect color)
{
	t_color tmp;

	tmp.r = color.x;
	tmp.g = color.y;
	tmp.b = color.z;
	return (tmp);
}

t_vect c_to_v(t_color color)
{
	t_vect tmp;

	tmp.x = color.r;
	tmp.y = color.g;
	tmp.z = color.b;
	return (tmp);
}

bool is_shadowed(t_data *data, t_vect point, t_object *obj)
{
	t_ray shadow_ray;
	t_object *obj_tmp;
	shadow_ray.origin = point;
	shadow_ray.direction = vect_sub(data->lighting->light->point, point);

	data->r = shadow_ray;
	obj_tmp = data->object;
	while (obj_tmp)
	{
		if (obj_tmp == obj)
		{
			obj_tmp = obj_tmp->next;
			continue;
		}

		t_hitrecod shadow_rec;
		if (hit(data , &shadow_rec, obj_tmp))
			return true; // Shadow ray intersects another object
		obj_tmp = obj_tmp->next;
	}
	return false; // No object found between the point and light source
}

bool	hit_sphere(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_vect	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_sphere	*sp;
	t_object	*obj_tmp;
	/* t_vect		light;
	   double		dot; */
	double		dot;

	sp = obj->object;
	oc = vect_sub(data->r.origin, sp->center);
	a = vect_dot(data->r.direction, data->r.direction);
	half_b = vect_dot(oc, data->r.direction);
	c = vect_dot(oc, oc) - sp->radius * sp->radius;
	discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0)
		return (false);
	rec->hit_point_distance = (-half_b - sqrt(discriminant)) / a;
	if (rec->hit_point_distance < data->r.t_min || data->r.t_max < rec->hit_point_distance)
	{
		if (rec->hit_point_distance < data->r.t_min || data->r.t_max < rec->hit_point_distance)
			return (false);
	}
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->normal = vect_scale(vect_sub(rec->p, sp->center), 1 / sp->radius);
	set_face_normal(&data->r, rec);

	obj_tmp = data->object;
	while (obj_tmp)
	{
		if (obj_tmp == obj)
		{
			obj_tmp = obj_tmp->next;
			continue;
		}
		if (is_shadowed(data, rec->p, obj_tmp))
		{
			dot = fmax(vect_dot(data->lighting->light->point, rec->normal), 0.0);
			rec->color = vec_to_color(vect_scale(vect_scale(c_to_v(sp->color), dot), 0.2));
			return (false);
		}
		/* light = vect_sub(data->lighting->light->point, rec->p);
		   dot = fmax(vect_dot(rec->normal, light), 0.0);
		   rec->color = vec_to_color(vect_scale(vect_scale(c_to_v(sp->color), dot), data->lighting->light->ratio)); */

		obj_tmp = obj_tmp->next;
	}


	dot = fmax(vect_dot(data->lighting->light->point, rec->normal), 0.0);
	rec->color = vec_to_color(vect_scale(vect_scale(c_to_v(sp->color), dot), data->lighting->light->ratio));
	return (true);
}
