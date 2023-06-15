/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:29:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/15 15:00:29 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct	s_ray
{
	t_vect	origin;
	t_vect	direction;
}				t_ray;

// t_ray			ray_new(t_vect origin, t_vect direction);
t_ray ray_new(t_camera *cam, double x, double y);
t_vect			ray_at(t_ray *r, double t);

#endif
