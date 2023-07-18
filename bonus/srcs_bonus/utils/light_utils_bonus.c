/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/18 22:57:29 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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

t_vect	vect_reflect(t_vect light, t_vect normal)
{
	// t_vect	normalized;

	/* normalized = vect_normalize(normal);
	   normalized = vect_scale(normalized, 2 * vect_dot(light, normalized));
	// normalized = vect_normalize(normalized);
	return (normalized);
	// return (vect_sub(light, vect_scale(normalized, 2 * vect_dot(light, normalized)))); */
	return (vect_sub(light, vect_scale(normal, 2 * vect_dot(light, normal))));
}

t_color	color_merge(t_color c1, t_color c2)
{
	t_color	tmp;

	tmp.r = c1.r + c2.r / 2;
	tmp.g = c1.g + c2.g / 2;
	tmp.b = c1.b + c2.b / 2;
	return (tmp);
}

void	calculate_diffuse(t_data *data, t_hitrecod *rec, double dot)
{
	// t_color		diffuse;
	t_color		specular;
	// t_vect		light_normalized;
	t_vect		reflect;
	double		specular_factor;

	if (dot > rec->light_ratio)
		rec->light_ratio = dot;
	if (rec->type != PLANE && rec->type != TRIANGLE)
	{
		// diffuse = color_scalar(rec->color, (dot));
		if (data->switches.specular)
		{
			reflect = vect_reflect(vect_normalize(data->lighting->light->point), rec->normal);
			specular_factor = pow(fmax(vect_dot(reflect, vect_normalize(data->r.direction)), 0.0), 32);
			specular = color_scalar(data->lighting->light->color, specular_factor);
			rec->specular = color_add(rec->specular, specular);
			// rec->color = color_add(diffuse, specular);
		}
		/* else
		   rec->color = diffuse; */
	}
	// av_color(&rec->color, data->lighting->light->color);
	// rec->color = _color_clap(rec->color);
}
void	calculate_and_apply_light(t_data *data, t_hitrecod *rec, bool shadow)
{
	double		dot;
	t_vect		light_normalized;

	if (shadow)
	{
		rec->shadow_ratio *= data->lighting->amb_light->ratio;
		// rec->color = color_scalar(rec->color, data->lighting->amb_light->ratio);
		return ;
	}
	light_normalized = vect_normalize(data->lighting->light->point);
	dot = fmax(vect_dot(light_normalized, rec->normal), 0.0);
	if (dot < data->lighting->amb_light->ratio)
		dot = data->lighting->amb_light->ratio;
	calculate_diffuse(data, rec, dot);
}

void	aplly_light(t_data *data, t_hitrecod *rec)
{
	bool	shadow;
	t_light	*tmp;

	rec->shadow_ratio = 1;
	rec->light_ratio = 0;
	rec->specular = fill_color(0, 0, 0);
	tmp = data->lighting->light;
	while (data->lighting->light)
	{
		shadow = is_in_shadow(data, rec);
		calculate_and_apply_light(data, rec, shadow);
		data->lighting->light = data->lighting->light->next;
	}
	rec->color = color_scalar(rec->color, rec->shadow_ratio);
	if (rec->type != PLANE && rec->type != TRIANGLE)
	{
		rec->color = color_add(rec->color, rec->specular);
		rec->color = color_scalar(rec->color, rec->light_ratio);
		rec->color = _color_clap(rec->color);
	}
	data->lighting->light = tmp;
}
