/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:45:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/26 04:39:54 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	vec_to_color(t_vect color)
{
	t_color tmp;

	tmp.r = color.x;
	tmp.g = color.y;
	tmp.b = color.z;
	return (tmp);
}

t_vect c_to_v(t_color color)
{
	t_vect tmp;

	tmp.x = color.r;
	tmp.y = color.g;
	tmp.z = color.b;
	return (tmp);
}

bool	hit_sphere(t_data *data, t_hitrecod *rec, t_object *obj)
{
	t_vect	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_sphere	*sp;
	/* t_vect		light;
	   double		dot; */

	sp = obj->object;
	oc = vect_sub(data->r.origin, sp->center);
	a = vect_dot(data->r.direction, data->r.direction);
	half_b = vect_dot(oc, data->r.direction);
	c = vect_dot(oc, oc) - sp->radius * sp->radius;
	discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0)
		return (false);
	rec->hit_point_distance = (-half_b - sqrt(discriminant)) / a;
	if (rec->hit_point_distance < data->r.t_min || data->r.t_max < rec->hit_point_distance)
	{
		if (rec->hit_point_distance < data->r.t_min || data->r.t_max < rec->hit_point_distance)
			return (false);
	}
	rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
	rec->normal = vect_scale(vect_sub(rec->p, sp->center), 1 / sp->radius);
	set_face_normal(&data->r, rec);

	/* t_vect		light;
	double		dot;
	double		brightness;
 */
	/* brightness = 1;
	light = vect_normalize(vect_new(1, 1, 1));
	dot = fmax(vect_dot(light, rec->normal), 0.0);
	rec->color = vec_to_color(vect_scale(vect_scale(c_to_v(sp->color), dot), brightness)); */
	return (true);
}
