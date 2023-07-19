/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:10:30 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/18 00:59:41 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_BONUS_H
# define OBJECTS_BONUS_H

typedef enum e_type
{
	NONE,
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE
}				t_type;

typedef struct s_qua_sol
{
	double		t1;
	double		t2;
	double		delta;
}				t_qua_sol;

typedef struct s_sphere
{
	t_vect		center;
	double		radius;
	double		diameter;
	t_color		color_a;
	t_color		color_b;
}				t_sphere;

typedef struct s_plane
{
	t_vect		normal;
	t_vect		point;
	double		distance;
	t_color		color_a;
	t_color		color_b;
}				t_plane;

typedef struct s_cylinder
{
	t_vect		center;
	t_vect		normal;
	double		radius;
	double		diameter;
	double		height;
	t_color		color_a;
	t_color		color_b;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vect		point_a;
	t_vect		point_b;
	t_vect		point_c;
	t_vect		normalized;
	t_color		color_a;
	t_color		color_b;
}	t_triangle;

typedef struct s_object
{
	t_type			type;
	void			*object;
	struct s_object	*next;
}				t_object;

t_sphere	*sphere_new(t_vect center, double radius);
#endif
