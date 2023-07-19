/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:23:46 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/19 18:27:02 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	ambient_light(t_data *data, t_color color)
{
	double	ratio;
	t_color	tmp;

	ratio = data->lighting->amb_light->ratio;
	tmp = color_scalar(color, ratio);
	if (data->lighting->light->ratio < EPSILON)
		return (tmp);
	if (tmp.r < color.r)
		tmp.r = color.r;
	if (tmp.g < color.g)
		tmp.g = color.g;
	if (tmp.b < color.b)
		tmp.b = color.b;
	return (tmp);
}

t_color	_color_clap(t_color color)
{
	t_color	tmp;

	tmp = color;
	if (tmp.r > 255)
		tmp.r = 255;
	if (tmp.g > 255)
		tmp.g = 255;
	if (tmp.b > 255)
		tmp.b = 255;
	return (tmp);
}

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
