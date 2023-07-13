/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:33:06 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:53:14 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	__init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->img.aspect_ratio = 16.0 / 9.0;
	data->camera->aspect_ratio = data->img.aspect_ratio;
	data->camera->lookat = vect_new(0, 0, 0);
	data->img.width = WIN_W;
	data->img.height = data->img.width / data->img.aspect_ratio;
	printf("width = %f\n", data->img.width);
	printf("height = %f\n", data->img.height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img.width + 300,
			data->img.height, "miniRT");
	data->img.img = mlx_new_image(data->mlx_ptr, data->img.width,
			data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->img.samples_per_pixel = 10;
	data->depth = MAX_DEPTH;
	data->camera->origin_lock = UNLOCKED;
	data->camera->view_lock = UNLOCKED;
	data->head = data->object;
}
