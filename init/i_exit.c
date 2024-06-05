/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:47:01 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/04 22:51:49 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "init.h"

int	map_error(char *s1, char *s2, int status)
{
	ft_putstr_fd("cub3d: map: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	return (status);
}
