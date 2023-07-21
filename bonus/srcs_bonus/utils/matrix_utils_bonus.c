/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:12:06 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:14:05 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

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
