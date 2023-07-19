/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:05:25 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/19 18:06:10 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	does_t(t_ray r, double t, t_cylinder *cy)
{
	return ((t >= 0
			&& (t * r.direction.y + r.origin.y >= cy->center.y - cy->height / 2)
			&& (t * r.direction.y + r.origin.y
				<= cy->center.y + cy->height / 2)));
}

void	initialize_rotated_ray(t_ray *rotated_ray, t_ray r, t_mat4 mat)
{
	rotated_ray->direction = mat4_mult_vect(mat, r.direction);
	rotated_ray->origin = mat4_mult_vect(mat, r.origin);
	rotated_ray->t_max = r.t_max;
	rotated_ray->t_min = r.t_min;
}

t_vect	calculate_normal(t_hitrecod *rec, t_cylinder *cy, t_mat4 mat, double y)
{
	t_vect	normal;

	if (y <= -cy->height / 2 || y >= cy->height / 2)
		normal = vect_normalize(mat4_mult_vect(mat, cy->normal));
	else
		normal = vect_normalize(mat4_mult_vect(mat,
					vect_unit(vect_sub(vect_sub(rec->p, cy->center),
							vect_scale(cy->normal, y)))));
	return (normal);
}
