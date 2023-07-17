/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:49:52 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/31 08:13:12 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_hex(unsigned long nb, int cap)
{
	char	*hex;
	char	*arr;
	int		tmp;
	int		i;

	i = 0;
	if (cap == 1)
		hex = ft_strdup("0123456789ABCDEF");
	else
		hex = ft_strdup("0123456789abcdef");
	arr = ft_calloc(17, sizeof(char));
	while (nb > 0)
	{
		tmp = nb % 16;
		arr[i++] = hex[tmp];
		nb /= 16;
	}
	free(hex);
	return (arr);
}

char	*ft_tohex(unsigned long nb, int cap)
{
	char	*arr;
	char	*ptr;

	if (nb == 0)
		return (ft_strdup("0"));
	arr = ft_hex(nb, cap);
	ft_strrev(arr);
	ptr = ft_strdup(arr);
	free(arr);
	return (ptr);
}
