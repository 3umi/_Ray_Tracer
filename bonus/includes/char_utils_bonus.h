/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:13 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 03:22:21 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_UTILS_BONUS_H
# define CHAR_UTILS_BONUS_H

int	__2d_len(char **tab);

typedef struct s_atod_utils
{
	double	result;
	double	decimal;
	int		sign;
}			t_atod_utils;

#endif
