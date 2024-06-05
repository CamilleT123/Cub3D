/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:31:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/05 11:46:33 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strspaceless(char *str)
{
	char	*spl;
	int		i;
	int		len;
	
	i = 0;
	len = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			len++;
		i++;
	}
	spl = malloc(sizeof(char) * len + 1);
	if (!spl)
		return (map_error("", MALLOC, 1), NULL);
	i = 0;
	len = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			spl[len++] = str[i]; // tentative de ++ le len apres !!!!
		i++;
	}
	spl[len] = '\0';
	return (spl);
}

char	*get_path(char *info)
{
	char	*path;
	int		i;

	path = strspaceless(info);
	while (path && *path >= 'A' && *path <= 'Z')
		path++;
	while (info && info[i])
	{
		while (info[i] == ' ' || info[i] == '\t')
			i++;
		while (info[i] >= 'A' && info[i] <= 'Z')
			i++;
		while (info[i] == ' ' || info[i] == '\t')
			i++;
		


	}
}
int	edit_wall(void **sprite, char *info)
{
	char *path;

	path = get_path(info);
	if (!*sprite)
	{
		*sprite
	}
}

int	is_valid_map(t_cub *cub, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ' || map[i][j] == '\t')
				j++;
			if (map[i][j] == 'N' && map[i][j + 1] == 'O')
				edit_wall(cub->scene->north, map[i]);
			else if (map[i][j] == 'S' && map[i][j + 1] == 'O')
				edit_wall(cub->scene->south, map[i]);
			else if (map[i][j] == 'W' && map[i][j + 1] == 'E')
				edit_wall(cub->scene->west, map[i]);
			else if (map[i][j] == 'E' && map[i][j + 1] == 'A')
				edit_wall(cub->scene->east, map[i]);
			else if (map[i][j] == 'F' && map[i][j + 1] == ' ')
				test_n(map, i);
			else if (map[i] == 'C')
				test_n(map, i);
			else
				return (exit_map(cub, map, 1));
		}
		i++;
	}
	return (0);
}

int check_file(char *file, char *ext)
{
	int	f;
	int	e;
	int	fd;

	if (!file || !ext)
		return (1);
	f = ft_strlen(file) - 1;
	e = ft_strlen(ext) - 1;
	while (f >= e && e >= 0)
	{
		if (file[f] != ext[e])
			return (map_error(file, EXTENSION, 1));
		e--;
		f--;
	}
	fd = open(file, O_DIRECTORY);
	if (fd == -1)
		return (0);
	close(fd);
	return (map_error(file, IS_DIR, 1));
	// check permissions !!!!
}

int	init_cub(char *file, t_cub *cub)
{
	char	*line;
	char	**scene;

	ft_bzero(cub, sizeof(t_cub));
	if (check_file(file, ".cub"))
		return (1);
	line = get_all_lines(file);
	if (!line)
		return (perror("Error\n"), 1);
	scene = ft_split(line, '\n');
	free(line);
	if (!scene)
		return (perror("Error\n"), 1);
	ft_putar(scene);

	return (0);
}
/*
	if (ft_strncmp(line, "", 1) == 0)
		return (ft_error('m'), free(line), NULL);
	if (is_no_empty_line(line))
		return (ft_error('s'), free(line), NULL);
	if (check_map_char(line))
		return (ft_error('l'), free(line), NULL);
	game->map = ft_split(line, '\n');
	if (!game->map)
		return (free(line), perror("Error\n"), NULL);
	free(line);
	if (!check_map(game))
		return (NULL);
	return (game->map);
}
*/
