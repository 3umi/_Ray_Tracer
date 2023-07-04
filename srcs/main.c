/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/04 02:04:48 by belkarto         ###   ########.fr       */
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

// ray color is function that takes a ray send from camera to a pixel in 
// the screen and return the color of the pixel after the ray hit the object
// in the scene
t_color ray_color(t_data *data) 
{
	t_hitrecod	rec;
	// t_vect		target;

	if (data->depth <= 0)
		return (fill_color(0, 0, 0));
	if (hittable_list_hit(data, &rec))
		return (rec.color);
	return (fill_color(0, 0, 0));
}

void	av_color(t_color *pixel_color, t_color color)
{
		*pixel_color = color_scalar(color_add(*pixel_color, color), 0.5);
}

void	fill_img(t_data *data)
{
	int	x;
	int	y;
	init_camera(data->camera);

	y = data->img.height - 1;
	t_color	pixel_color = fill_color(0, 0, 0);
	data->img.samples_count = 0;
	while (data->img.samples_count < data->img.samples_per_pixel)
	{
		while (y >= 0)	{
			x = 0;
			while (x <= data->img.width)
			{
				data->img.u = (double)(x + ((double)data->img.samples_count / 10)) / (data->img.width - 1);
				data->img.v = (double)(data->img.height - y + (double)data->img.samples_count / 10) / (data->img.height - 1);
				data->r = ray_new(data->camera, data->img.u, data->img.v);
				av_color(&pixel_color, ray_color(data));
				my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color));
				x++;
			}
			y--;
		}
		data->img.samples_count++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

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
