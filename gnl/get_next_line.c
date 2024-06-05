/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:15:13 by aduvilla          #+#    #+#             */
/*   Updated: 2023/11/22 11:27:44 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	isend(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_to_result(char *result, const int fd)
{
	char	*buff;
	char	*copy;
	int		i;

	i = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (free(result), free(buff), buff = NULL, NULL);
		else if (i == 0)
			break ;
		buff[i] = '\0';
		if (!result)
			result = gnl_strnew();
		copy = result;
		result = gnl_strjoin(copy, buff);
		free(copy);
		if (isend(result))
			break ;
	}
	return (free(buff), buff = NULL, result);
}

char	*stash_memory(char *result)
{
	char	*memory;
	size_t	i;
	size_t	size;

	i = 0;
	while (result[i] != '\n' && result[i] != '\0')
		i++;
	if (result[i] == '\0' || result[i + 1] == '\0')
		return (NULL);
	size = gnl_strlen(result) - i;
	memory = gnl_substr(result, i + 1, size);
	if (!memory)
		return (free(memory), memory = NULL, NULL);
	result[i + 1] = '\0';
	return (memory);
}

char	*get_next_line(const int fd)
{
	static char	*memory;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(memory);
		memory = NULL;
		return (NULL);
	}
	if (memory && isend(memory))
		result = memory;
	else
		result = read_to_result(memory, fd);
	if (!result)
		return (NULL);
	memory = stash_memory(result);
	return (result);
}
