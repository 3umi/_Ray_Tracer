/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:18:25 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/30 04:10:18 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_strrev(char *str)
{
	int		len;
	int		i;
	char	c;

	len = ft_strlen(str) - 1;
	i = 0;
	while (i < len)
	{
		c = str[i];
		str[i++] = str[len];
		str[len--] = c;
	}
}
