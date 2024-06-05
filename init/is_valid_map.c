/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:31:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/05 15:32:25 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_elements(char *info)
{
	int		i;
	int		element;

	i = 0;
	element = 0;
	while (info && info[i])
	{
		while (info[i] == ' ' || info[i] == '\t')
			i++;
		if (info[i] != ' ' && info[i] != '\t' && info[i] != 0)
		{
			element++;
			while (info[i] != ' ' && info[i] != '\t' && info[i] != 0)
				i++;
		}
	}
	if (element < 2)
		return (map_error(info, NO_FILE, 1));
	else if (element > 2)
		return (map_error(info, TM_FILE, 1));
	return (0);
}

int	edit_wall(char **path, char *info)
{
	if (check_elements(info))
		return (1);
	if (*path != NULL)
		return (map_error("", TM_ELEMENT, 1));
	*path = get_path(info, 2);
	if (!path)
		return (1);
	return (0);
}

int	edit_back(int *color, char *info)
{

}
int	check_wall(t_cub *cub, char *info)
{
	int	i;
	int	res;

	i = 0;
	while (info[i] == ' ' || info[i] == '\t')
		i++;
	if (info[i] == 'N' && info[i + 1] == 'O' && info[i + 2] == ' ')
		res = edit_wall(&cub->scene->north, info);
	else if (info[i] == 'S' && info[i + 1] == 'O' && info[i + 2] == ' ')
		res = edit_wall(&cub->scene->south, info);
	else if (info[i] == 'W' && info[i + 1] == 'E' && info[i + 2] == ' ')
		res = edit_wall(&cub->scene->west, info);
	else if (info[i] == 'E' && info[i + 1] == 'A' && info[i + 2] == ' ')
		res = edit_wall(&cub->scene->east, info);
	else if (info[i] == 'F' && info[i + 1] == ' ')
		res = edit_back(&cub->scene->f_color, info);
	else if (info[i] == 'C'&& info[i + 1] == ' ')
		res = edit_back(&cub->scene->f_color, info);
	else
		res = 1;
	return (res);
}

int	is_valid_info(t_cub *cub, char **map)
{
	int	i;

	i = 0;
	while (map && map[i] && i < NB_ELEMENT)
	{
		if (check_wall(cub, map[i]))
			return (1);
		i++;
	}
	if (i != NB_ELEMENT)
		return (map_error("", TF_ELEMENT, 1));
	return (0);
}

int	init_scene(t_cub *cub, char **map)
{
	ft_bzero(cub->scene, sizeof(t_scene));
	if (is_valid_info(cub, map))
		return (1);
	if (is_valid_map(cub, map))
		return (1);
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

int	check_lines(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line && line[i] && count < NB_ELEMENT)
	{
		while (line[i] == '\n')
			i++;
		if (line[i] != '\n' && line[i] != 0)
			count++;
		while (line[i] != '\n' && line[i] != 0)
			i++;
	}
	if (count != NB_ELEMENT)
		return (1);
	while (line[i] == '\n')
		i++;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
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
	if (check_lines(line))
		return (map_error("", LINES, 1));
	scene = ft_split(line, '\n');
	free(line);
	if (!scene)
		return (perror("Error\n"), 1);
	if (init_scene(cub, scene))
		return (1);
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
