/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/06 18:29:00 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color		ambient_light(t_data *data, t_color color)
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

bool	intesect_shadow(t_ray r, t_object *obj)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	t_sphere	*sphere;

	sphere = obj->object;
	oc = vect_sub(r.origin, sphere->center);
	a = vect_dot(r.direction, r.direction);
	b = 2 * vect_dot(oc, r.direction);
	c = vect_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t0 = (-b - sqrt(discriminant)) / (2 * a);
	if (t0 > 0)
	{
		return (true);
	}
	return (false);
}

bool	is_in_shadow(t_data *data, t_hitrecod *rec)
{
	t_vect ray_to_light;
	t_ray shadow_ray;
	t_object *tmp;

	ray_to_light = vect_sub(data->lighting->light->point, rec->p);
	shadow_ray.origin = rec->p;
	shadow_ray.direction = ray_to_light;
	tmp = data->head;
	while (tmp)
	{
		if (intesect_shadow(shadow_ray, tmp))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	aplly_light(t_data *data, t_hitrecod *rec)
{

	double		dot;
	if (is_in_shadow(data, rec))
		rec->color = color_scalar(rec->color, 0.1);
	if (data->lighting->light->ratio > EPSILON)
	{
		if (rec->type == SPHERE)
		{
			dot = fmax(vect_dot(data->lighting->light->point, rec->normal), 0.0);
			rec->color = color_scalar(rec->color, dot);
		}
		/* else if (rec->type == PLANE)
		{
			dot = fmax(vect_dot(rec->normal, data->lighting->light->point), 1.0);
			rec->color = color_scalar(rec->color, dot);
		} */
	}
	rec->color = ambient_light(data, rec->color);
}
