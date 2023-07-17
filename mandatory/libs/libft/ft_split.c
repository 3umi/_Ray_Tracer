/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:23:21 by belkarto          #+#    #+#             */
/*   Updated: 2022/12/08 16:58:34 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	alloc_count(const char *str, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			counter++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (counter);
}

static int	string_alloc(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	**ft_free_str(char **str, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	ft_fill_str(char *str, const char *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;
	int		k;
	int		next;

	str = (char **)ft_calloc((alloc_count(s, c) + 1), sizeof(char *));
	if (!str || !s)
		return (0);
	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			next = string_alloc(s + i, c);
			str[k] = (char *)malloc((next + 1) * sizeof(char));
			if (!str[k])
				return (ft_free_str(str, k));
			else
				i += ft_fill_str(str[k++], s + i, next);
		}
	}
	return (str);
}
