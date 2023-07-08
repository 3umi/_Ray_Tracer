/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:54:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/08 07:43:55 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* double	cy_distance(t_data *data, t_cylinder *cy)
{
	t_vect	V;
	t_vect	projV;
	t_vect	N;
	double	dotVD;
	double	N_len;

	V = vect_sub(cy->center, data->r.origin);
	dotVD = vect_dot(V, data->r.direction);
	projV = vect_scale(data->r.direction, (vect_dot(V, data->r.direction) / vect_dot(data->r.direction, data->r.direction)));
	N = vect_sub(V, projV);
	N_len = vect_length(N);
	if (N_len > cy->radius)
		return (-1.0);
	return (0.0);
}

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	(void)data;
	(void)rec;
	(void)obj;

	t_cylinder	*cy;

	cy = obj->object;
	// rec->hit_point_distance = cy_distance();
	return (true);
} */

// bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
// {
// 	(void)rec;
// 	float		a;
// 	float		b;
// 	float		c;
	
// 	t_cylinder	*cy;
	
// 	cy = obj->object;

// 	a = (data->r.direction.x * data->r.direction.x) + (data->r.direction.z * data->r.direction.z);
// 	b = 2.0 * (data->r.direction.x * (data->r.origin.x - cy->center.x) + data->r.direction.z * (data->r.origin.z - cy->center.z));
// 	c = (data->r.origin.x - cy->center.x) * (data->r.origin.x - cy->center.x) + (data->r.origin.z - cy->center.z) * (data->r.origin.z - cy->center.z) - (cy->radius * cy->radius);

// 	float		delta;

// 	delta = (b * b) - 4 * (a * c);
// 	if (delta < 0)
// 	{
// 		printf("ok1\n");
// 		return (false);
// 	}
// 	float	t1 = (-b - sqrt(delta)) / (2 * a);
//     float	t2 = (-b + sqrt(delta)) / (2 * a);
    
//     if (t1 > t2)
// 	{
// 		double temp = t1;
// 		t1 = t2;
// 		t2 = temp;
// 	}
    
//     double y1 = data->r.origin.y + t1 * data->r.direction.y;
//     double y2 = data->r.origin.y + t2 * data->r.direction.y;
    
//     if ((y1 < cy->center.y || y1 > cy->center.y + cy->height) && (y2 < cy->center.y || y2 > cy->center.y + cy->height))
// 	{
// 		printf("ok2\n");
//         return false;  // No intersection with the finite cy
//     }
// 	rec->p = vect_new(0, 0, 1);
// 	rec->type = CYLINDER;
// 	rec->normal = cy->normal;
// 	rec->color = cy->color;
// 	rec->obj = obj;
// 	return (true);
// }

bool	hit_cylinder(t_data *data, t_hitrecod *rec, t_object *obj)
{
	double		discriminant;
	double		a;
	double		b;
	double		c;
	t_cylinder	*cy;

	cy = obj->object;
	a = pow(data->r.direction.x, 2) + pow(data->r.direction.z, 2);
	b = 2 * (data->r.direction.x * (data->r.origin.x - cy->center.x) + data->r.direction.z * (data->r.origin.z - cy->center.z));
	c = pow(data->r.origin.x - cy->center.x, 2) + pow(data->r.origin.z - cy->center.z, 2) - pow(cy->radius, 2);

	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant > 0)
	{
		rec->hit_point_distance = (-b - sqrt(discriminant)) / (2 * a);
		if (rec->hit_point_distance < 0)
			rec->hit_point_distance = (-b + sqrt(discriminant)) / (2 * a);
		rec->p = ray_hit_point(&data->r, rec->hit_point_distance);
		rec->normal = vect_unit(vect_sub(vect_sub(rec->p, cy->center), vect_scale(cy->normal, cy->height)));
		rec->type = CYLINDER;
		rec->color = cy->color;
		rec->obj = obj;
		return (true);
	}
	return (false);
}

