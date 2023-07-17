/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:51:42 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/18 21:36:02 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_des;
	size_t	len_src;

	i = 0;
	j = 0;
	len_des = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize == 0 || dstsize <= len_des)
		return (len_src + dstsize);
	while (src[j] != '\0' && j < dstsize - len_des - 1)
	{
		dst[i + len_des] = src[j];
		i++;
		j++;
	}
	dst[i + len_des] = '\0';
	return (len_des + len_src);
}
