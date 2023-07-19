/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:47:04 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 00:35:24 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vect	vect_normalize(t_vect v)
{
	double	length;

	length = vect_length(v);
	if (length == 0)
		return (v);
	return (vect_scale(v, 1 / length));
}

t_vect	vect_new(double x, double y, double z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1;
	return (v);
}

double	vect_length(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vect	vect_unit(t_vect v)
{
	return (vect_scale(v, 1 / vect_length(v)));
}

/* t_vect		vect_mult(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
} */

/* t_vect		vect_div(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
} */
