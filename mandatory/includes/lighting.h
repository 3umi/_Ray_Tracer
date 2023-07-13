/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:39:49 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/13 04:50:27 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "colors.h"
# include "vectors.h"

typedef struct s_amb_light
{
	double	ratio;
	t_color	color;
}			t_amb_light;

typedef struct s_ligh
{
	double	ratio;
	t_vect	point;
	t_color	color;
}			t_light;

typedef struct s_lighting
{
	t_amb_light	*amb_light;
	t_light		*light;
}				t_lighting;

#endif
