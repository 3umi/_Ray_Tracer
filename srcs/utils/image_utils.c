/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:07:55 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/17 11:24:43 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + \
		(y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
