/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:54:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/13 05:20:33 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

static	t_qua_sol	calculate_quadratic_solution(t_ray r, t_cylinder *cy)
{
	t_qua_sol	solution;
	double		a;
	double		b;
	double		c;
	
	a = pow(r.direction.x, 2) + pow(r.direction.y, 2);
	b = 2 * (r.direction.x * (r.origin.x - cy->center.x) + r.direction.y * (r.origin.y - cy->center.y));
	c = pow(r.origin.x - cy->center.x, 2) + pow(r.origin.y - cy->center.y, 2) - pow(cy->radius, 2);
	
	solution.delta = pow(b, 2) - 4 * a * c;
	if (solution.delta < 0)
		return (solution);
	solution.t1 = (-b - sqrt(solution.delta)) / (2 * a);
	solution.t2 = (-b + sqrt(solution.delta)) / (2 * a);
	return (solution);
}

static bool	get_closet_hit(t_data *data, t_hitrecod *rec, t_cylinder *cy, t_qua_sol solution)
{
	double	hit1;
	double	hit2;

	hit1 = (solution.t1 >= 0 
			&& (solution.t1 * data->r.direction.z + data->r.origin.x >= cy->center.z - cy->height / 2)
			&& (solution.t1 * data->r.direction.z + data->r.origin.x <= cy->center.z + cy->height / 2));
	hit2 = (solution.t2 >= 0
			&& (solution.t2 * data->r.direction.z + data->r.origin.x >= cy->center.z - cy->height / 2)
			&& (solution.t2 * data->r.direction.z + data->r.origin.x <= cy->center.z + cy->height / 2));
	if (hit1 && hit2)
		rec->hit_point_distance = fmin(solution.t1, solution.t2);
	else if (hit1)
		rec->hit_point_distance = solution.t1;
	else if (hit2)
		rec->hit_point_distance = solution.t2;
	else
		return (false);
	return (true);
}

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_cylinder	*cy;
	t_qua_sol	solution;
	bool		hit;

	cy = obj->object;
	solution = calculate_quadratic_solution(data->r, cy);
	if (solution.delta> 0)
	{
		hit = get_closet_hit(data, rec, cy, solution);
		if (!hit)
			return (false);
		rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
		double y = rec->p.z - cy->center.z;
	
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
