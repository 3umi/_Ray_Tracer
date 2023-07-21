/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:05:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:05:46 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

bool	sphere_shadow(t_ray r, t_sphere *sphere)
{
	t_qua_sol	solution;

	solution = calc_quadratic_sphere(r, sphere);
	if (solution.delta < 0)
		return (false);
	if (solution.t1 > EPSILON || solution.t2 > EPSILON)
		return (true);
	return (false);
}

bool	cylinder_shadow(t_ray r, t_cylinder *cy)
{
	t_qua_sol	solution;
	bool		hit;
	t_ray		rotated_ray;
	t_mat4		mat;

	mat = mat4_rotate(cy->normal);
	rotated_ray.direction = mat4_mult_vect(mat, r.direction);
	rotated_ray.origin = mat4_mult_vect(mat, r.origin);
	rotated_ray.t_max = r.t_max;
	rotated_ray.t_min = r.t_min;
	solution = calculate_quadratic_cylinder(rotated_ray, cy);
	if (solution.delta > 0)
	{
		hit = get_closet_hit(rotated_ray, NULL, cy, solution);
		if (!hit)
			return (false);
		return (true);
	}
	return (false);
}

bool	intesect_shadow(t_ray r, t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(r, obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_shadow(r, obj->object));
	return (false);
}
