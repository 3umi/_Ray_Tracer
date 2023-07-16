/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:48:04 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/16 02:40:38 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

t_color	_color_clap(t_color color)
{
	t_color	tmp;

	tmp = color;
	if (tmp.r > 255)
		tmp.r = 255;
	if (tmp.g > 255)
		tmp.g = 255;
	if (tmp.b > 255)
		tmp.b = 255;
	return (tmp);
}

t_color	gradient(t_color color1, t_color color2, double t)
{
	t_color	color;

	color.r = (1 - t) * color1.r + t * color2.r;
	color.g = (1 - t) * color1.g + t * color2.g;
	color.b = (1 - t) * color1.b + t * color2.b;
	color = _color_clap(color);
	return (color);
}

int	rgb(t_color color)
{
	int	rgb;

	rgb = 0x00;
	rgb += (int)color.r << 16;
	rgb += (int)color.g << 8;
	rgb += (int)color.b;
	return (rgb);
}

t_color	fill_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}


t_color	color_add(t_color a, t_color b)
{
	t_color	color;

	color.r = a.r + b.r;
	color.g = a.g + b.g;
	color.b = a.b + b.b;
	return (color);
}

t_color	color_scalar(t_color color, double scalar)
{
	color.r *= scalar;
	color.g *= scalar;
	color.b *= scalar;
	return (color);
}

void	av_color(t_color *pixel_color, t_color color)
{
		*pixel_color = color_scalar(color_add(*pixel_color, color), 0.5);
}
