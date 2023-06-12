/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:14 by brahim            #+#    #+#             */
/*   Updated: 2023/06/12 05:08:31 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../mlx/mlx.h"
# include "../libs/libft/libft.h"
# include "vectors.h"
# include "image.h"
# include "ray.h"

# define WIN_W 800
# define WIN_H 400

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;

# include "key_hook.h"

#endif
