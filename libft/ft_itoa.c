/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:04:07 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/08 14:09:42 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_power(int n, int power)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	while (i < power)
	{
		result *= n;
		i++;
	}
	return (result);
}

char	*ft_itoa(int nbr)
{
	int			i;
	int			dec;
	char		*str;
	long int	nb;

	dec = ft_nbrlen(nbr);
	str = (char *)malloc(sizeof(char) * (dec + 1));
	nb = nbr;
	if (!str)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		str[0] = '-';
		nb = nb * -1;
		i++;
	}
	while (i < dec)
	{
		str[i] = nb / ft_power(10, (dec - i - 1)) + 48;
		nb = nb - (str[i] - 48) * ft_power(10, (dec - i - 1));
		i++;
	}
	str[i] = '\0';
	return (str);
}
