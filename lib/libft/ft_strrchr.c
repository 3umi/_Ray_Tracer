/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:43:32 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/09 17:06:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*found;
	int		i;
	int		len;

	i = 0;
	found = NULL;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			found = (char *)&s[i];
		i++;
	}
	return (found);
}
