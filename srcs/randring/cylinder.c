/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:54:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/08 08:52:52 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	double		discriminant;
	double		a;
	double		b;
	double		c;
	t_cylinder	*cy;

	cy = obj->object;
	a = pow(data->r.direction.x, 2) + pow(data->r.direction.z, 2);
	b = 2 * (data->r.direction.x * (data->r.origin.x - cy->center.x) + data->r.direction.z * (data->r.origin.z - cy->center.z));
	c = pow(data->r.origin.x - cy->center.x, 2) + pow(data->r.origin.z - cy->center.z, 2) - pow(cy->radius, 2);

	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant > 0)
	{
		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);

		bool hit1 = (t1 >= 0 
				&& (t1 * data->r.direction.y + data->r.origin.y >= cy->center.y - cy->height / 2)
				&& (t1 * data->r.direction.y + data->r.origin.y <= cy->center.y + cy->height / 2));

		bool hit2 = (t2 >= 0
				&& (t2 * data->r.direction.y + data->r.origin.y >= cy->center.y - cy->height / 2)
				&& (t2 * data->r.direction.y + data->r.origin.y <= cy->center.y + cy->height / 2));

		if (hit1 && hit2)
			rec->hit_point_distance = fmin(t1, t2);
		else if (hit1)
			rec->hit_point_distance = t1;
		else if (hit2)
			rec->hit_point_distance = t2;
		else
			return (false);
		rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
		double y = rec->p.y - cy->center.y;
	
		if (y <= -cy->height / 2 || y >= cy->height / 2)
			rec->normal = cy->normal;
		else
			rec->normal = vect_unit(vect_sub(vect_sub(rec->p, cy->center), vect_scale(cy->normal, y)));
		rec->type = CYLINDER;
		rec->color = cy->color;
		rec->obj = obj;
		return (true);
	}
	return (false);
}

