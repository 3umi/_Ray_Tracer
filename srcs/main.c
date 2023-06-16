/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/16 11:55:20 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <float.h>
#include <limits.h>
#include <stdio.h>

t_vect clamp_vec(t_vect color)
{
	t_vect tmp;

	tmp.x = fmin(color.x, 1.0);
	tmp.y = fmin(color.y, 1.0);
	tmp.z = fmin(color.z, 1.0);
	return (tmp);
}

int	rgb(double r, double g, double b)
{
	int	rgb;

	rgb = 0x00;
	r = 255.999 * r;
	g = 255.999 * g;
	b = 255.999 * b;
	rgb += (int)r << 16;
	rgb += (int)g << 8;
	rgb += (int)b;
	return (rgb);
}

double	rnd(void)
{
	return ((double)rand() / ((double)RAND_MAX + 1));
}

double	rnd2(double min, double max)
{
	return (min + (max - min) * rnd());
}

t_vect ray_color(t_ray *r, t_object *world)
{
	t_hitrecod	rec;

	if (hittable_list_hit(world, r, 0, INFINITY, &rec))
	{
		// return(vect_new(1, 0, 1));
		return (rec.color);
		return (vect_scale(vect_new(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1), 0.5));
	}
	// return (vect_new(0, 0, 0));
	t_vect	unit_direction;
	unit_direction = vect_unit(r->direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	return (vect_add(vect_scale(vect_new(1.0, 1.0, 1.0), 1.0 - t), vect_scale(vect_new(0.0, 0.0, 1.0), t)));
}

void	fill_img(t_data *data)
{
	int	x;
	int	y;
	t_object	*object;
	t_sphere	*sphere;
	t_sphere	*sphere2;
	t_camera	cam;

	object = ft_calloc(3, sizeof(t_object));
	sphere = sphere_new(vect_new(0, 0, -1), 0.5);
	sphere2 = sphere_new(vect_new(0, -1000, -1), 1000);
	object[0].type = SPHERE;
	object[0].object = sphere;
	object[1].type = SPHERE;
	object[1].object = sphere2;
	object[2].type = NONE;

	//camera
	cam = init_camera(vect_new(0, 0, 0), vect_new(0, 0, -1), vect_new(0, 1, 0), 90, data->img.aspect_ratio);

	//render
	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x <= data->img.width)
		{
			double u = (double)x / (data->img.width - 1);
			double v = (double)(data->img.height - y) / (data->img.height - 1);
			// double v = (double)y / (data->img.height - 1);
			t_ray r = ray_new(&cam, u, v);
			t_vect pixel_color = ray_color(&r, object);
			my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color.x, pixel_color.y, pixel_color.z));
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	__parsing(argc, argv, &data);
	__init(&data);
	rerander(&data);
	fill_img(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
