/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:45:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 00:10:58 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdlib.h>

t_qua_sol	calc_quadratic_sphere(t_ray r, t_sphere *sp)
{
	double		a;
	double		half_b;
	double		c;
	t_qua_sol	solution;

	a = vect_dot(r.direction, r.direction);
	half_b = vect_dot(vect_sub(r.origin, sp->center), r.direction);
	c = vect_dot(vect_sub(r.origin, sp->center),
			vect_sub(r.origin, sp->center)) - sp->radius * sp->radius;
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
	solution = calc_quadratic_sphere(data->r, sp);
	if (solution.delta < 0)
		return (false);
	if (solution.t1 < data->r.t_min || data->r.t_max < solution.t1)
		return (false);
	rec->hit_point_distance = solution.t1;
	rec->type = SPHERE;
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->normal = vect_normalize(vect_sub(rec->p, sp->center));
	rec->normal = vect_normalize(rec->normal);
	rec->obj = obj;
	rec->color = sp->color;
	return (true);
}
