/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:33:06 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/14 06:56:42 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

t_color	gradient(t_color color1, t_color color2, double t)
{
	t_color	color;

	color.r = (1 - t) * color1.r + t * color2.r;
	color.g = (1 - t) * color1.g + t * color2.g;
	color.b = (1 - t) * color1.b + t * color2.b;
	return (color);
}
void	put_gradient_bg(t_data *data, t_color color1, t_color color2)
{
	int		x;
	int		y;
	t_color	pixel_color;

	y = data->img.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x <= data->img.width)
		{
			pixel_color = gradient(color1, color2, (double)y / (data->img.height - 50));
			my_mlx_pixel_put(&data->menu_img, x, y, rgb(pixel_color));
			x++;
		}
		y--;
	}
}

void	draw_checkbox(t_data *data,int x,int y, t_color color)
{
	int		i;
	int		j;

	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			my_mlx_pixel_put(&data->menu_img, x + i, y + j, rgb(color));
			j++;
		}
		i++;
	}
}

void	fill_menu(t_data *data)
{
	int	i;

	put_gradient_bg(data, fill_color(0xFF, 0x3E, 0x9D), fill_color(0x0E, 0x1F, 0x40));
	i = -1;
	while (++i < 5)
		draw_checkbox(data, 10, 10 + (i * 30), fill_color(0xF7, 0xcE, 0x78));
}


void	init_menu(t_data *data)
{
	data->menu_img.img = mlx_new_image(data->mlx_ptr, 300, data->img.height);
	data->menu_img.addr = mlx_get_data_addr(data->menu_img.img,
			&data->menu_img.bits_per_pixel, &data->menu_img.line_length,
			&data->menu_img.endian);
	data->loading_img.img = mlx_new_image(data->mlx_ptr, 300, 50);
	data->loading_img.addr = mlx_get_data_addr(data->loading_img.img,
			&data->loading_img.bits_per_pixel, &data->loading_img.line_length,
			&data->loading_img.endian);
	data->menu_img.width = 300;
	data->menu_img.height = data->img.height;
	fill_menu(data);
	data->switches.specular_sphere = 1;
	data->switches.checkboard_plane = 1;
	data->switches.checkboard_sphere = 1;
}

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
	init_menu(data);
}
