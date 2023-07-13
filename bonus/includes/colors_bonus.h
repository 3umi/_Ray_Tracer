/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:26 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:15:46 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_BONUS_H
# define COLORS_BONUS_H

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}			t_color;

t_color	fill_color(double r, double g, double b);
t_color	color_add(t_color a, t_color b);
t_color	color_scalar(t_color a, double scalar);
void	av_color(t_color *pixel_color, t_color color);
int		rgb(t_color color);

#endif
