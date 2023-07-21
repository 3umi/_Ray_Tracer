/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:10:49 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

bool	is_in_shadow(t_data *data, t_hitrecod *rec)
{
	t_vect		ray_to_light;
	t_ray		shadow_ray;
	t_object	*tmp;

	ray_to_light = vect_sub(data->lighting->light->point, rec->p);
	shadow_ray.origin = vect_add(rec->p, vect_scale(ray_to_light, EPSILON));
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

t_vect	vect_reflect(t_vect light, t_vect normal)
{
	return (vect_sub(light, vect_scale(normal, 2 * vect_dot(light, normal))));
}

void	calculate_diffuse(t_data *data, t_hitrecod *rec, double dot)
{
	t_color		specular;
	t_vect		reflect;
	double		specular_factor;

	if (dot > rec->light_ratio)
		rec->light_ratio = dot;
	if (rec->type != PLANE && rec->type != TRIANGLE)
	{
		if (data->switches.specular)
		{
			reflect = vect_reflect(vect_normalize(data->lighting->light->point),
					rec->normal);
			specular_factor = pow(fmax(vect_dot(reflect,
							vect_normalize(data->r.direction)), 0.0), 100);
			specular = color_scalar(fill_color(255, 255, 255), specular_factor);
			rec->specular = color_add(rec->specular, specular);
		}
	}
	if (rec->type == TRIANGLE)
	{
		rec->light_ratio = 1;
	}
}

void	calculate_and_apply_light(t_data *data, t_hitrecod *rec, bool shadow)
{
	double		dot;
	t_vect		light_normalized;

	if (shadow)
	{
		rec->shadow_num++;
		rec->shadow_ratio *= data->lighting->amb_light->ratio;
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

	rec->shadow_num = 0;
	tmp = data->lighting->light;
	while (data->lighting->light)
	{
		shadow = is_in_shadow(data, rec);
		calculate_and_apply_light(data, rec, shadow);
		data->lighting->light = data->lighting->light->next;
	}
	data->lighting->light = tmp;
	if (rec->shadow_num > 0)
		rec->color = color_scalar(rec->color, rec->shadow_ratio);
	if (rec->type != PLANE)
	{
		rec->color = color_add(rec->color, rec->specular);
		rec->color = color_scalar(rec->color, rec->light_ratio);
	}
	else
		rec->color = ambient_light(data->lighting, rec->color);
}
