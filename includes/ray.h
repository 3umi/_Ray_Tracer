/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:29:17 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/10 19:39:42 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct	s_ray
{
	t_vect	origin;
	t_vect	direction;
}				t_ray;

t_ray			ray_new(t_vect origin, t_vect direction);

#endif
