/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:29:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:17:46 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_BONUS_H
# define RAY_BONUS_H

typedef struct s_ray
{
	t_vect	origin;
	t_vect	direction;
	double	t_min;
	double	t_max;
}			t_ray;

t_ray	ray_new(t_camera *cam, double x, double y);
t_vect	ray_hit_point(t_ray *r, double t);

#endif
