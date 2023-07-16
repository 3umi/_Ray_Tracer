/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 04:01:04 by brahim            #+#    #+#             */
/*   Updated: 2023/07/16 00:59:48 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.y += 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.y += 0.1;
				sphere->center.y += 0.1;
			}
		}
		if (keycode == S_KEY || keycode == 115)
		{
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.y -= 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.y -= 0.1;
				sphere->center.y -= 0.1;
			}
		}
		else if (keycode == D_KEY || keycode == 100)
		{
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.x += 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.x += 0.1;
				sphere->center.x += 0.1;
			}
		}
		else if (keycode == A_KEY || keycode == 97)
		{
			if (mlx->camera->origin_lock == UNLOCKED)
			{
				mlx->camera->origin.x -= 0.1;
			}
			if (mlx->camera->view_lock == UNLOCKED)
			{
				mlx->camera->lookat.x -= 0.1;
				sphere->center.x -= 0.1;
			}
		}
		else if (keycode == LEFT_AROW)
			mlx->lighting->light->point.x -= 1;
		else if (keycode == RIGHT_AROW)
			mlx->lighting->light->point.x += 1;
		else if (keycode == UP_AROW)
			mlx->lighting->light->point.z -= 1;
		else if (keycode == DOWN_AROW)
			mlx->lighting->light->point.z += 1;
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
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 300, 0);
	return (0);
}
