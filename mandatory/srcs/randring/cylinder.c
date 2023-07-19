/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:54:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/19 18:06:06 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_qua_sol	calculate_quadratic_cylinder(t_ray r, t_cylinder *cy)
{
	t_qua_sol	solution;
	double		a;
	double		b;
	double		c;

	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	b = 2 * (r.direction.x * (r.origin.x - cy->center.x)
			+ r.direction.z * (r.origin.z - cy->center.z));
	c = pow(r.origin.x - cy->center.x, 2) + pow(r.origin.z - cy->center.z, 2)
		- pow(cy->radius, 2);
	solution.delta = pow(b, 2) - 4 * a * c;
	if (solution.delta < 0)
		return (solution);
	solution.t1 = (-b - sqrt(solution.delta)) / (2 * a);
	solution.t2 = (-b + sqrt(solution.delta)) / (2 * a);
	return (solution);
}

bool	get_closet_hit(t_ray r, t_hitrecod *rec, t_cylinder *cy, t_qua_sol s)
{
	double	hit1;
	double	hit2;

	hit1 = does_t(r, s.t1, cy);
	hit2 = does_t(r, s.t2, cy);
	if (hit1 && hit2)
	{
		if (rec != NULL)
			rec->hit_point_distance = fmin(s.t1, s.t2);
	}
	else if (hit1)
	{
		if (rec != NULL)
			rec->hit_point_distance = s.t1;
	}
	else if (hit2)
	{
		if (rec != NULL)
			rec->hit_point_distance = s.t2;
	}
	else
		return (false);
	return (true);
}

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_cylinder	*cy;
	t_qua_sol	solution;
	t_ray		rotated_ray;
	t_mat4		mat;
	double		y;

	cy = obj->object;
	mat = mat4_rotate(cy->normal);
	initialize_rotated_ray(&rotated_ray, data->r, mat);
	solution = calculate_quadratic_cylinder(rotated_ray, cy);
	if (solution.delta <= 0)
		return (false);
	if (!get_closet_hit(rotated_ray, rec, cy, solution))
		return (false);
	rec->p = ray_hit_point(&rotated_ray, rec->hit_point_distance);
	y = rec->p.y - cy->center.y;
	mat = mat4_rotate(vect_scale(cy->normal, -1));
	rec->normal = calculate_normal(rec, cy, mat, y);
	rec->type = CYLINDER;
	rec->color = cy->color;
	rec->obj = obj;
	return (true);
}
