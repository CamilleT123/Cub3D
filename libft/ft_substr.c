/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:18:54 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/09 10:41:10 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) - start <= len)
		len = ft_strlen(s) - start;
	if (start <= ft_strlen(s))
		res = (char *)malloc(sizeof(char) * (len + 1));
	else
		res = (char *)malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	i = 0;
	if (start <= ft_strlen(s))
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
