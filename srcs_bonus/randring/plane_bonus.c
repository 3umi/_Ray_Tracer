/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:12:40 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/12 23:35:22 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	rec->color = plane->color;
	rec->obj = obj;
	return (true);
}
