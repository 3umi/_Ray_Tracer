/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:20:37 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/13 04:53:15 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

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
