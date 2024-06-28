/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:31 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/28 16:58:52 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "init.h"

static int	check_elements(char *info)
{
	int		i;
	int		element;

	i = 0;
	element = 0;
	while (info && info[i])
	{
		while (cub_isspace(info[i]))
			i++;
		if (info[i] && !cub_isspace(info[i]))
		{
			element++;
			while (info[i] && !cub_isspace(info[i]))
				i++;
		}
	}
	if (element < 2)
		return (map_error(info, NO_FILE, 1));
	else if (element > 2)
		return (map_error(info, TM_FILE, 1));
	return (0);
}

static int	check_colors(char **code)
{
	int	i;
	int	j;

	i = 0;
	while (code && code[i])
	{
		if (i > 2)
			return (map_error("", TM_NUM, 1));
		j = 0;
		while (code[i][j])
		{
			if (j > 2)
				return (map_error(code[i], BIG_NUM, 1));
			if (!ft_isdigit(code[i][j]))
				return (map_error(code[i], INVALID_NUM, 1));
			j++;
		}
		i++;
	}
	if (i < 3)
		return (map_error("", TF_NUM, 1));
	return (0);
}

static int	get_color(char **code)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = ft_atoi(code[0]);
	if (r < 0 || r > 255)
		return (map_error(code[0], BIG_NUM, -1));
	g = ft_atoi(code[1]);
	if (g < 0 || g > 255)
		return (map_error(code[1], BIG_NUM, -1));
	b = ft_atoi(code[2]);
	if (b < 0 || b > 255)
		return (map_error(code[2], BIG_NUM, -1));
	color = r * 65536 + g * 256 + b;
	return (color);
}
//	color = (r << 16) + (g << 8) + b;

int	edit_wall(char **path, char *info)
{
	if (*path != NULL)
		return (map_error(info, TM_ELEMENT, 1));
	if (check_elements(info))
		return (1);
	*path = get_path(info, 2);
	if (!*path)
		return (1);
	if (check_file(*path, ".xpm"))
		return (1);
	return (0);
}

int	edit_back(int *color, char *info)
{
	char	**code;
	char	*path;

	if (*color >= 0)
		return (map_error(info, TM_ELEMENT, 1));
	path = get_path(info, 1);
	if (!path)
		return (1);
	code = ft_split(path, ',');
	free(path);
	if (!code)
		return (map_error("", MALLOC, 1));
	if (check_colors(code))
		return (ft_freetab(code), 1);
	*color = get_color(code);
	ft_freetab(code);
	if (*color < 0)
		return (1);
	return (0);
}
