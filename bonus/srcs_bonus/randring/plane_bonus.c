/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:12:40 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/14 06:52:30 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static t_color	checkboard_plane(t_plane *plane, t_vect p)
{
	t_color		color;
	double		sines;

	sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
	if (sines < 0)
		color = plane->color;
	else
		color = fill_color(20, 20, 100);
	return (color);
}

bool	hit_plane(t_data *data, t_hitrecod *rec, t_object *obj)
{
	double	denom;
	t_plane	*plane;

	plane = obj->object;
	plane->normal = vect_normalize(plane->normal);
	denom = vect_dot(plane->normal, data->r.direction);
	if (fabs(denom) < EPSILON || denom > 0)
		return (false);
	rec->hit_point_distance = vect_dot(vect_sub(plane->point, data->r.origin),
			plane->normal) / denom;
	if (rec->hit_point_distance < data->r.t_min
		|| rec->hit_point_distance > data->r.t_max)
		return (false);
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->type = PLANE;
	rec->normal = plane->normal;
	rec->obj = obj;
	if (data->switches.checkboard_plane)
		rec->color = checkboard_plane(plane, rec->p);
	else
		rec->color = plane->color;
	// rec->color = plane->color;
	return (true);
}
