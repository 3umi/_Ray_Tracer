/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/05 09:51:55 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	get_pixel_color(t_data *data, int x, int y)
{
	t_img	*img;
	char	*dst;
	int		color;
	img = &data->img;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (fill_color((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF));
}

t_ray	comput_primary_ray(t_data *data, int x, int y)
{
	t_ray	r;

	double	aspec_ratio;
	double	half_width;
	double	half_height;

	double	pixel_norm_x;
	double	pixel_norm_y;

	aspec_ratio = (double)data->img.width / (double)data->img.height;
	half_width = tan(M_PI / 4);
	half_height = half_width / aspec_ratio;

	pixel_norm_x = (2 * ((x + 0.5) / data->img.width) - 1) * half_width;
	pixel_norm_y = (1 - 2 * ((y + 0.5) / data->img.height)) * half_height;

	r.origin = data->camera->origin;
	r.direction = vect_normalize(vect_new(pixel_norm_x, pixel_norm_y, -1));
	return (r);
}

bool	intersect_sphere(t_ray r, t_object *obj, t_vect *hit_point, t_vect *hit_normal, t_color *color)
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
		*hit_point = vect_add(r.origin, vect_scale(r.direction, t0));
		*hit_normal = vect_sub(*hit_point, sphere->center);
		*hit_normal = vect_scale(*hit_normal, 1 / vect_length(*hit_normal));
		*color = sphere->color;
		return (true);
	}
	return (false);
}

bool	intersect(t_ray r, t_object *obj, t_vect *hit_point, t_vect *hit_normal, t_color *color)
{
	if (obj->type == SPHERE)
		return (intersect_sphere(r, obj, hit_point, hit_normal, color));
	return (false);
}

double	distance(t_vect a, t_vect b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
}

bool	intersect_shadow(t_ray r, t_object *obj)
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

t_color	cast_ray(t_data *data)
{
	double	min_dist;
	t_object	*obj;
	t_vect	hit_point;
	t_vect	hit_normal;
	t_color	color;
	double	t;
	t_vect	eye_pos;

	eye_pos = vect_new(0, 0, 2);
	color = fill_color(0, 0, 0);
	min_dist = INFINITY;
	obj = NULL;
	data->object = data->head;
	while (data->object)
	{
		if (intersect(data->r, data->object, &hit_point, &hit_normal, &color))
		{
			t = distance(eye_pos, hit_point);
			if (t < min_dist)
			{
				min_dist = t;
				obj = data->object;
			}
		}
		data->object = data->object->next;
	}
	bool	is_shadow;
	is_shadow = false;
	if (obj != NULL)
	{
		t_ray	shadow_ray;
		t_object	*shadow_obj;

		shadow_obj = data->head;
		shadow_ray.origin = hit_point;
		shadow_ray.direction = vect_sub(data->lighting->light->point, hit_point);
		while (shadow_obj)
		{
			if (intersect_shadow(shadow_ray, shadow_obj))
			{
				is_shadow = true;
				break ;
			}
			shadow_obj = shadow_obj->next;
		}
	}
	if (is_shadow == true)
	{
		color = fill_color(0, 0, 0);
	}
	return (color);
}

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.r;
	g = (int)color.g;
	b = (int)color.b;
	return (r << 16 | g << 8 | b);
}

void	__draw(t_data *data)
{
	int	x;
	int	y;
	t_color	color;

	init_camera(data->camera);
	y = -1;
	while (++y < data->img.height)
	{
		x = -1;
		while (++x < data->img.width)
		{
			//compute primary ray
			data->r = comput_primary_ray(data, x, y);
			//cast ray in the scene and search for intersection
			color = cast_ray(data);
			//put pixel in the image
			my_mlx_pixel_put(&data->img, x, y, color_to_int(color));
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	__parsing(argc, argv, &data);
	__init(&data);
	__draw(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_loop(data.mlx_ptr);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_key_hook(data.win_ptr, lock_key_hook, &data);
	return (0);

}
