/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:33:06 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 15:24:52 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

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
			pixel_color = gradient(color1, color2, (double)y / (data->img.height));
			my_mlx_pixel_put(&data->menu_img, x, y, rgb(pixel_color));
			x++;
		}
		y--;
	}
}

void	draw_box(t_data *data, t_vect corr, t_vect width_and_hieght, t_color color)
{
	int		i;
	int		j;

	i = 0;
	while (i < width_and_hieght.x)
	{
		j = 0;
		while (j < width_and_hieght.y)
		{
			my_mlx_pixel_put(&data->menu_img, corr.x + i, corr.y + j, rgb(color));
			j++;
		}
		i++;
	}
}

void	put_camera_rotation_button(t_data *data, t_color color)
{
	t_vect	corr;
	t_vect	size;

	size = vect_new(86, 30, 0);
	corr = vect_new(10, 470, 0);
	draw_box(data, corr, size, color);
	corr.x += 86 + 10;
	draw_box(data, corr, size, color);
	corr.x += 86 + 10;
	draw_box(data, corr, size, color);
	corr.x = 86 + 20;
	corr.y = 470 - 40;
	draw_box(data, corr, size, color);
}

void	fill_menu(t_data *data)
{
	int	i;
	t_vect	corrd;
	t_vect	size;

	corrd = vect_new(0, 0, 0);
	size = vect_new(20, 20, 0);
	put_gradient_bg(data, fill_color(0xFF, 0x3E, 0x9D), fill_color(0x0E, 0x1F, 0x40));
	i = -1;
	while (++i < 5)
	{
		corrd.x = 10;
		corrd.y = 10 + (i * 30);
		draw_box(data, corrd, size, fill_color(0xF7, 0xcE, 0x78));
	}
	corrd.y = 530;
	size.x = 280;
	size.y = 40;
	draw_box(data, corrd, size, fill_color(0xF7, 0xcE, 0x78));
	put_camera_rotation_button(data, fill_color(0xAA, 0x11, 0xAA));
}


void	init_menu(t_data *data)
{
	data->menu_img.img = mlx_new_image(data->mlx_ptr, 300, data->img.height);
	data->menu_img.addr = mlx_get_data_addr(data->menu_img.img,
			&data->menu_img.bits_per_pixel, &data->menu_img.line_length,
			&data->menu_img.endian);
	data->empty_img.img = mlx_new_image(data->mlx_ptr, data->img.width,
			data->img.height);
	data->empty_img.addr = mlx_get_data_addr(data->empty_img.img,
			&data->empty_img.bits_per_pixel, &data->empty_img.line_length,
			&data->empty_img.endian);
	data->menu_img.width = 300;
	data->menu_img.height = data->img.height;
	fill_menu(data);
	data->switches.specular = 0;
	data->switches.checkboard_plane = 0;
	data->switches.sphere_gradient = 0;
	data->switches.cylinder_gradient = 0;
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
	data->img.samples_per_pixel = 100;
	data->camera->origin_lock = UNLOCKED;
	data->camera->view_lock = UNLOCKED;
	data->head = data->object;
	init_menu(data);
}
