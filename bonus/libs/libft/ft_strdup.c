/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:01:33 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/22 14:47:01 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	str = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + 1);
	if (!str)
		return (0);
	len = ft_strlen(s1);
	while (i <= len)
	{
		str[i] = '\0';
		i++;
	}
	ft_memcpy(str, s1, len);
	return (str);
}
