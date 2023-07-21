/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:37:07 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 01:51:51 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT_bonus.h"

void	initialize_rotated_ray(t_ray *rotated_ray, t_ray r, t_mat4 mat)
{
	rotated_ray->direction = mat4_mult_vect(mat, r.direction);
	rotated_ray->origin = mat4_mult_vect(mat, r.origin);
	rotated_ray->t_max = r.t_max;
	rotated_ray->t_min = r.t_min;
}

t_vect	calculate_normal(t_hitrecod *rec, t_cylinder *cy)
{
	t_vect	normal;
	double	y;
	t_mat4	mat;

	mat = mat4_rotate(vect_scale(cy->normal, -1));
	y = rec->p.y - cy->center.y;
	if (y <= -cy->height / 2 || y >= cy->height / 2)
		normal = vect_normalize(mat4_mult_vect(mat, cy->normal));
	else
		normal = vect_normalize(mat4_mult_vect(mat,
					vect_unit(vect_sub(vect_sub(rec->p, cy->center),
							vect_scale(cy->normal, y)))));
	return (normal);
}
