/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:09:58 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/08 16:51:39 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*buf;
	const char	*source;

	i = 0;
	buf = (char *)dest;
	source = (const char *)src;
	while (i < n && dest != src)
	{
		buf[i] = source[i];
		i++;
	}
	return (dest);
}
