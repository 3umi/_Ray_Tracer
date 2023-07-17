/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:48 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/13 05:18:45 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_bonus.h"

void	__exit_error(char *str)
{
	if (!str)
		exit (FAILURE_RETURN);
	write(2, str, ft_strlen(str));
	exit(FAILURE_RETURN);
}
