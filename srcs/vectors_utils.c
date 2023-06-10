/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:08:57 by brahim            #+#    #+#             */
/*   Updated: 2023/06/10 04:17:38 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

t_vect		vect_add(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vect		vect_sub(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vect		vect_mult(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vect		vect_div(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}

t_vect		vect_scale(t_vect v, double c)
{
	t_vect	v1;

	v1.x = v.x * c;
	v1.y = v.y * c;
	v1.z = v.z * c;
	return (v1);
}

t_vect cross(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}


double		vect_dot(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double sqrt(double x)
{
	double		res;
	double		tmp;
	int			i;

	res = x / 2;
	tmp = 0;
	i = 0;
	while (res != tmp && i < 20)
	{
		tmp = res;
		res = (x / tmp + tmp) / 2;
		i++;
	}
	return (res);
}

double		vector_magnitude(t_vect v)
{
	return (sqrt(vect_dot(v, v)));
}

t_vect vector_normalize(t_vect v)
{
	double		magnitude;

	magnitude = vector_magnitude(v);
	return (vect_scale(v, 1 / magnitude));
}

t_vect vector_negate(t_vect v)
{
	t_vect	v1;

	v1.x = -v.x;
	v1.y = -v.y;
	v1.z = -v.z;
	return (v1);
}
