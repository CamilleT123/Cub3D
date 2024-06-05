/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:31:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/05 22:07:27 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int check_file(char *file, char *ext)
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

static int	check_lines(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && count < NB_ELEMENT)
	{
		if (line[i] != '\n' && line[i] != 0)
			count++;
		while (line[i] != '\n' && line[i] != 0)
			i++;
		while (line[i] == '\n')

			i++;
	}
	if (count != NB_ELEMENT)
		return (map_error("", TF_ELEMENT, 1));
	count = ft_strlen(line) - 1;
	while (line[count] == '\n')
		count--;
	i--;
	while (line[++i] && i < count)
		if (line[i] == '\n' && line[i + 1] == '\n')
			return (1);
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
		return (free(line), map_error("", LINES, 1));
	scene = ft_split(line, '\n');
	free(line);
	if (!scene)
		return (perror("Error\n"), 1);
	if (init_scene(cub, scene))
		return (1);
	ft_freetab(scene);
	return (0);
}
