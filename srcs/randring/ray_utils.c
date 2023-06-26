/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:40:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/26 04:34:33 by belkarto         ###   ########.fr       */
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

//ray at is used to determine the point at which the ray hits the sphere
t_vect	ray_hit_point(t_ray *r, double t)
{
	return (vect_add(r->origin, vect_scale(r->direction, t)));
}

//set face normal is used to determine if the ray is inside or outside the sphere 
//if the ray is inside the sphere, the normal is inverted 
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

/* t_vect av_color(t_vect color1, t_vect color2)
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
} */



t_vect vect_reflect(t_vect v, t_vect n)
{
	return (vect_sub(v, vect_scale(n, 2 * vect_dot(v, n))));
}

bool	hit(t_data *data, t_hitrecod *rec,	t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(data, rec, obj));
	else if (obj->type == PLANE)
		return (hit_plane(data, rec, obj));
	return (false);
}

bool hittable_list_hit(t_data *data, t_hitrecod *rec)
{
	t_hitrecod	tmp_rec;
	bool		hit_anything;
	t_object	*tmp;

	hit_anything = false;
	tmp = data->object;
	while (tmp)
	{
		if (hit(data, &tmp_rec, tmp))
		{
			hit_anything = true;
			data->r.t_max = tmp_rec.hit_point_distance;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}
