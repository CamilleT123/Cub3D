/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:09:22 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/05 21:05:34 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_info(t_cub *cub, char *info)
{
	int	i;
	int	res;

	i = 0;
	while (cub_isspace(info[i]))
		i++;
	if (info[i] == 'N' && info[i + 1] == 'O' && cub_isspace(info[i + 2]))
		res = edit_wall(&cub->scene.north, info);
	else if (info[i] == 'S' && info[i + 1] == 'O' && cub_isspace(info[i + 2]))
		res = edit_wall(&cub->scene.south, info);
	else if (info[i] == 'W' && info[i + 1] == 'E' && cub_isspace(info[i + 2]))
		res = edit_wall(&cub->scene.west, info);
	else if (info[i] == 'E' && info[i + 1] == 'A' && cub_isspace(info[i + 2]))
		res = edit_wall(&cub->scene.east, info);
	else if (info[i] == 'F' && cub_isspace(info[i + 1]))
		res = edit_back(&cub->scene.f_color, info);
	else if (info[i] == 'C'&& cub_isspace(info[i + 1]))
		res = edit_back(&cub->scene.c_color, info);
	else
		res = 1;
	return (res);
}

static int	is_valid_map(t_cub *cub, char **map)
{

	(void)cub;
	(void)map;
	return (0);
}

static int	is_valid_info(t_cub *cub, char **map)
{
	int	i;

	i = 0;
	while (map && map[i] && i < NB_ELEMENT)
	{
		if (check_info(cub, map[i]))
			return (1);
		i++;
	}
	if (i != NB_ELEMENT)
		return (map_error("", TF_ELEMENT, 1));
	return (0);
}

int	init_scene(t_cub *cub, char **map)
{
	ft_bzero(&cub->scene, sizeof(t_scene));
	cub->scene.f_color = -1;
	cub->scene.c_color = -1;
	if (is_valid_info(cub, map))
		return (1);
	if (is_valid_map(cub, map))
		return (1);
	return (0);
}
