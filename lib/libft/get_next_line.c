/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:49:23 by belkarto          #+#    #+#             */
/*   Updated: 2022/11/29 18:02:05 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_nl(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_line(char *str, char *str1)
{
	char	*p;
	int		i;

	i = 0;
	free(str1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	p = ft_substr(str, 0, i);
	if (p && *p == '\0')
		return (NULL);
	return (p);
}

static char	*ft_rest(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '\n')
			break ;
	}
	ptr = ft_substr(str, i, ft_strlen(str) - i);
	free (str);
	if (ptr && ptr[0] == 0)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

static char	*ft_dup(char *line, char *str)
{
	free(str);
	return (ft_strdup_gnl(line));
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line = NULL;
	int			readed;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0 || BUFFER_SIZE == 2147483647)
		return (NULL);
	str = malloc(BUFFER_SIZE + 1);
	while (1)
	{
		if (find_nl(line) == 1)
			break ;
		readed = read(fd, str, BUFFER_SIZE);
		if (readed == -1 || readed == 0)
		{
			tmp = ft_dup(line, str);
			line = NULL;
			return (tmp);
		}
		str[readed] = '\0';
		line = ft_strjoin_gnl(line, str);
	}
	tmp = ft_line(line, str);
	line = ft_rest(line);
	return (tmp);
}
