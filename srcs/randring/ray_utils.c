/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/18 15:08:42 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdbool.h>

t_ray ray_new(t_camera * cam, double x, double y)
{
	t_ray ray;
	t_vect tmp;
	t_vect tmp2;

	tmp = vect_scale(cam->horizontal, x);
	tmp2 = vect_scale(cam->vertical, y);
	ray.origin = cam->origin;
	ray.direction = vect_add(cam->lower_left_corner, tmp);
	ray.direction = vect_add(ray.direction, tmp2);
	ray.direction = vect_sub(ray.direction, cam->origin);
	/* t_ray ray;

	   ray.origin = origin;
	   ray.direction = direction; */
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

t_vect av_color(t_vect color1, t_vect color2)
{
	t_vect tmp;

	if (color1.x == 0 && color1.y == 0 && color1.z == 0)
		return (color2);
	if (color2.x == 0 && color2.y == 0 && color2.z == 0)
		return (color1);
	tmp.x = (color1.x + color2.x) / 2;
	tmp.y = (color1.y + color2.y) / 2;
	tmp.z = (color1.z + color2.z) / 2;
	return (tmp);
}

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
bool	hit_sphere(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj)
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

	t_vect		light;
	double		dot;
	double		brightness;

	brightness = 1;
	light = vect_normalize(vect_new(1, 1, 1));
	dot = fmax(vect_dot(light, rec->normal), 0.0);
	rec->color = vec_to_color(vect_scale(vect_scale(c_to_v(sp->color), dot), brightness));
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
	t_object	*tmp;

	hit_anything = false;
	closest_so_far = t_max;
	tmp_rec.color_set = false;
	tmp = list;
	while (tmp)
	{
		if (hit(r, t_min, closest_so_far, &tmp_rec, tmp))
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}
