/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:29:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 21:58:38 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "objects.h"

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
