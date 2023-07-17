/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <belkarto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:56:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/17 15:08:56 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniRT_bonus.h"

static void	hit_checkbox(t_data *data, int y)
{
	if (y >= 10 && y <= 30)
		data->switches.checkboard_plane = !data->switches.checkboard_plane;
	else if (y >= 40 && y <= 60)
		data->switches.specular = !data->switches.specular;
	else if (y >= 70 && y <= 90)
		data->switches.sphere_gradient = !data->switches.sphere_gradient;
	/* else if (y >= 100 && y <= 120)
	else if (y >= 130 && y <= 150)
	else if (y >= 160 && y <= 180) */
	put_text(data);
}

void	rotation_camera(t_data *data, int x, int y)
{
	// up x 106 192 y 430 460
	// down x 106 192 y 470 500
	// left x 10 96 y 470 500
	// right x 202 288 y 470 500
	t_mat4	mat;
	
	mat = mat4_identity();
	if (x >= 106 && x <= 192 && y >= 430 && y <= 460)
	{
		mat = mat4_rotate_x(90 * M_PI / 180);
		data->camera->origin = mat4_mult_vect(mat, data->camera->origin);
		printf("up x %d y %d\n", x, y);
	}
	else if (x >= 106 && x <= 192 && y >= 470 && y <= 500)
	{
		mat4_rotate_x(-1 * (90 * M_PI / 180));
		data->camera->origin = mat4_mult_vect(mat, data->camera->origin);
		printf("x %d y %d\n", x, y);
	}
	else if (x >= 10 && x <= 96 && y >= 470 && y <= 500)
	{
		mat4_rotate_y(90 * M_PI / 180);
		data->camera->origin = mat4_mult_vect(mat, data->camera->origin);
		printf("x %d y %d\n", x, y);
	}
	else if (x >= 202 && x <= 288 && y >= 470 && y <= 500)
	{
		mat4_rotate_y(-90 * M_PI / 180);
		data->camera->origin = mat4_mult_vect(mat, data->camera->origin);
		printf("x %d y %d\n", x, y);
	}
	//printf("x %d y %d\n", x, y);
}
int	mouse_release(int key, int x, int y, t_data *data)
{
	if (key == 1)
	{
		if (x >= 10 && x <= 290 && y >= 530 && y <= 570)
			rerander(data);
		else if (x >= 10 && x <= 290 && y >= 430 && y <= 500)
			rotation_camera(data, x, y);
		else if (x >= 10 && x <= 30)
			hit_checkbox(data, y);
	}
	return (0);
}
