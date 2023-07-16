/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:54:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/16 04:22:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

t_qua_sol	calculate_quadratic_cylinder(t_ray r, t_cylinder *cy)
{
	t_qua_sol	solution;
	double		a;
	double		b;
	double		c;

	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	b = 2 * (r.direction.x * (r.origin.x - cy->center.x) + r.direction.z * (r.origin.z - cy->center.z));
	c = pow(r.origin.x - cy->center.x, 2) + pow(r.origin.z - cy->center.z, 2) - pow(cy->radius, 2);
	solution.delta = pow(b, 2) - 4 * a * c;
	if (solution.delta < 0)
		return (solution);
	solution.t1 = (-b - sqrt(solution.delta)) / (2 * a);
	solution.t2 = (-b + sqrt(solution.delta)) / (2 * a);
	return (solution);
}

bool	get_closet_hit(t_ray r, t_hitrecod *rec, t_cylinder *cy, t_qua_sol solution)
{
	double	hit1;
	double	hit2;

	hit1 = (solution.t1 >= 0 
			&& (solution.t1 * r.direction.y + r.origin.y >= cy->center.y - cy->height / 2)
			&& (solution.t1 * r.direction.y + r.origin.y <= cy->center.y + cy->height / 2));
	hit2 = (solution.t2 >= 0
			&& (solution.t2 * r.direction.y + r.origin.y >= cy->center.y - cy->height / 2)
			&& (solution.t2 * r.direction.y + r.origin.y <= cy->center.y + cy->height / 2));
	if (hit1 && hit2)
	{
		if (rec != NULL)
			rec->hit_point_distance = fmin(solution.t1, solution.t2);
	}
	else if (hit1)
	{
		if (rec != NULL)
			rec->hit_point_distance = solution.t1;
	}
	else if (hit2)
	{
		if (rec != NULL)
			rec->hit_point_distance = solution.t2;
	}
	else
		return (false);
	return (true);
}

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_cylinder	*cy;
	t_qua_sol	solution;
	bool		hit;
	t_ray		rotated_ray;
	t_mat4		mat;

	cy = obj->object;
	mat = mat4_rotate(cy->normal);
	rotated_ray.direction = mat4_mult_vect(mat, data->r.direction);
	rotated_ray.origin = mat4_mult_vect(mat, data->r.origin);
	rotated_ray.t_max = data->r.t_max;
	rotated_ray.t_min = data->r.t_min;
	solution = calculate_quadratic_cylinder(rotated_ray, cy);
	if (solution.delta > 0)
	{
		hit = get_closet_hit(rotated_ray, rec, cy, solution);
		if (!hit)
			return (false);
		rec->p = ray_hit_point(&rotated_ray, rec->hit_point_distance);
		double y = rec->p.y - cy->center.y;

		mat = mat4_rotate(vect_scale(cy->normal, -1));
		if (y <= -cy->height / 2 || y >= cy->height / 2)
			rec->normal = vect_normalize(mat4_mult_vect(mat, cy->normal));
		else
			rec->normal = vect_normalize(mat4_mult_vect(mat, vect_unit(vect_sub(vect_sub(rec->p, cy->center), vect_scale(cy->normal, y)))));
		rec->type = CYLINDER;
		rec->color = cy->color;
		rec->obj = obj;
		return (true);
	}
	return (false);
}
