/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/16 04:44:59 by belkarto         ###   ########.fr       */
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
	
	mat = mat4_rotate(cy->normal);//mat4_rotate_y(90 * (M_PI / 180));
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

bool	is_in_shadow(t_data *data, t_hitrecod *rec)
{
	t_vect		ray_to_light;
	t_ray		shadow_ray;
	t_object	*tmp;

	ray_to_light = vect_sub(data->lighting->light->point, rec->p);
	shadow_ray.origin = rec->p;
	shadow_ray.direction = ray_to_light;
	tmp = data->head;
	while (tmp)
	{
		if (tmp == rec->obj)
		{
			tmp = tmp->next;
			continue ;
		}
		if (intesect_shadow(shadow_ray, tmp))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

// calaculate dot product of light and normal
// if dot > 0
// calculate specular and diffuse
// apply specular and diffuse
// apply ambient
// else	
// apply ambient
// end

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

void	calculate_diffuse(t_data *data, t_hitrecod *rec, double dot)
{
	t_color		diffuse;
	t_vect		light_normalized;

	if (rec->type == SPHERE)
	{
		light_normalized = vect_normalize(data->lighting->light->point);
		diffuse = color_scalar(rec->color,
				(dot * data->lighting->light->ratio));
		rec->color = diffuse;
		rec->color = _color_clap(rec->color);
	}
	else if (rec->type == CYLINDER)
	{
		light_normalized = vect_normalize(data->lighting->light->point);
		rec->color = color_scalar(rec->color,
				(dot * data->lighting->light->ratio));
	}
	(void)light_normalized;
}

void	calculate_and_apply_light(t_data *data, t_hitrecod *rec, bool shadow)
{
	double		dot;
	t_vect		light_normalized;

	if (shadow)
	{
		rec->color = color_scalar(rec->color, data->lighting->amb_light->ratio);
		return ;
	}
	light_normalized = vect_normalize(data->lighting->light->point);
	dot = fmax(vect_dot(light_normalized, rec->normal), 0.0);
	calculate_diffuse(data, rec, dot);
}

void	aplly_light(t_data *data, t_hitrecod *rec)
{
	bool	shadow;

	shadow = is_in_shadow(data, rec);
	calculate_and_apply_light(data, rec, shadow);
}
