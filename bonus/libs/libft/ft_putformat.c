/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 07:43:32 by belkarto          #+#    #+#             */
/*   Updated: 2022/11/29 16:45:22 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(va_list para, char c)
{
	char	*ptr;
	int		len;
	char	*tmp;

	if (c == 'x')
		ptr = ft_tohex(va_arg(para, unsigned int), 0);
	else if (c == 'X')
		ptr = ft_tohex(va_arg(para, unsigned int), 1);
	else
	{
		tmp = ft_tohex(va_arg(para, unsigned long), 0);
		ptr = ft_strjoin("0x", tmp);
		free(tmp);
	}
	len = ft_putstr_fd(ptr, 1);
	free(ptr);
	return (len);
}

static int	ft_format(va_list arg, char c)
{
	int	len;

	len = 1;
	if (c == 'd' || c == 'i')
		len = ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'p' || c == 'x' || c == 'X')
		len = ft_puthex(arg, c);
	else if (c == 'c')
		ft_putchar_fd(va_arg(arg, int), 1);
	else if (c == 's')
		len = ft_putstr_fd(va_arg(arg, char *), 1);
	else if (c == 'u')
		len = ft_putuint(va_arg(arg, unsigned int));
	else if (c == '%')
		ft_putchar_fd('%', 1);
	else
		return (0);
	return (len);
}

int	ft_putformat(const char *str, va_list args)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			counter += ft_format(args, str[i++ + 1]);
			i++;
		}
		else
			counter += write(1, &str[i++], 1);
	}
	return (counter);
}
