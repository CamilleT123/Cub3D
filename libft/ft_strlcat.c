/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:12:36 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/08 17:48:42 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	sdest;

	if (!dst && size == 0)
		return (ft_strlen(src));
	sdest = ft_strlen(dst);
	i = 0;
	if (size == 0 || size <= sdest)
		return (ft_strlen(src) + size);
	while (i + sdest < size - 1 && src[i])
	{
		dst[i + sdest] = src[i];
		i++;
	}
	dst[i + sdest] = '\0';
	return (ft_strlen(src) + sdest);
}
