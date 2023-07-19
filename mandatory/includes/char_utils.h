/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:51:52 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/19 16:49:31 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_UTILS_H
# define CHAR_UTILS_H

int	__2d_len(char **tab);

typedef struct s_atod_utils
{
	double	result;
	double	decimal;
	int		sign;
	int		hasdecimal;
}			t_atod_utils;

#endif
