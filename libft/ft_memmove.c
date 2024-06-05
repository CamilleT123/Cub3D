/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:00 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/06 16:44:53 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*source;
	char	*res;

	source = (char *)src;
	res = (char *)dest;
	if (!dest && !src)
		return (dest);
	if (src < dest)
		while (n--)
			res[n] = source[n];
	else
	{
		while (n--)
			*res++ = *source++;
	}
	return (dest);
}
