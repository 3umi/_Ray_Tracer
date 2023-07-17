/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerander_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:37:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/17 18:45:23 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	put_text(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->menu_img.img, 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 80, 540, 0xFF0000,
			"RERANDER IMAGE");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 10, 0x0000C0FF,
			"Plane checkboard");
	if (data->switches.checkboard_plane)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 15, 10, 0x0000C0FF, "X");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 40, 0x0000C0FF,
			"Sphere specular");
	if (data->switches.specular)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 15, 40, 0x0000C0FF, "X");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 70, 0x0000C0FF,
			"Sphere gradient");
	if (data->switches.sphere_gradient)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 15, 70, 0x0000C0FF, "X");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 100, 0x0000C0FF,
			"Cylinder gradient");
	if (data->switches.cylinder_gradient)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 15, 100, 0x0000C0FF, "X");
	// put up down left right for camera
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 440, 0x0000C0FF,
			"UP");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 130, 480, 0x0000C0FF,
			"DOWN");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 480, 0x0000C0FF,
			"LEFT");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 230, 480, 0x0000C0FF,
			"RIGHT");
}

void	rerander(t_data *data)
{
	int		x;
	int		y;
	t_color	pixel_color;

	printf("randring\n");
	pixel_color = fill_color(0, 0, 0);
	init_camera(data->camera);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->empty_img.img, 300, 0);
	y = -1;
	data->img.samples_count = 0;
	while (data->img.samples_count < data->img.samples_per_pixel)
	{
		while (++y < data->img.height)
		{
			x = -1;
			while (++x <= data->img.width)
			{
				data->r = calculate_ray(data, x, y);
				av_color(&pixel_color, ray_color(data));
				my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color));
			}
		}
		data->img.samples_count++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 300, 0);
	put_text(data);
	printf("done\n");
}
