/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:44:32 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/18 17:02:39 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

bool	hit_triangle(t_data *data, t_hitrecod *rec, t_object *obj)
{
	//compute the plane normal
	t_triangle *tr;
	
	tr = obj->object;
	t_vect v0v1;
	t_vect v0v2;
	t_vect normal;
	double area;
	double t;
	// print stuff 
	//printf("%f %f %f \n", tr->point_c.x, tr->point_c.y, tr->point_c.z);
	v0v1 = vect_sub(tr->point_b, tr->point_a);
	v0v2 = vect_sub(tr->point_c, tr->point_a);
	normal = vect_cross(v0v1, v0v2);
	area = vect_length(normal);

	//find p
	double dot;

	dot = vect_dot(normal, data->r.direction);
	if (fabs(dot) < EPSILON)
		return (false);
	t = vect_dot(vect_sub(tr->point_a, data->r.origin), normal) / dot;
	if (t < data->r.t_min || t > data->r.t_max)
		return (false);
	//find the intersection point
	t_vect p;
	p = vect_add(data->r.origin, vect_scale(data->r.direction, t));
	t_vect c;
	t_vect vp0;

	vp0 = vect_sub(p, tr->point_a);
	c = vect_cross(v0v1, vp0);
	if (vect_dot(normal, c) < 0)
		return (false);
	t_vect vp1;

	//v0v2 = vect_sub(v2, v0);
	vp1 = vect_sub(p, tr->point_b);
	c = vect_cross(v0v2, vp1);
	if (vect_dot(normal, c) < 0)
		return (false);

	t_vect v1v2;
	t_vect vp2;

	v1v2 = vect_sub(tr->point_a, tr->point_b);
	vp2 = vect_sub(p, tr->point_c);
	c = vect_cross(v1v2, vp2);
	if (vect_dot(normal, c) < 0)
		return (false);

	//find the uv coordinates
	double u;
	double v;
	u = vect_dot(v0v1, vp0) / area;
	v = vect_dot(v0v2, vp0) / area;
	if (u < 0 || u > 1)
		return (false);
	if (v < 0 || v > 1)
		return (false);
	if (u + v > 1)
		return (false);
	//fill the hit record
	rec->hit_point_distance = t;
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->normal = normal;
	rec->color = fill_color(0xFF, 0, 0);
	(void)obj;
	return (true);
}
