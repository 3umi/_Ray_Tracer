/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/16 21:47:01 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <float.h>
#include <limits.h>
#include <stdio.h>

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
double randomBetweenZeroAndOne()
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
}
t_vect vect_random(double min, double max)
{
	t_vect p;

	p = vect_new(random_double(min, max), random_double(min, max), random_double(min, max));
	return (p);
}

double vect_length_squared(t_vect v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vect vect_random_in_unit_sphere()
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
}
/* t_vect t_ray_new(t_vect origin, t_vect direction)
{
	t_ray r;

	r.origin = origin;
	r.direction = direction;
	return (r);
} */
t_vect ray_color(t_ray *r, t_object *world, int depth)
{
	t_hitrecod	rec;
	t_vect		target;

	if (depth <= 0)
		return (vect_new(0, 0, 0));
	target = vect_add(r->origin, vect_add(r->direction, vect_random_in_unit_sphere()));
	if (hittable_list_hit(world, r, 0, INFINITY, &rec))
	{
		// return(vect_new(1, 0, 1));
		return (rec.color);
		// rec.color = vect_scale(rec.color, 0.5);
		// return (vect_scale(ray_color(&target_ray, world, depth - 1), 0.5));
		// return (vect_scale(&target_ray, world, depth - 1), 0.5);
		// return (vect_scale(vect_new(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1), 0.5));
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
	int			s;
	int			bounce_limit;

	object = ft_calloc(3, sizeof(t_object));
	sphere = sphere_new(vect_new(0, 0, -1), 0.5);
	sphere2 = sphere_new(vect_new(0, -100, -1), 100);
	object[0].type = SPHERE;
	object[0].object = sphere;
	object[1].type = SPHERE;
	object[1].object = sphere2;
	object[2].type = NONE;

	//camera
	cam = init_camera(vect_new(0, 0, 10), vect_new(0, 0, -1), vect_new(0, 1, 0), 20, data->img.aspect_ratio);

	//render
	y = data->img.height - 1;
	t_vect pixel_color = vect_new(0, 0, 0);
	bounce_limit = 50;
	while (y >= 0)//) < data->img.height)
	{
		x = 0;
		while (x <= data->img.width)
		{
			s = 0;
			while (s < data->img.samples_per_pixel)
			{
				data->img.u = (double)(x + ((double)s / 10)) / (data->img.width - 1);
				data->img.v = (double)(data->img.height - y + (double)s / 10) / (data->img.height - 1);
				t_ray r = ray_new(&cam, data->img.u, data->img.v);
				pixel_color = vect_scale(vect_add(pixel_color, ray_color(&r, object, bounce_limit)), 0.5);
				s++;
			}
			my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color.x, pixel_color.y, pixel_color.z));
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
	rerander(&data);
	fill_img(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
