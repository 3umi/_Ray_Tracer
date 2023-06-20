/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:29:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/20 14:11:00 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "objects.h"

typedef struct	s_ray
{
	t_vect	origin;
	t_vect	direction;
}				t_ray;

// t_ray			ray_new(t_vect origin, t_vect direction);
t_ray ray_new(t_camera *cam, double x, double y);
t_vect			ray_at(t_ray *r, double t);
t_color	ray_color(t_ray *r, t_object *obj, int depth);

#endif
