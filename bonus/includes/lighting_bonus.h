/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:14:34 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:16:58 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_BONUS_H
# define LIGHTING_BONUS_H

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
