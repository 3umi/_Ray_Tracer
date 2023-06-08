/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:20:24 by belkarto          #+#    #+#             */
/*   Updated: 2022/10/24 11:09:28 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	number_count(long int n)
{
	int	i;

	i = 0;
	if (n <= 9 && n >= 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	string_of_number(char *s, int i, long int n)
{
	if (n >= 0)
	{
		while (i > 0)
		{
			s[i - 1] = n % 10 + 48;
			n /= 10;
			i--;
		}
	}
	else
	{
		n *= -1;
		while (i > 0)
		{
			s[i] = n % 10 + 48;
			n /= 10;
			i--;
		}
		s[0] = '-';
	}
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nbr;

	nbr = n;
	if (nbr < 0)
		i = number_count(-nbr);
	else
		i = number_count(nbr);
	if (n < 0)
	{
		str = (char *)ft_calloc((i + 2), sizeof(char));
		if (!str)
			return (NULL);
		string_of_number(str, i, nbr);
	}
	else
	{
		str = (char *)ft_calloc((i + 1), sizeof(char));
		string_of_number(str, i, nbr);
	}
	return (str);
}
