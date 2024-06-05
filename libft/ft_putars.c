/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:40:41 by aduvilla          #+#    #+#             */
/*   Updated: 2024/01/20 15:05:21 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putars(char **tab, char sep)
{
	int	i;

	if (!tab || !sep)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		ft_putchar(sep);
		i++;
	}
}
