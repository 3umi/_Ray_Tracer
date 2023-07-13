/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:54:49 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/24 12:15:53 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_checker(const char *set, int c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_begi(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (ft_checker(set, s1[i]) == 1)
		i++;
	return (i);
}

static int	ft_end(const char *s1, const char *set)
{
	int	i;
	int	end;

	end = 0;
	i = ft_strlen(s1) - 1;
	while (ft_checker(set, s1[i]) == 1)
	{
		i--;
		end++;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	begi;
	size_t	last;
	int		str_len;

	if (!s1 || !set)
		return (0);
	begi = ft_begi(s1, set);
	last = ft_end(s1, set);
	str_len = ft_strlen(s1) - begi - last;
	str = ft_substr(s1, begi, str_len);
	return (str);
}
