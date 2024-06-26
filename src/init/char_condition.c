/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:15:12 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/26 18:18:15 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	is_startchar(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	is_mapchar(char c)
{
	if (c == '0' || c == '1' || c == '3')
		return (1);
	else
		return (0);
}

static void	init_start(t_scene *scene, char c, int i, int j)
{
	scene->start_x = j;
	scene->start_y = i;
	if (c == 'N')
		scene->start_angle = PI / 2;
	if (c == 'W')
		scene->start_angle = 0;
	if (c == 'S')
		scene->start_angle = 3 * PI / 2;
	if (c == 'E')
		scene->start_angle = PI;
}

int	only_goodchar(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (scene->map[i])
	{
		j = 0;
		while (scene->map[i][j])
		{
			if (is_startchar(scene->map[i][j]) && scene->start_x == 0)
				init_start(scene, scene->map[i][j], i, j);
			else if (is_startchar(scene->map[i][j]) && scene->start_x != 0)
				return (map_error("", TM_START, 1));
			else if (!is_mapchar(scene->map[i][j]) && scene->map[i][j] != ' ')
				return (map_error("", FORBIDDEN_CHAR, 1));
			j++;
		}
		i++;
	}
	if (scene->start_x == 0)
		return (map_error("", NO_START, 1));
	return (0);
}
