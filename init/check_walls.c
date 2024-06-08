/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:53:04 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/07 11:19:29 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_topbot(char **map, int j)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (!cub_isspace(map[0][i]) && map[0][i] != '1')
			return (map_error("", WALLS, 1));
		i++;
	}
	i = 0;
	while (map[j][i])
	{
		if (!cub_isspace(map[j][i]) && map[j][i] != '1')
			return (map_error("", WALLS, 1));
		i++;
	}
	return (0);
}

static int check_arround(char **map, int i, int j)
{
	int	check;

	if (i == 0 || j == 0 || !map[i + 1])
		return (1);
	check = cub_isspace(map[i + 1][j]) + cub_isspace(map[i - 1][j]);
	check = check + cub_isspace(map[i][j - 1]) + cub_isspace(map[i][j + 1]);
	if (check)
		return (1);
	return (0);
}

static int check_midmap(char **map, int lim)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[++i] && i < lim)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				if (check_arround(map, i, j))
					return (map_error("", WALLS, 1));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_walls(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	i--;
	if (i < 3)
		return (map_error("", TOO_SMALL, 1));
	if (check_topbot(map, i))
		return (1);
	if (check_midmap(map, i))
		return (1);
	return (0);
}