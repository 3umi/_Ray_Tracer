/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/10 19:27:49 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	close_win(t_data *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
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

int	key_hook(int keycode, t_data *mlx)
{
	if (keycode == 53)
		close_win(mlx);
	return (0);
}

void	fill_img(t_img *img)
{
	int	x;
	int	y;

	y = WIN_H+1;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WIN_W)
		{
			my_mlx_pixel_put(img, x, y, rgb((double)x/WIN_H, (double)y/WIN_W, 0.25));
		}
	}
}

int	main(void)
{
	t_data	mlx;
	t_img	img;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, "miniRT");
	img.img = mlx_new_image(mlx.mlx_ptr, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	fill_img(&img);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, 0, 0);
	mlx_hook(mlx.win_ptr, 17, 0, close_win, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
