/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:06:57 by brahim            #+#    #+#             */
/*   Updated: 2023/07/03 07:39:46 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vect
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
double		vect_magnitude(t_vect v);
t_vect		vect_normalize(t_vect v);
t_vect		vect_negate(t_vect v);
t_vect		vect_new(double x, double y, double z);
t_vect		vect_copy(t_vect v);
t_vect		vect_from_points(t_vect p1, t_vect p2);
double		vect_length(t_vect v);
t_vect		vect_unit(t_vect v);

#endif
