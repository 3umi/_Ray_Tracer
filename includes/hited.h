/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hited.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 02:29:00 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/28 09:10:16 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITED_H
# define HITED_H
# include "vectors.h"
# include "ray.h"
# include "objects.h"

//hit record
//p: hit point
//normal: normal vector 
//front_face: true if the ray is outside the object 
typedef struct s_hitrecod
{
	t_vect		p;
	t_vect		normal;
	t_color		color;
	t_type		type;
	double		hit_point_distance;
	bool		front_face;
}				t_hitrecod;

bool	hit(t_data *data, t_hitrecod *rec, t_object *obj);
bool	hit_sphere(t_data *data, t_hitrecod *rec, t_object *obj);
void	set_face_normal(t_ray *r, t_hitrecod *rec);
bool	hittable_list_hit(t_data *data, t_hitrecod *rec);

#endif
