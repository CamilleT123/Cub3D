/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:21:25 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/13 11:21:39 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	n;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	n = nmemb * size;
	if (n / size != nmemb)
		return (NULL);
	result = malloc(n);
	if (!result)
		return (NULL);
	ft_bzero(result, n);
	return (result);
}
