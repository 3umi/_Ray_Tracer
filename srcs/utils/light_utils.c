/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/07 09:32:02 by belkarto         ###   ########.fr       */
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

bool	sphere_shadow(t_ray r, t_sphere *sphere)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	double	t1;

	oc = vect_sub(r.origin, sphere->center);
	a = vect_dot(r.direction, r.direction);
	b = 2 * vect_dot(oc, r.direction);
	c = vect_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t0 = (-b - sqrt(discriminant)) / (2 * a);
	t1 = (-b + sqrt(discriminant)) / (2 * a);

	if (t0 > EPSILON || t1 > EPSILON)
		return (true);
	return (false);
}

bool	intesect_shadow(t_ray r, t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(r, obj->object));
	return (false);
}

bool	is_in_shadow(t_data *data, t_hitrecod *rec)
{
	t_vect ray_to_light;
	t_ray shadow_ray;
	t_object *tmp;

	// ray_to_light = vect_sub(data->lighting->light->point, rec->p);
	ray_to_light = data->lighting->light->point;
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
	return (vect_sub(light, vect_scale(normal, 2 * vect_dot(light, normal))));
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

void	calculate_and_apply_light(t_data *data, t_hitrecod *rec, bool shadow)
{
	double		dot;
	t_vect		light_normalized;
	t_vect		view_dir;

	if (shadow)
	{
		rec->color = color_scalar(rec->color, data->lighting->amb_light->ratio);
		return ;
	}
	light_normalized = vect_normalize(data->lighting->light->point);
	dot = fmax(vect_dot(light_normalized, rec->normal), 0.0);

	view_dir = vect_normalize(vect_sub(data->camera->origin, rec->p));
	if (rec->type == SPHERE)
	{
		/* double		specular;
		t_color		specular_color;

		specular = pow(fmax(vect_dot(vect_reflect(light_normalized, rec->normal), view_dir), 0.0), 32);
		specular_color = color_scalar(data->lighting->light->color, specular);
		specular_color = fill_color(0, 255, 255);
		rec->color = _color_clap(color_add(rec->color, specular_color)); */
		rec->color = color_scalar(rec->color, dot);
		return ;
	}
	rec->color = color_scalar(rec->color, data->lighting->amb_light->ratio);
}

void	aplly_light(t_data *data, t_hitrecod *rec)
{
	bool	shadow;

	shadow = is_in_shadow(data, rec);
	calculate_and_apply_light(data, rec, shadow);
}
