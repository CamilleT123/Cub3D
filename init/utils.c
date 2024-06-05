/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:45:06 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/05 15:32:27 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(char *str, int skip)
{
	char	*spl;
	int		i;
	int		len;
	
	i = -1;
	len = -skip;
	spl = NULL;
	while (str && str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			len++;
	if (len >= 0)
	{
		spl = malloc(sizeof(char) * len + 1);
		if (!spl)
			return (map_error("", MALLOC, 1), NULL);
		i = -1;
		len = 0;
		while (str && str[++i])
			if (str[i] != ' ' && str[i] != '\t')
				spl[len++] = str[i]; // tentative de ++ le len apres !!!!
		spl[len] = '\0';
	}
	return (spl);
}

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

