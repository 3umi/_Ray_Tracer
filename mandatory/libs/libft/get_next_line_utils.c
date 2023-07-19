/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:30:50 by belkarto          #+#    #+#             */
/*   Updated: 2022/11/29 17:14:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = (char *) malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!str)
		return (0);
	while (i <= len)
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1 && s1[++i] != '\0')
		str[i] = s1[i];
	free(s1);
	i = -1;
	while (s2 && s2[++i] != '\0')
		str[i + len_s1] = s2[i];
	str[len_s1 + len_s2] = 0;
	return (str);
}
