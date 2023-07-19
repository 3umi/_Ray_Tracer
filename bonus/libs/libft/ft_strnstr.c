/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:59:07 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/09 21:04:57 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	str = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (str);
	i = 0;
	while (i < len && haystack[i])
	{
		k = i;
		j = 0;
		while (str[k] == needle[j] && k < len)
		{
			if (needle[j + 1] == '\0')
				return (&str[i]);
			k++;
			j++;
		}
		i++;
	}
	return (NULL);
}
