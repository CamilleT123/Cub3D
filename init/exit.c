/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:47:01 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/19 14:41:07 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "init.h"

int	map_error(char *s1, char *s2, int status)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	return (status);
}

int	map_ext_error(char *s1, char *s2, int status)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": extension ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(" expected\n", 2);
	return (status);
}

int	exit_map(t_cub *cub, int status)
{
	if (cub->scene.map)
		ft_freetab(cub->scene.map);
	cub->scene.map = NULL;
	if (cub->scene.east)
		free(cub->scene.east);
	cub->scene.east = NULL;
	if (cub->scene.west)
		free(cub->scene.west);
	cub->scene.west = NULL;
	if (cub->scene.north)
		free(cub->scene.north);
	cub->scene.north = NULL;
	if (cub->scene.south)
		free(cub->scene.south);
	cub->scene.south = NULL;
	return (status);
}
