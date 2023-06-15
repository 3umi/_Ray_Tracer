/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hited.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:29:00 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/15 10:25:20 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITED_H
# define HITED_H
# include "vectors.h"
# include "ray.h"
# include "objects.h"

//hit record
typedef struct s_hitrecod
{
	t_vect		p;
	t_vect		normal;
	t_vect		color;
	bool		color_set;
	double		t;
	bool		front_face;
}				t_hitrecod;

typedef struct	s_hittable_list
{
	int size;
	int capacity;
	t_object		*objects;
	struct s_hittable_list	*next;
}				t_hittable_list;

bool			hit(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj);
bool			hit_sphere(t_ray *r, double t_min, double t_max, t_hitrecod *rec, t_object *obj);
void			set_face_normal(t_ray *r, t_hitrecod *rec);
bool hittable_list_hit(t_object *list, t_ray *r, double t_min, double t_max, t_hitrecod *rec);

#endif
