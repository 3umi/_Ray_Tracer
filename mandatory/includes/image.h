/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:10:15 by belkarto          #+#    #+#             */
/*   Updated: 2023/06/25 22:59:22 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
