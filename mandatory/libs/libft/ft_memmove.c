/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:27:01 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/21 11:33:11 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*p_dst;
	char	*p_src;

	p_dst = dst;
	p_src = (char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			p_dst[len - 1] = p_src[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return ((void *)dst);
}
