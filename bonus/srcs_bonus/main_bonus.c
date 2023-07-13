/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/13 07:01:24 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	fill_img(t_data *data)
{
	int		x;
	int		y;
	t_color	pixel_color;

	pixel_color = fill_color(0, 0, 0);
	init_camera(data->camera);
	y = data->img.height - 1;
	data->img.samples_count = 0;
	while (data->img.samples_count < data->img.samples_per_pixel)
	{
		while (y >= 0)
		{
			x = 0;
			while (x <= data->img.width)
			{
				data->r = calculate_ray(data, x, y);
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
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 300, 0);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_key_hook(data.win_ptr, lock_key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
