/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hited_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:16:12 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITED_BONUS_H
# define HITED_BONUS_H

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
	t_object	*obj;
}				t_hitrecod;

bool	hit(t_data *data, t_hitrecod *rec, t_object *obj);
bool	hit_sphere(t_data *data, t_hitrecod *rec, t_object *obj);
bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj);
void	set_face_normal(t_ray *r, t_hitrecod *rec);
bool	hittable_list_hit(t_data *data, t_hitrecod *rec);

#endif
