/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:44 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/18 01:45:55 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	__parsing(argc, argv, &data);
	__init(&data);
	rerander(&data);
	mlx_hook(data.win_ptr, 17, 0, close_win, &data);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_key_hook(data.win_ptr, lock_key_hook, &data);
	// mlx_hook(data.win_ptr, 5, 0, mouse_release, &data);
	mlx_mouse_hook(data.win_ptr, mouse_release, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
