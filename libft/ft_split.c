/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:09:23 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/09 12:03:27 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *s, char sep)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (s[i] && s[i] != sep)
		{
			count++;
			while (s[i] && s[i] != sep)
				i++;
		}
	}
	return (count);
}

static char	*ft_mallocword(const char *s, char sep)
{
	unsigned int	i;
	char			*res;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	res = (char *)malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != sep)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**ft_free_tab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(const char *s, char sep)
{
	unsigned int	i;
	char			**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countwords(s, sep) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		if (*s && *s != sep)
		{
			tab[i] = ft_mallocword(s, sep);
			if (!tab[i])
				return (ft_free_tab(tab));
			i++;
			while (*s && *s != sep)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
