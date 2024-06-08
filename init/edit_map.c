/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:29:50 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/08 10:20:15 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_startchar(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	is_mapchar(char c)
{
	if (c == '0' || c == '1')
		return (1);
	else
		return (0);
}

static int	only_goodchar(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_startchar(map[i][j]) && count == 0)
				count++;
			else if (is_startchar(map[i][j]) && count > 0)
				return (map_error("", TM_START, 1));
			else if (!is_mapchar(map[i][j]) && !cub_isspace(map[i][j]))
				return (map_error("", FORBIDDEN_CHAR, 1));
			j++;
		}
		i++;
	}
	if (count == 0)
		return (map_error("", NO_START, 1));
	return (0);
}

int	check_map(t_cub *cub)
{
	if (only_goodchar(cub->scene.map))
		return (1);
	if (check_walls(cub->scene.map))
		return (1);
	// verif jouable
	// position joueur et direction
	return (0);
}
