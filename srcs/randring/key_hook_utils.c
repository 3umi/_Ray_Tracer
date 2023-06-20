/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 04:01:04 by brahim            #+#    #+#             */
/*   Updated: 2023/06/20 15:40:47 by belkarto         ###   ########.fr       */
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
	if (keycode == W_KEY)
	{
		mlx->img.samples_per_pixel = 1;
		if (mlx->camera->origin_lock == UNLOCKED)
		{
			mlx->camera->origin.y += 0.1;
			sphere->center.y += 0.1;
		}
		if (mlx->camera->view_lock == UNLOCKED)
		{
			mlx->camera->lookat.y += 0.1;
			sphere->center.y += 0.1;
		}
		init_camera(mlx->camera);
		rerander(mlx);
	}
	if (keycode == S_KEY)
	{
		mlx->img.samples_per_pixel = 1;
		if (mlx->camera->origin_lock == UNLOCKED)
		{
			mlx->camera->origin.y -= 0.1;
			sphere->center.y -= 0.1;
		}
		if (mlx->camera->view_lock == UNLOCKED)
		{
		    mlx->camera->lookat.y -= 0.1;
		    sphere->center.y -= 0.1;
		}
		init_camera(mlx->camera);
		rerander(mlx);
	}
	if (keycode == D_KEY)
	{
		mlx->img.samples_per_pixel = 1;
		if (mlx->camera->origin_lock == UNLOCKED)
		{
			mlx->camera->origin.x += 0.1;
			sphere->center.x += 0.1;
		}
		if (mlx->camera->view_lock == UNLOCKED)
		{
		    mlx->camera->lookat.x += 0.1;
		    sphere->center.x += 0.1;
		}
		init_camera(mlx->camera);
		rerander(mlx);
	}
	if (keycode == A_KEY)
	{
		mlx->img.samples_per_pixel = 1;
		if (mlx->camera->origin_lock == UNLOCKED)
		{
			mlx->camera->origin.x -= 0.1;
			sphere->center.x -= 0.1;
		}
		if (mlx->camera->view_lock == UNLOCKED)
		{
		    mlx->camera->lookat.x -= 0.1;
		    sphere->center.x -= 0.1;
		}
		init_camera(mlx->camera);
		rerander(mlx);
	}
	if (keycode == Q_KEY)
	{
		if (mlx->camera->origin_lock == UNLOCKED)
			mlx->camera->origin_lock = LOCKED;
		else
			mlx->camera->origin_lock = UNLOCKED;
	}
	if (keycode == E_KEY)
	{
		if (mlx->camera->view_lock == UNLOCKED)
			mlx->camera->view_lock = LOCKED;
		else
			mlx->camera->origin_lock = UNLOCKED;
	}
	if (mlx->camera->origin_lock == LOCKED)
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0x00FFFFFF, "Origin locked");
	else
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0x00FFFFFF, "Origin unlocked");
	if (mlx->camera->view_lock == LOCKED)
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 30, 0x00FFFFFF, "View locked");
	else
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 30, 0x00FFFFFF, "View unlocked");
	printf("keycode %d\n", keycode);
	return (0);
}
