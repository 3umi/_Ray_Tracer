/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:12:40 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/23 19:34:57 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// p(t) = p0 + t*v
// t = (a - p0) * n / v * n
// a = point on plane
// p0 = origin of ray
// v = direction of ray 
// n = normal of plane 
// t = distance from origin to plane 
/*
static t_color	vec_to_color(t_vect color)
{
	t_color tmp;

	tmp.r = color.x;
	tmp.g = color.y;
	tmp.b = color.z;
	return (tmp);
}

static t_vect c_to_v(t_color color)
{
	t_vect tmp;

	tmp.x = color.r;
	tmp.y = color.g;
	tmp.z = color.b;
	return (tmp);
} */
bool hit_plane(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj)
{
	t_plane	*pl;
	double	denom;
	double	t;
	// t_vect	p;

	pl = obj->object;
	r->direction = vect_normalize(r->direction);
	r->origin = vect_normalize(r->origin);
	pl->normal = vect_negate(pl->normal);
	denom = vect_dot(pl->normal, r->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	/* if (denom > 0)
		return (false); */
	t = vect_dot(vect_sub(pl->point, r->origin), pl->normal) / denom;
	if (t < t_min || t > t_max)
		return (false);
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->normal = pl->normal;
	rec->color = pl->color;
/* 	
	t_vect light = vect_normalize(vect_new(1, 1, 1));
	double dot = fmax(vect_dot(rec->normal, light), 0.0);
	rec->color = c_to_v(vec_to_color(vect_scale(rec->color, dot))); */
	return (true);
}
