/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/14 16:13:12 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <stdio.h>

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
		return (vect_scale(vect_new(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1), 0.5));
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
	t_sphere	*sphere3;
	t_camera	cam;
	
	object = ft_calloc(4, sizeof(t_object));
	sphere = sphere_new(vect_new(0, 0, -1), 0.5);
	sphere2 = sphere_new(vect_new(0, -100.5, -1), 100);
	sphere3 = sphere_new(vect_new(0, 0, 1), 0.5);
	object[0].type = SPHERE;
	object[0].object = sphere;
	object[1].type = SPHERE;
	object[1].object = sphere2;
	object[2].type = SPHERE;
	object[2].object = sphere3;
	object[3].type = NONE;
	//image
	aspect_ratio = 16.0 / 9.0;
	image_width = WIN_W;
	image_height = (int)(image_width / aspect_ratio);
	
	//camera
	cam = init_camera(vect_new(0, 0, 0), vect_new(0.5, 0.5, 1), 100.0);

	//render
	y = 0;
	while (y < image_height)
	{
		x = 0;
		while (x <= image_width)
		{
			double u = (double)x / (image_width - 1);
			double v = (double)(image_height - y) / (image_height - 1);
			t_ray r = ray_new(cam.origin, vect_add(cam.lower_left_corner, vect_add(vect_scale(cam.horizontal, u), vect_scale(cam.vertical, v))));
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
	t_img	img;

	__parsing(argc, argv, &data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "miniRT");
	img.img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	fill_img(&img);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img.img, 0, 0);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}


/* void	fill_img(t_img *img)
   {
   int	x;
   int	y;
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
//put this in a struct later
//and put it befor mlx_new_window and mlx_new_image
//and put it in a function and use those values in mlx_new_window and 
//mlx_new_image
//and maybe put put them as global variables
aspect_ratio = 16.0 / 9.0;
image_width = WIN_W;
image_height = (int)(image_width / aspect_ratio);
//camera
//viewport is the rectangle that we project the world
viewport_height = 2.0;
viewport_width = aspect_ratio * viewport_height;
//focal_length is the distance between the camera and the viewport_height
focal_length = 1.0;
//origin is the position of the camera
origin = vect_new(0, 0, 0);
//horizontal is the width of the viewport
horizontal = vect_new(viewport_width, 0, 0);
//vertical is the height of the viewport 
vertical = vect_new(0, viewport_height, 0);
//lower_left_corner is the bottom left corner of the viewport 
//we need the lower_left_corner to calculate the ray 
//that goes from the camera to the pixel 
lower_left_corner = vect_sub(vect_sub(vect_sub(origin, vect_scale(horizontal, 1.0/2)), vect_scale(vertical, 1.0/2)), vect_new(0, 0, focal_length));
//render
y = 0;
while (y < image_height)
{
x = 0;
while (x <= image_width)
{
//u is the position of the pixel on the horizontal axis
double u = (double)x / (image_width - 1);
//v is the position of the pixel on the vertical axis
double v = (double)(image_height - y) / (image_height - 1);
//r is the ray that goes from the camera to the pixel
t_ray r = ray_new(origin, vect_add(lower_left_corner, vect_add(vect_scale(horizontal, u), vect_scale(vertical, v))));
//pixel_color is the color of the pixel 
//we used vector as a color because it's easier to work with 
//-------------------------------------------------------------
//          note!! need to creat color struct later	           |
//          inside ray struct and use it here                  |
//-------------------------------------------------------------
t_vect pixel_color = ray_color(&r);
// printf("pixel_color: %f %f %f\n", pixel_color.x, pixel_color.y, pixel_color.z);
my_mlx_pixel_put(img, x, y, rgb(pixel_color.x, pixel_color.y, pixel_color.z));
// my_mlx_pixel_put(img, x, y, rgb((double)x / WIN_W, (double)(WIN_H - y) / WIN_H, 0.25));
x++;
}
y++;
}
} */
