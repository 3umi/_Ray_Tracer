/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:29:41 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/31 07:16:42 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	else
		return (write(fd, s, ft_strlen(s)));
}
