/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 04:01:04 by brahim            #+#    #+#             */
/*   Updated: 2023/07/07 02:01:51 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <stdio.h>

int	close_win(t_data *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
}

int	key_hook(int keycode, t_data *mlx)
{
	t_sphere	*sphere;

	sphere = mlx->object->object;
	if (keycode == ESC || keycode == ESC_LINUX)
		close_win(mlx);
	if (mlx->camera->origin_lock == UNLOCKED || mlx->camera->view_lock == UNLOCKED)
	{
		if (keycode == W_KEY || keycode == 119)
		{
			mlx->img.samples_per_pixel = 10;
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.y += 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.y += 0.1;
				sphere->center.y += 0.1;
			}
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		if (keycode == S_KEY || keycode == 115)
		{
			mlx->img.samples_per_pixel = 10;
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.y -= 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.y -= 0.1;
				sphere->center.y -= 0.1;
			}
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		else if (keycode == D_KEY || keycode == 100)
		{
			mlx->img.samples_per_pixel = 10;
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.x += 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.x += 0.1;
				sphere->center.x += 0.1;
			}
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		else if (keycode == A_KEY || keycode == 97)
		{
			mlx->img.samples_per_pixel = 10;
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.x -= 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.x -= 0.1;
				sphere->center.x -= 0.1;
			}
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		else if (keycode == LEFT_AROW)
		{
			mlx->lighting->light->point.x -= 1;
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		else if (keycode == RIGHT_AROW)
		{
			mlx->lighting->light->point.x += 1;
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		else if (keycode == UP_AROW)
		{
			mlx->lighting->light->point.z -= 1;
			// init_camera(mlx->camera);
			rerander(mlx);
		}
		else if (keycode == DOWN_AROW)
		{
			mlx->lighting->light->point.z += 1;
			// init_camera(mlx->camera);
			rerander(mlx);
		}
	}
	printf("keycode %d\n", keycode);
	return (0);
}

int	lock_key_hook(int keycode, t_data *mlx)
{
	if (keycode == Q_KEY || keycode == 113)
	{
		if (mlx->camera->origin_lock == UNLOCKED)
			mlx->camera->origin_lock = LOCKED;
		else
			mlx->camera->origin_lock = UNLOCKED;
	}
	else if (keycode == E_KEY || keycode == 101)
	{
		if (mlx->camera->view_lock == UNLOCKED)
			mlx->camera->view_lock = LOCKED;
		else
			mlx->camera->view_lock = UNLOCKED;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	if (mlx->camera->origin_lock == LOCKED)
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0x00FF0000, "Origin : locked");
	else
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0x00FF0000, "Origin : unlocked");
	if (mlx->camera->view_lock == LOCKED)
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 30, 0x00FF0000, "View   : locked");
	else
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 30, 0x00FF0000, "View   : unlocked");
	//printf origin
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 50, 0x00FF0000, "Origin : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 100, 50, 0x00FF0000, ft_itoa(mlx->camera->origin.x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 150, 50, 0x00FF0000, ft_itoa(mlx->camera->origin.y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 50, 0x00FF0000, ft_itoa(mlx->camera->origin.z));
	//printf view
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 70, 0x00FF0000, "View   : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 100, 70, 0x00FF0000, ft_itoa(mlx->camera->lookat.x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 150, 70, 0x00FF0000, ft_itoa(mlx->camera->lookat.y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 70, 0x00FF0000, ft_itoa(mlx->camera->lookat.z));
	//printf light
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 90, 0x00FF0000, "Light  : ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 100, 90, 0x00FF0000, ft_itoa(mlx->lighting->light->point.x));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 150, 90, 0x00FF0000, ft_itoa(mlx->lighting->light->point.y));
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 200, 90, 0x00FF0000, ft_itoa(mlx->lighting->light->point.z));
	return (0);
}
