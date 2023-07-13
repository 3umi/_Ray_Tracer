/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:37 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 05:15:54 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_BONUS_H
# define DATA_BONUS_H

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_object	*head;
	t_object	*object;
	t_camera	*camera;
	t_lighting	*lighting;
	t_img		img;
	t_ray		r;
	int			depth;
}				t_data;

#endif
