/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/16 11:25:28 by belkarto         ###   ########.fr       */
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
	return (vect_new(0, 0, 0));
	t_vect	unit_direction;
	unit_direction = vect_unit(r->direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	return (vect_add(vect_scale(vect_new(1.0, 1.0, 1.0), 1.0 - t), vect_scale(vect_new(0.5, 0.8, 1.0), t)));
}

void	fill_img(t_img *img)
{
	int	x;
	int	y;
	double	aspect_ratio;
	double	image_width;
	double	image_height;
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
	//image
	aspect_ratio = 16.0 / 9.0;
	image_width = WIN_W;
	image_height = (int)(image_width / aspect_ratio);

	//camera
	cam = init_camera(vect_new(0, 0, 0), vect_new(0, 0, -1), vect_new(0, 1, 0), 90, aspect_ratio);

	//render
	y = 0;
	while (y < image_height)
	{
		x = 0;
		while (x <= image_width)
		{
			double u = (double)x / (image_width - 1);
			double v = (double)(image_height - y) / (image_height - 1);
			t_ray r = ray_new(&cam, u, v);
			t_vect pixel_color = ray_color(&r, object);
			my_mlx_pixel_put(img, x, y, rgb(pixel_color.x, pixel_color.y, pixel_color.z));
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	__parsing(argc, argv, &data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "miniRT");
	data.img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	rerander(&data);
	fill_img(&data.img);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
