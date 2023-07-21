/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:44:32 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 02:56:53 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static bool	is_inside(t_triangle *tr, t_vect p)
{
	t_vect	c;
	t_vect	vp0;
	t_vect	vp1;
	t_vect	vp2;

	vp0 = vect_sub(p, tr->point_a);
	c = vect_cross(tr->edge_ab, vp0);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	vp1 = vect_sub(p, tr->point_b);
	tr->edge_bc = vect_sub(tr->point_c, tr->point_b);
	c = vect_cross(tr->edge_bc, vp1);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	vp2 = vect_sub(p, tr->point_c);
	tr->edge_ac = vect_sub(tr->point_a, tr->point_c);
	c = vect_cross(tr->edge_ac, vp2);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	return (true);
}

bool	hit_triangle(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_triangle	*tr;
	double		normal_dot_ray_dir;
	double		t;
	double		d;
	t_vect		p;

	tr = obj->object;
	tr->edge_ab = vect_sub(tr->point_b, tr->point_a);
	tr->edge_ac = vect_sub(tr->point_c, tr->point_a);
	tr->normalized = vect_cross(tr->edge_ab, tr->edge_ac);
	normal_dot_ray_dir = vect_dot(tr->normalized, data->r.direction);
	if (fabs(normal_dot_ray_dir) < EPSILON)
		return (false);
	d = -vect_dot(tr->normalized, tr->point_a);
	t = -(vect_dot(tr->normalized, data->r.origin) + d) / normal_dot_ray_dir;
	if (t < data->r.t_min || t > data->r.t_max)
		return (false);
	p = vect_add(data->r.origin, vect_scale(data->r.direction, t));
	if (!is_inside(tr, p))
		return (false);
	rec->hit_point_distance = t;
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->normal = vect_scale(tr->normalized, 1);
	rec->color = tr->color_a;
	return (true);
}
