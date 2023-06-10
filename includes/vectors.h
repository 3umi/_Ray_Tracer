/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:06:57 by brahim            #+#    #+#             */
/*   Updated: 2023/06/10 04:17:25 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vect;

t_vect		vector_add(t_vect v1, t_vect v2);
t_vect		vector_sub(t_vect v1, t_vect v2);
t_vect		vector_mult(t_vect v1, t_vect v2);
t_vect		vector_div(t_vect v1, t_vect v2);
t_vect		vector_scale(t_vect v1, double c);
t_vect		vector_cross(t_vect v1, t_vect v2);
double		vector_dot(t_vect v1, t_vect v2);
double		vector_magnitude(t_vect v);
t_vect		vector_normalize(t_vect v);
t_vect		vector_negate(t_vect v);
/* t_vect		vector_new(double x, double y, double z);
t_vect		vector_copy(t_vect v);
t_vect		vector_from_points(t_vect p1, t_vect p2); */

#endif
