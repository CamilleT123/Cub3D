/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:07:27 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/24 20:28:28 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	getint(char c)
{
	if (is_startchar(c) || c == '0')
		return (0);
	else if (c == '1')
		return (1);
	else if (c == '3')
		return (3);
	else
		return (2);
}

static int	get_map_int(t_cub *cub)
{
	int	i;
	int	j;
	int	k;

	cub->map = malloc(sizeof(int) * cub->mapsize);
	if (!cub->map)
		return (map_error("", MALLOC, 1));
	i = 0;
	j = -1;
	while (cub->scene.map[++j])
	{
		k = 0;
		while (cub->scene.map[j][k])
		{
			cub->map[i++] = getint(cub->scene.map[j][k]);
			k++;
		}
		while (k < cub->mapx)
		{
			cub->map[i++] = 2;
			k++;
		}
	}
	return (0);
}

int	init_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->scene.map && cub->scene.map[i])
	{
		j = 0;
		while (cub->scene.map[i][j])
			j++;
		if (j > cub->mapx)
			cub->mapx = j;
		i++;
	}
	cub->mapy = i;
	cub->mapsize = cub->mapx * cub->mapy;
	cub->f_color = cub->scene.f_color;
	cub->c_color = cub->scene.c_color;

	if (get_map_int(cub))
		return (exit_map(cub, 1), 1);
	return (0);
}

static int	get_texture(t_cub *cub, int i, char *path)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (map_error("", MALLOC, 1));
	ft_bzero(tex, sizeof(t_texture));
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (map_error("", "cannot create image", 1));
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
		return (map_error("", "cannot get image address", 1));
	cub->texture[i] = tex;
	return (0);
}

int	init_textures(t_cub *cub)
{
	int		i;
	char	*arrtex[5];

	cub->texture = malloc(sizeof(t_texture *) * 5);
	if (!cub->texture)
		return (map_error("", MALLOC, 1));
	arrtex[0] = cub->scene.north;
	arrtex[1] = cub->scene.south;
	arrtex[2] = cub->scene.east;
	arrtex[3] = cub->scene.west;
	arrtex[4] = DOORPATH;
	i = 0;
	while (i < 5)
	{
		if (get_texture(cub, i, arrtex[i]))
			return (exit_map(cub, 1));
//		free(arrtex[i]);
		i++;
	}
//	cub->scene.north = NULL;
//	cub->scene.south = NULL;
//	cub->scene.east = NULL;
//	cub->scene.west = NULL;
	return (0);
}
