/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:31:27 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/19 18:31:38 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_mat4	mat4_rotate_x(double angle)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[1][1] = cos(angle);
	mat.m[1][2] = -sin(angle);
	mat.m[2][1] = sin(angle);
	mat.m[2][2] = cos(angle);
	return (mat);
}

t_mat4	mat4_rotate_y(double angle)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = cos(angle);
	mat.m[0][2] = sin(angle);
	mat.m[2][0] = -sin(angle);
	mat.m[2][2] = cos(angle);
	return (mat);
}

t_mat4	mat4_rotate_z(double angle)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = cos(angle);
	mat.m[0][1] = -sin(angle);
	mat.m[1][0] = sin(angle);
	mat.m[1][1] = cos(angle);
	return (mat);
}

t_mat4	mat4_rotate(t_vect v)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat = mat4_mult(mat4_rotate_x(v.x), mat);
	mat = mat4_mult(mat4_rotate_y(v.y), mat);
	mat = mat4_mult(mat4_rotate_z(v.z), mat);
	return (mat);
}

t_vect	mat4_mult_vect(t_mat4 m, t_vect v)
{
	t_vect	res;

	res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	res.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
	return (res);
}
