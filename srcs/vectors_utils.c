/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:08:57 by brahim            #+#    #+#             */
/*   Updated: 2023/06/11 19:48:00 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

t_vect		vector_add(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vect		vector_sub(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vect		vector_mult(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vect		vector_div(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}

t_vect		vector_scale(t_vect v, double c)
{
	t_vect	v1;

	v1.x = v.x * c;
	v1.y = v.y * c;
	v1.z = v.z * c;
	return (v1);
}

t_vect vector_cross(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}


double		vector_dot(t_vect v1, t_vect v2)
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
	return (sqrt(vector_dot(v, v)));
}

t_vect vector_normalize(t_vect v)
{
	double		magnitude;

	magnitude = vector_magnitude(v);
	return (vector_scale(v, 1 / magnitude));
}

t_vect vector_negate(t_vect v)
{
	t_vect	v1;

	v1.x = -v.x;
	v1.y = -v.y;
	v1.z = -v.z;
	return (v1);
}

t_vect vector_new(double x, double y, double z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vect	vector_copy(t_vect v)
{
	t_vect	v1;

	v1.x = v.x;
	v1.y = v.y;
	v1.z = v.z;
	return (v1);
}
