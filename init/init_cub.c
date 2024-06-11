/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:31:25 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/11 15:53:41 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file(char *file, char *ext)
{
	int	fd;

	if (check_extension(file, ext))
		return (1);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), map_error(file, IS_DIR, 1));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\n", 2), perror(file), 1);
	close(fd);
	return (0);
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
	scene = ft_split(line, '\n');
	if (!scene)
		return (perror("Error\n"), free(line), 1);
	if (init_scene(cub, scene))
		return (ft_freetab(scene), free(line), 1);
	if (check_lines(line))
		return (ft_freetab(scene), free(line), map_error("", LINES, 1));
	free(line);
	ft_freetab(scene);
	return (0);
}
