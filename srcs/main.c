/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/25 22:45:16 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <float.h>
#include <limits.h>
#include <stdio.h>

int	rgb(t_color color)
{
	int	rgb;

	rgb = 0x00;
	rgb += (int)color.r << 16;
	rgb += (int)color.g << 8;
	rgb += (int)color.b;
	return (rgb);
}
/* double randomBetweenZeroAndOne()
{
    // Seed the random number generator

    // Generate a random number between 0 and RAND_MAX
    int randNum = rand();

    // Scale the random number to the range [0, 1]
    double result = (double)randNum / RAND_MAX;

    return result;
}
double random_double(double min, double max)
{
	return (min + (max - min) * randomBetweenZeroAndOne());
} */
/* t_vect vect_random(double min, double max)
{
	t_vect p;

	p = vect_new(random_double(min, max), random_double(min, max), random_double(min, max));
	return (p);
}
 */
double vect_length_squared(t_vect v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

/* t_vect vect_random_in_unit_sphere()
{
	t_vect p;

	p = vect_new(0, 0, 0);
	while (1)
	{
		p = vect_random(-1, 1);
		if (vect_length_squared(p) >= 1)
			break ;
	}
	return (p);
} */

t_color ray_color(t_ray *r, t_object *world, int depth)
{
	t_hitrecod	rec;
	// t_vect		target;

	if (depth <= 0)
		return (fill_color(0, 0, 0));
	// target = vect_add(r->origin, vect_add(r->direction, vect_random_in_unit_sphere()));
	if (hittable_list_hit(world, r, 0, INFINITY, &rec))
	{
		return (rec.color);
	}
	return (fill_color(0, 0, 0));
}

t_color color_sqrt(t_color color)
{
	color.r = sqrt(color.r);
	color.g = sqrt(color.g);
	color.b = sqrt(color.b);
	return (color);
}

void	av_color(t_color *pixel_color, t_color color, int ind)
{
	/* if (ind == 0)
		pixel_color = &color;
	else */
	(void)ind;
	{
		*pixel_color = color_scalar(color_add(*pixel_color, color), 0.5);
	}
}

void	fill_img(t_data *data)
{
	int	x;
	int	y;
	int			s;


	//camera
	init_camera(data->camera);

	//render
	y = data->img.height - 1;
	t_color	pixel_color = fill_color(0, 0, 0);
	while (y >= 0)	{
		x = 0;
		while (x <= data->img.width)
		{
			s = 0;
			while (s < data->img.samples_per_pixel)
			{
				data->img.u = (double)(x + ((double)s / 10)) / (data->img.width - 1);
				data->img.v = (double)(data->img.height - y + (double)s / 10) / (data->img.height - 1);
				t_ray r = ray_new(data->camera, data->img.u, data->img.v);
				av_color(&pixel_color, ray_color(&r, data->object, data->depth), s);
				s++;
			}
			my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color));
			x++;
		}
		y--;
	}
}
#include <time.h>

int	main(int argc, char **argv)
{
	t_data	data;
	srand(time(NULL));

	__parsing(argc, argv, &data);
	__init(&data);
	fill_img(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_key_hook(data.win_ptr, lock_key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);

}
