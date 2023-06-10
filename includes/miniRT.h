/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:14 by brahim            #+#    #+#             */
/*   Updated: 2023/06/10 18:12:53 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "vectors.h"
# include "../libs/libft/libft.h"
# include "image.h"

# define WIN_W 500
# define WIN_H 500

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;


#endif
