/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:32:24 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/31 17:44:13 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putuint(unsigned int n)
{
	if (n < 10)
		ft_putchar_fd(n + 48, 1);
	else
	{
		ft_putuint(n / 10);
		ft_putchar_fd(n % 10 + 48, 1);
	}
	return (ft_intlen(n));
}
