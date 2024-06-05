/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:40:56 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/17 10:18:10 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (gnl_strlen(s) - start <= len)
		len = gnl_strlen(s) - start;
	if (start <= gnl_strlen(s))
		res = (char *)malloc(sizeof(char) * (len + 1));
	else
		res = (char *)malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	i = 0;
	if (start <= gnl_strlen(s))
	{
		while (i < len && s[start])
		{
			res[i] = s[start];
			i++;
			start++;
		}
	}
	res[i] = '\0';
	return (res);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2)) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] && s1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && s2)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*gnl_strnew(void)
{
	char	*res;

	res = malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}
