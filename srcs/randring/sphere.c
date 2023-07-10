/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:45:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/09 11:11:30 by belkarto         ###   ########.fr       */
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

/* static double hit_point(t_vect oc, double radius, t_vect direction)
{
} */
// static t_qua_sol calc_quadratic(t_vect oc, t_vect direction, double radius)
static t_qua_sol calc_quadratic(t_ray r, t_sphere *sp)
{
	double		a;
	double		half_b;
	double		c;
	t_qua_sol	solution;

	a = vect_dot(r.direction, r.direction);
	half_b = vect_dot(vect_sub(r.origin, sp->center), r.direction);
	c = vect_dot(vect_sub(r.origin, sp->center), vect_sub(r.origin, sp->center)) - sp->radius * sp->radius;
	solution.delta = pow(half_b, 2) - a * c;
	if (solution.delta < 0)
		return (solution);
	solution.t1 = (-half_b - sqrt(solution.delta)) / a;
	solution.t2 = (-half_b + sqrt(solution.delta)) / a;
	return (solution);
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
	t_qua_sol	solution;

	sp = obj->object;

	solution = calc_quadratic(data->r, sp);
	if (solution.delta < 0)
		return (false);
	if (solution.t1 < data->r.t_min || data->r.t_max < solution.t1)
		return (false);
	rec->hit_point_distance = solution.t1;
	rec->type = SPHERE;
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	// rec->normal = vect_scale(vect_sub(rec->p, sp->center), 1 / sp->radius);
	rec->normal = vect_sub(rec->p, sp->center);
	rec->normal = vect_normalize(rec->normal);
	rec->obj = obj;
	rec->color = sp->color;
	return (true);
}
