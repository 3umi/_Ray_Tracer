/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:31:21 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/14 15:22:37 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "vectors.h"
# include "colors.h"
# include "ray.h"

typedef enum e_type
{
	NONE,
	SPHERE,
	PLANE,
	CYLINDER
}				t_type;

typedef struct s_sphere
{
	t_vect		center;
	double		radius;
	double		diameter;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_vect		normal;
	t_vect		point;
	double		distance;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vect		center;
	t_vect		normal;
	double		radius;
	double		diameter;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct s_object
{
	int			type;
	void		*object;
}				t_object;

t_sphere	*sphere_new(t_vect center, double radius);
#endif
