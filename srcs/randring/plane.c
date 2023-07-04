/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:12:40 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/03 22:09:53 by belkarto         ###   ########.fr       */
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
bool hit_plane(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_plane	*pl;
	double	denom;
	double	t;
	// t_vect	p;

	pl = obj->object;
	pl->normal = vect_normalize(pl->normal);
	denom = vect_dot(pl->normal, data->r.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vect_dot(vect_sub(pl->point, data->r.origin), pl->normal) / denom;
	if (t < data->r.t_min || t > data->r.t_max)
		return (false);
	rec->hit_point_distance = t;
	rec->p = ray_hit_point(&data->r, t);
	rec->type = PLANE;


	rec->normal = pl->normal;
	rec->color = pl->color;
	/* dot = fmax(vect_dot(rec->normal, data->lighting->light->point), 0);
	rec->color = color_scalar(rec->color, dot); */
	return (true);
}
