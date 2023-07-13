/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:12:53 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:17:55 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_BONUS_H
# define VECTORS_BONUS_H

typedef struct s_vect
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vect;

t_vect		vect_add(t_vect v1, t_vect v2);
t_vect		vect_sub(t_vect v1, t_vect v2);
t_vect		vect_mult(t_vect v1, t_vect v2);
t_vect		vect_div(t_vect v1, t_vect v2);
t_vect		vect_scale(t_vect v1, double c);
t_vect		vect_cross(t_vect v1, t_vect v2);
double		vect_dot(t_vect v1, t_vect v2);
t_vect		vect_normalize(t_vect v);
t_vect		vect_new(double x, double y, double z);
double		vect_length(t_vect v);
t_vect		vect_unit(t_vect v);

#endif
