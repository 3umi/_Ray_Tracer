/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:45:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/07 05:16:36 by belkarto         ###   ########.fr       */
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

static double hit_point(t_vect oc, double radius, t_vect direction)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	a = vect_dot(direction, direction);
	half_b = vect_dot(oc, direction);
	c = vect_dot(oc, oc) - radius * radius;
	discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return (- half_b - sqrt(discriminant)) / a;
	return (discriminant);
}

double	color_scale_ratio(double ratio)
{
	if (ratio > 1.0)
		ratio = 1;
	else if (ratio < EPSILON)
		ratio = 0;
	ratio *= 255;
	return (ratio);
}

bool	hit_sphere(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_sphere	*sp;

	sp = obj->object;
	rec->hit_point_distance = hit_point(vect_sub(data->r.origin, sp->center),sp->radius, data->r.direction);
	if (rec->hit_point_distance < data->r.t_min || data->r.t_max < rec->hit_point_distance)
		return (false);
	rec->type = SPHERE;
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	// rec->normal = vect_scale(vect_sub(rec->p, sp->center), 1 / sp->radius);
	rec->normal = vect_sub(rec->p, sp->center);
	rec->normal = vect_normalize(rec->normal);
	rec->obj = obj;
	rec->color = sp->color;
	return (true);
}
