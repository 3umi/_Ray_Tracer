/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:02:28 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:03:58 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

int	rgb(t_color color)
{
	int	rgb;

	color = _color_clap(color);
	rgb = 0x00;
	rgb += (int)color.r << 16;
	rgb += (int)color.g << 8;
	rgb += (int)color.b;
	return (rgb);
}

t_color	gradient(t_color color1, t_color color2, double t)
{
	t_color	color;

	color.r = (1 - t) * color1.r + t * color2.r;
	color.g = (1 - t) * color1.g + t * color2.g;
	color.b = (1 - t) * color1.b + t * color2.b;
	return (color);
}

t_color	ambient_light(t_lighting *light, t_color color)
{
	double	ratio;
	t_color	tmp;

	ratio = light->amb_light->ratio;
	tmp = color_scalar(color, ratio);
	if (light->light->ratio < EPSILON)
		return (tmp);
	if (tmp.r < color.r)
		tmp.r = color.r;
	if (tmp.g < color.g)
		tmp.g = color.g;
	if (tmp.b < color.b)
		tmp.b = color.b;
	return (tmp);
}
