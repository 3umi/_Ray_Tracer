/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:37:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/12 23:54:33 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	rerander(t_data *data)
{
	int		x;
	int		y;
	t_color	pixel_color;

	pixel_color = fill_color(0, 0, 0);
	init_camera(data->camera);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
