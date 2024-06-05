/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:45:06 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/04 22:18:35 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_all_lines(char *ber)
{
	int		fd;
	char	*buf;
	char	*line;
	char	*copy;

	fd = open(ber, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			break ;
		copy = line;
		line = ft_strjoin(line, buf);
		if (!line)
			return (close(fd), free(buf), free(copy), NULL);
		free(copy);
		free(buf);
	}
	close(fd);
	return (line);
}

char	**tab_dup(char **tab)
{
	int		i;
	char	**res;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		res[i] = ft_strdup(tab[i]);
		if (!res[i])
			return (ft_freetab(res), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

