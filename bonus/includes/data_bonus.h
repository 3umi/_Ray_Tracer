/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:37 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/19 15:24:30 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_BONUS_H
# define DATA_BONUS_H

typedef struct s_switch
{
	bool		checkboard_plane;
	bool		specular;
	bool		sphere_gradient;
	bool		cylinder_gradient;
}				t_switch;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_object	*head;
	t_object	*object;
	t_camera	*camera;
	t_lighting	*lighting;
	t_img		img;
	t_img		menu_img;
	t_img		empty_img;
	t_ray		r;
	t_switch	switches;
}				t_data;

#endif
