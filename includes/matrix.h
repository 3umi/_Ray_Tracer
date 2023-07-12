/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 04:44:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/03 15:47:58 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct	s_mat2
{
	double		m[2][2];
}				t_mat2;

typedef struct	s_mat3
{
	double		m[3][3];
}				t_mat3;

typedef struct	s_mat4
{
	double		m[4][4];
}				t_mat4;

void		print_mat4(t_mat4 mat);
t_mat4		mat4_identity(void);
t_mat4		mat4_mult(t_mat4 a, t_mat4 b);
t_mat4		mat4_translate(t_vect v);
t_mat4		mat4_scale(t_vect v);
t_mat4		mat4_rotate_x(double angle);
t_mat4		mat4_rotate_y(double angle);
t_mat4		mat4_rotate_z(double angle);
t_mat4		mat4_rotate(t_vect v);
t_mat4		mat4_transpose(t_mat4 m);
t_mat4		mat4_inverse(t_mat4 m);
t_vect		mat4_mult_vect(t_mat4 m, t_vect v);


#endif
