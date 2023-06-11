/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/12 00:38:14 by belkarto         ###   ########.fr       */
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

double vector_length(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vect vector_unit(t_vect v)
{
	return (vector_scale(v, 1 / vector_length(v)));
}

bool	hit_sphere(t_vect center, double radius, t_ray *r)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vector_sub(r->origin, center);
	a = vector_dot(r->direction, r->direction);
	b = 2.0 * vector_dot(oc, r->direction);
	c = vector_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

t_vect ray_color(t_ray *r)
{
	t_vect unit_direction;
	double t;

	if (hit_sphere(vector_new(0, 0, -2), 1.0, r))
		return (vector_new(1, 0, 0));
	unit_direction = vector_unit(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vector_add(vector_scale(vector_new(1.0, 1.0, 1.0), 1.0 - t), vector_scale(vector_new(0.5, 0.7, 1.0), t)));
}

void	fill_img(t_img *img)
{
	int	x;
	int	y;
	int width;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	double	focal_length;
	double	image_width;
	double	image_height;
	t_vect	origin;
	t_vect	horizontal;
	t_vect	vertical;
	t_vect	lower_left_corner;

	//image
	aspect_ratio = 16.0 / 9.0;
	image_width = 400;
	image_height = (int)(image_width / aspect_ratio);
	//camera
	viewport_height = 2.0;
	viewport_width = aspect_ratio * viewport_height;
	focal_length = 1.0;
	origin = vector_new(0, 0, 0);
	horizontal = vector_new(viewport_width, 0, 0);
	vertical = vector_new(0, viewport_height, 0);
	lower_left_corner = vector_sub(vector_sub(vector_sub(origin, vector_scale(horizontal, 1.0/2)), vector_scale(vertical, 1.0/2)), vector_new(0, 0, focal_length));
	//render
	y = 0;
	while (y < image_height)
	{
		x = WIN_W - 1;
		width = 0;
		while (x >= 0)
		{
			double u = (double)x / (image_width - 1);
			double v = (double)y / (image_height - 1);
			t_ray r = ray_new(origin, vector_add(lower_left_corner, vector_add(vector_scale(horizontal, u), vector_scale(vertical, v))));
			t_vect pixel_color = ray_color(&r);
			my_mlx_pixel_put(img, x, y, rgb(pixel_color.x, pixel_color.y, pixel_color.z));
			// my_mlx_pixel_put(img, width, y, rgb((double)(WIN_W - x) / WIN_W, (double)(WIN_H - y) / WIN_H, 0.25));
			x--;
			width++;
		}
		y++;
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
