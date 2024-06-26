/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:45:06 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/18 19:47:42 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	check_extension(char *file, char *ext)
{
	int	f;
	int	e;

	if (!file || !ext)
		return (1);
	f = ft_strlen(file) - 1;
	e = ft_strlen(ext) - 1;
	while (f >= e && e >= 0)
	{
		if (file[f] != ext[e])
			return (map_ext_error(file, ext, 1));
		e--;
		f--;
	}
	return (0);
}

char	*get_path(char *str, int skip)
{
	char	*spl;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str && str[++i])
		if (!cub_isspace(str[i]))
			len++;
	if (len < skip)
		return (NULL);
	spl = malloc(sizeof(char) * len + 1 - skip);
	if (!spl)
		return (map_error("", MALLOC, 1), NULL);
	i = -1;
	len = 0;
	while (str && str[++i])
	{
		if (!cub_isspace(str[i]) && skip <= 0)
			spl[len++] = str[i];
		else if (!cub_isspace(str[i]) && skip > 0)
			skip--;
	}
	spl[len] = '\0';
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
