/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 01:56:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/16 02:45:51 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniRT_bonus.h"

static void	hit_checkbox(t_data *data, int y)
{
	if (y >= 10 && y <= 30)
		data->switches.checkboard_plane = !data->switches.checkboard_plane;
	else if (y >= 40 && y <= 60)
		data->switches.specular_sphere = !data->switches.specular_sphere;
	else if (y >= 70 && y <= 90)
		data->switches.sphere_gradient = !data->switches.sphere_gradient;
	/* else if (y >= 100 && y <= 120)
	else if (y >= 130 && y <= 150)
	else if (y >= 160 && y <= 180) */
	put_text(data);
}

int	mouse_release(int key, int x, int y, t_data *data)
{
	if (key == 1)
	{
		if (x >= 10 && x <= 290 && y >= 530 && y <= 570)
			rerander(data);
		else if (x >= 10 && x <= 30)
			hit_checkbox(data, y);
	}
	return (0);
}
