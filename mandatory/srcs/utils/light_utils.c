/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 18:25:06 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	if (dot < data->lighting->amb_light->ratio)
		dot = data->lighting->amb_light->ratio;
	calculate_diffuse(data, rec, dot);
}

void	aplly_light(t_data *data, t_hitrecod *rec)
{
	bool	shadow;

	shadow = is_in_shadow(data, rec);
	calculate_and_apply_light(data, rec, shadow);
}
