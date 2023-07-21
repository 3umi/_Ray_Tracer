/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:54:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/21 01:52:16 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

t_qua_sol	calculate_quadratic_cylinder(t_ray r, t_cylinder *cy)
{
	t_qua_sol	sol;
	double		a;
	double		b;
	double		c;

	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	b = 2 * (r.direction.x * (r.origin.x - cy->center.x)
			+ r.direction.z * (r.origin.z - cy->center.z));
	c = pow(r.origin.x - cy->center.x, 2) + pow(r.origin.z - cy->center.z, 2)
		- pow(cy->radius, 2);
	sol.delta = pow(b, 2) - 4 * a * c;
	if (sol.delta < 0)
		return (sol);
	sol.t1 = (-b - sqrt(sol.delta)) / (2 * a);
	sol.t2 = (-b + sqrt(sol.delta)) / (2 * a);
	return (sol);
}

bool	does_t(t_ray r, double t, t_cylinder *cy)
{
	return ((t >= 0
			&& (t * r.direction.y + r.origin.y >= cy->center.y - cy->height / 2)
			&& (t * r.direction.y + r.origin.y
				<= cy->center.y + cy->height / 2)));
}

bool	get_closet_hit(t_ray r, t_hitrecod *rec, t_cylinder *cy, t_qua_sol sol)
{
	double	hit1;
	double	hit2;

	hit1 = does_t(r, sol.t1, cy);
	hit2 = does_t(r, sol.t2, cy);
	if (hit1 && hit2)
	{
		if (rec != NULL)
			rec->hit_point_distance = fmin(sol.t1, sol.t2);
	}
	else if (hit1)
	{
		if (rec != NULL)
			rec->hit_point_distance = sol.t1;
	}
	else if (hit2)
	{
		if (rec != NULL)
			rec->hit_point_distance = sol.t2;
	}
	else
		return (false);
	return (true);
}

void	cylinder_gradient(t_hitrecod *rec, t_cylinder *cy)
{
	double	y_dist;
	double	t;

	y_dist = (rec->p.y - cy->center.y) * 2;
	t = (y_dist + cy->radius * 2) / cy->height;
	t = fmin(t, 1);
	t = fmax(t, 0);
	rec->color = gradient(cy->color_b, cy->color_a, t);
}

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_cylinder	*cy;
	t_qua_sol	sol;
	t_ray		rotated_ray;
	t_mat4		mat;

	cy = obj->object;
	mat = mat4_rotate(cy->normal);
	initialize_rotated_ray(&rotated_ray, data->r, mat);
	sol = calculate_quadratic_cylinder(rotated_ray, cy);
	if (sol.delta > 0)
	{
		if (!get_closet_hit(rotated_ray, rec, cy, sol))
			return (false);
		rec->p = ray_hit_point(&rotated_ray, rec->hit_point_distance);
		rec->normal = calculate_normal(rec, cy);
		if (data->switches.cylinder_gradient)
			cylinder_gradient(rec, cy);
		else
			rec->color = cy->color_a;
		rec->type = CYLINDER;
		rec->obj = obj;
		return (true);
	}
	return (false);
}
