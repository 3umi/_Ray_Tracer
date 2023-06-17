/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 01:50:17 by ohalim            #+#    #+#             */
/*   Updated: 2023/06/17 01:51:03 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	__2d_len(char **tab)
{
	int	len;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len++])
		;
	return (len - 1);
}
