/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:14:47 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/13 06:20:31 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_BONUS_H
# define IMAGE_BONUS_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width_int;
	int		height_int;
	double	width;
	double	height;
	double	aspect_ratio;
	int		samples_per_pixel;
	int		samples_count;
	double	u;
	double	v;
}				t_img;

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
