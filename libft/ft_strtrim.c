/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:46:06 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/10 13:03:17 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issep(const char *sep, char c)
{
	size_t	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_lenspace(const char *s, const char *sep)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] && ft_issep(sep, s[i]))
		i++;
	while (s[i])
	{
		count++;
		i++;
	}
	i = ft_strlen(s) - 1;
	if (count != 0)
	{
		while (ft_issep(sep, s[i]))
		{
			count--;
			i--;
		}
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1)
		return (NULL);
	size = ft_lenspace(s1, set);
	res = (char *)malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (ft_issep(set, s1[i]))
		i++;
	while (j < size)
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
