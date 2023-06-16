/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/15 18:09:52 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
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

bool	hit_sphere(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj)
{
	t_vect	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_sphere	*sp;
	t_vect		light;
	double		dot;

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



	light = vect_normalize(vect_new(1, 1, 1));
	   dot = fmax(vect_dot(light, rec->normal), 0.0);
	   double light_brightness = 1;
	   if (rec->color_set == false)
	   {
	   rec->color = vect_new(1, 0, 1);
	   rec->color = vect_scale(rec->color, dot);
	   rec->color = vect_scale(rec->color, light_brightness);
	   rec->color_set = true;
	   }
	/* light = vect_normalize(vect_new(1, 1, 1));
	dot = fmax(vect_dot(light, rec->normal), 0.0);
	double light_brightness = 0; // Adjust the light brightness factor as desired
	t_vect light_color = vect_new(0, 0, 1.0); // Set the light color as desired
	double ambient_brightness = 1; // Adjust the ambient brightness factor as desired
	if (rec->color_set == false)
	{
		// Ambient lighting
		t_vect ambient_color = vect_new(1, 1, 1); // Adjust the ambient color as desired

		// Scale the ambient color by the ambient brightness factor
		ambient_color = vect_scale(ambient_color, ambient_brightness);

		t_vect material_color = vect_new(1, 0, 0.5); // Assuming the material color is set to purple

		// Compute the final color by adding ambient, diffuse, and light components
		t_vect diffuse_color = vect_scale(material_color, dot);
		t_vect light_component = vect_scale(light_color, light_brightness);
		t_vect light_colorized = vect_mult(diffuse_color, light_component);
		rec->color = vect_add(ambient_color, light_colorized);

		rec->color_set = true;
	} */

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
	tmp_rec.color_set = false;
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
