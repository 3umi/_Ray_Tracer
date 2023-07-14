/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:12:06 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/14 09:46:20 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* void	print_mat4(t_mat4 mat)
{
	printf("matrix:\n");
	printf("\t|\t%.2f\t%.2f\t%.2f\t%.2f\t|\n", 
			mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3]);
	printf("\t|\t%.2f\t%.2f\t%.2f\t%.2f\t|\n", 
			mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3]);
	printf("\t|\t%.2f\t%.2f\t%.2f\t%.2f\t|\n", 
			mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3]);
	printf("\t|\t%.2f\t%.2f\t%.2f\t%.2f\t|\n", 
			mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]);
} */

t_mat4	mat4_identity(void)
{
	t_mat4	mat;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			mat.m[i][j] = 0;
			if (i == j)
				mat.m[i][j] = 1;
		}
	}
	return (mat);
}

t_mat4	mat4_mult(t_mat4 a, t_mat4 b)
{
	t_mat4	mat;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			mat.m[i][j] = 0;
			k = -1;
			while (++k < 4)
				mat.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (mat);
}

t_mat4	mat4_scale(t_vect v)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = v.x;
	mat.m[1][1] = v.y;
	mat.m[2][2] = v.z;
	return (mat);
}

t_mat4	mat4_translate(t_vect v)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][3] = v.x;
	mat.m[1][3] = v.y;
	mat.m[2][3] = v.z;
	return (mat);
}

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
