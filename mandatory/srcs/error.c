/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:06:48 by ohalim            #+#    #+#             */
/*   Updated: 2023/07/12 22:46:14 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	__exit_error(char *str)
{
	if (!str)
		exit (FAILURE_RETURN);
	write(2, str, ft_strlen(str));
	exit(FAILURE_RETURN);
}
