/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/04 18:52:21 by belkarto         ###   ########.fr       */
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
	(void)data;
	(void)x;
	(void)y;
	return (data->r);
}

bool	intersect_sphere(t_ray r, t_object *obj, double *t, t_vect *hit_point, t_vect *hit_normal)
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
		*t = t0;
		*hit_point = vect_add(r.origin, vect_scale(r.direction, t0));
		*hit_normal = vect_sub(*hit_point, sphere->center);
		*hit_normal = vect_scale(*hit_normal, 1 / vect_length(*hit_normal));
		return (true);
	}
	return (false);
}

t_color	cast_ray(t_data *data)
{
	t_color	color;
	t_object	*obj;
	t_vect	hit_point;
	t_vect	hit_normal;
	double	t;
	double	t_min;


	obj = data->head;
	t_min = INFINITY;
	color = fill_color(0, 0, 0);
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			if (intersect_sphere(data->r, obj, &t, &hit_point, &hit_normal))
				color = fill_color(255, 0, 0);
		}
		obj = obj->next;
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
			data->r = comput_primary_ray(data, data->img.u, data->img.v);
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
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_key_hook(data.win_ptr, lock_key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);

}
