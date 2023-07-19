/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:44:32 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 07:44:14 by soran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

bool	hit_triangle(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_triangle *tr;

	tr = obj->object;
	t_vect edge0;
	t_vect edge1;
	double normal_dot_ray_dir;
	double t;

	edge0 = vect_sub(tr->point_b, tr->point_a);
	edge1 = vect_sub(tr->point_c, tr->point_a);

	tr->normalized = vect_cross(edge0, edge1);

	normal_dot_ray_dir = vect_dot(tr->normalized, data->r.direction);
	// check if ray and plane are parallel
	if (fabs(normal_dot_ray_dir) < EPSILON)
		return (false);
	double d = -vect_dot(tr->normalized, tr->point_a);

	t = -(vect_dot(tr->normalized, data->r.origin) + d) / normal_dot_ray_dir;

	if (t < data->r.t_min || t > data->r.t_max)
		return (false);
	t_vect p;
	p = vect_add(data->r.origin, vect_scale(data->r.direction, t));

	// check if p inside triangle
	t_vect c;
	t_vect vp0;
	vp0 = vect_sub(p, tr->point_a);
	c = vect_cross(edge0, vp0);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	t_vect vp1;
	vp1 = vect_sub(p, tr->point_b);
	edge0 = vect_sub(tr->point_c, tr->point_b);
	c = vect_cross(edge0, vp1);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	t_vect vp2;
	vp2 = vect_sub(p, tr->point_c);
	edge0 = vect_sub(tr->point_a, tr->point_c);
	c = vect_cross(edge0, vp2);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	rec->hit_point_distance = t;
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->normal = vect_scale(tr->normalized, -1);
	rec->color = tr->color_a;
	return (true);
}
