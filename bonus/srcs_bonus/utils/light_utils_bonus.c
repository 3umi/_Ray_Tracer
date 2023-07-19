/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 06:43:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 08:49:06 by soran            ###   ########.fr       */
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

bool	triangle_shadow(t_ray r, t_triangle *tr)
{	
	t_vect edge0;
	t_vect edge1;
	double normal_dot_ray_dir;
	double t;

	edge0 = vect_sub(tr->point_b, tr->point_a);
	edge1 = vect_sub(tr->point_c, tr->point_a);

	tr->normalized = vect_cross(edge0, edge1);

	normal_dot_ray_dir = vect_dot(tr->normalized, r.direction);
	// check if ray and plane are parallel
	if (fabs(normal_dot_ray_dir) < EPSILON)
		return (false);
	double d = -vect_dot(tr->normalized, tr->point_a);

	t = -(vect_dot(tr->normalized, r.origin) + d) / normal_dot_ray_dir;

	t_vect p;
	p = vect_add(r.origin, vect_scale(r.direction, t));

	// check if p inside triangle
	t_vect c;
	t_vect vp0;
	vp0 = vect_sub(p, tr->point_a);
	c = vect_cross(edge0, vp0);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	t_vect vp1;
	vp1 = vect_sub(p, tr->point_b);
	edge0 = vect_sub(tr->point_c, tr->point_b);
	c = vect_cross(edge0, vp1);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	t_vect vp2;
	vp2 = vect_sub(p, tr->point_c);
	edge0 = vect_sub(tr->point_a, tr->point_c);
	c = vect_cross(edge0, vp2);
	if (vect_dot(tr->normalized, c) < 0)
		return (false);
	return (true);
}

bool	intesect_shadow(t_ray r, t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(r, obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_shadow(r, obj->object));
	else if (obj->type == TRIANGLE)
		return (triangle_shadow(r, obj->object));
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
	av_color(&rec->light_color, data->lighting->light->color);
	if (rec->type != PLANE && rec->type != TRIANGLE)
	{
		if (data->switches.specular)
		{
			reflect = vect_reflect(vect_normalize(data->lighting->light->point), rec->normal);
			specular_factor = pow(fmax(vect_dot(reflect, vect_normalize(data->r.direction)), 0.0), 32);
			specular = color_scalar(data->lighting->light->color, specular_factor);
			rec->specular = color_add(rec->specular, specular);
		}
	}
}
void	calculate_and_apply_light(t_data *data, t_hitrecod *rec, bool shadow)
{
	double		dot;
	t_vect		light_normalized;

	if (shadow)
	{
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

	rec->light_color = fill_color(255, 255, 255);
		tmp = data->lighting->light;
	while (data->lighting->light)
	{
		// printf("light ratio %f %f \n", data->lighting->light->ratio, 
		shadow = is_in_shadow(data, rec);
		calculate_and_apply_light(data, rec, shadow);
		data->lighting->light = data->lighting->light->next;
	}
	rec->color = color_scalar(rec->color, rec->shadow_ratio);
	av_color(&rec->color, rec->light_color);
	if (rec->type != PLANE && rec->type != TRIANGLE)
	{
		rec->color = color_add(rec->color, rec->specular);
		rec->color = color_scalar(rec->color, rec->light_ratio);
	}
	rec->color = _color_clap(rec->color);
	data->lighting->light = tmp;
}
