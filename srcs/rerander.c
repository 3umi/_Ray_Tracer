/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:37:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/16 20:52:43 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void		rerander(t_data *data)
{
	int	x;
	int	y;
	int	s;

	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		while (x <= data->img.width)
		{
			s = -1;
			while (s < data->img.samples_per_pixel)
			{
				data->img.u = (double)(x + (double)s / 10) / (data->img.width - 1);
				data->img.v = (double)(data->img.height - y + (double)s / 10) / (data->img.height - 1); 
				s++;
			}
			x++;
		}
		y++;
	}
}
