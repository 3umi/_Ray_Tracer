/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:11:13 by belkarto          #+#    #+#             */
/*   Updated: 2023/07/21 19:17:35 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_UTILS_BONUS_H
# define CHAR_UTILS_BONUS_H

int	__2d_len(char **tab);

typedef struct s_atod_utils
{
	double	result;
	double	decimal;
	bool	hasdecimal;
	int		sign;
}			t_atod_utils;

#endif
