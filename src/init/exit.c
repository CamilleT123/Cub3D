/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:47:01 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/28 16:18:14 by ctruchot         ###   ########.fr       */
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
	if (cub->scene.east)
		free(cub->scene.east);
	if (cub->scene.west)
		free(cub->scene.west);
	if (cub->scene.north)
		free(cub->scene.north);
	if (cub->scene.south)
		free(cub->scene.south);
	ft_bzero(&cub->scene, sizeof(t_scene));
	return (status);
}
