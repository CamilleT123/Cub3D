/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:09:22 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/26 17:25:37 by aduvilla         ###   ########.fr       */
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
	else if (info[i] == 'C' && cub_isspace(info[i + 1]))
		res = edit_back(&cub->scene.c_color, info);
	else
		res = (map_error(&info[i], VALID_COORD, 1));
	return (res);
}

static int	is_valid_info(t_cub *cub, char **map)
{
	int	i;

	i = 0;
	if (check_file(DOORPATH, ".xpm"))
		return (1);
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

static int	check_map(t_cub *cub)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (cub->scene.map && cub->scene.map[i])
	{
		j = 0;
		while (cub->scene.map[i][j])
		{
			c = cub->scene.map[i][j];
			if (!is_mapchar(c) && !is_startchar(c) && c != ' ')
				return (map_error("", FORBIDDEN_CHAR, 1));
			j++;
		}
		i++;
	}
	if (only_goodchar(&cub->scene))
		return (1);
	if (check_walls(cub->scene.map))
		return (1);
	return (0);
}

static int	is_valid_map(t_cub *cub, char **map)
{
	cub->scene.map = tab_dup(&map[6]);
	if (!cub->scene.map)
		return (map_error("", MALLOC, 1));
	if (check_map(cub))
		return (1);
	return (0);
}

int	init_scene(t_cub *cub, char **ar_scene)
{
	ft_bzero(&cub->scene, sizeof(t_scene));
	cub->scene.f_color = -1;
	cub->scene.c_color = -1;
	if (is_valid_info(cub, ar_scene))
		return (exit_map(cub, 1));
	if (is_valid_map(cub, ar_scene))
		return (exit_map(cub, 1));
	return (0);
}
