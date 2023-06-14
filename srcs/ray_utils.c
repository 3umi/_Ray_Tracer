/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/14 08:21:48 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdbool.h>

t_ray ray_new(t_vect origin, t_vect direction)
{
	t_ray ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vect	ray_at(t_ray *r, double t)
{
	return (vect_add(r->origin, vect_scale(r->direction, t)));
}

void set_face_normal(t_ray *r, t_hitrecod *rec)
{
	rec->front_face = vect_dot(r->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vect_scale(rec->normal, -1);
}

//hittable list
//linked list for hittable list
t_sphere	*sphere_new(t_vect center, double radius)
{
	t_sphere *sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	return (sp);
}

bool	hit_sphere(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj)
{
	t_vect	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_sphere	*sp;

	sp = obj->object;
	oc = vect_sub(r->origin, sp->center);
	a = vect_dot(r->direction, r->direction);
	half_b = vect_dot(oc, r->direction);
	c = vect_dot(oc, oc) - sp->radius * sp->radius;
	discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0)
		return (false);
	rec->t = (-half_b - sqrt(discriminant)) / a;
	if (rec->t < t_min || t_max < rec->t)
	{
		rec->t = (-half_b + sqrt(discriminant)) / a;
		if (rec->t < t_min || t_max < rec->t)
			return (false);
	}
	rec->p = ray_at(r, rec->t);
	rec->normal = vect_scale(vect_sub(rec->p, sp->center), 1 / sp->radius);
	set_face_normal(r, rec);
	return (true);
}

bool	hit(t_ray *r, double t_min, double t_max, t_hitrecod *rec,	t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(r, t_min, t_max, rec, obj));
	return (false);
}

bool hittable_list_hit(t_object *list, t_ray *r, double t_min, double t_max, t_hitrecod *rec)
{
	t_hitrecod	tmp_rec;
	bool		hit_anything;
	double		closest_so_far;
	int			i;

	hit_anything = false;
	closest_so_far = t_max;
	i = -1;
	while (list[++i].type != NONE)
	{
		if (hit(r, t_min, closest_so_far, &tmp_rec, &list[i]))
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
	}
	return (hit_anything);
}
