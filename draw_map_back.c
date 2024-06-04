/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/30 18:55:26 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display_back(t_minimap *minimap)
{
	int	i;
	int	j;

	if (minimap->win == NULL)
		return (1);
	i = 0;
	while (i < minimap->ymap)
	{
		j = 0;
		while (j < minimap->xmap)
			my_mlx_pixel_put(minimap, j++, i, 0x666999);
		++i;
	}
	return (0);
}

int	display_back2(t_minimap *minimap)
{
	int	i;
	int	j;

	if (minimap->win == NULL)
		return (1);
	i = 0;
	while (i < minimap->ymap / 2)
	{
		j = 523;
		while (j < minimap->xmap * 2 && j < 1011)
			my_mlx_pixel_put(minimap, j++, i, 0xb3b2dc);
		++i;
	}
	while (i < minimap->ymap)
	{
		j = 523;
		while (j < minimap->xmap * 2 && j < 1011)
			my_mlx_pixel_put(minimap, j++, i, 0x515072);
		++i;
	}
	return (0);
}

int	draw_map_1(t_minimap *minimap, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * minimap->mapsize;
	while (yo < y * minimap->mapsize + minimap->mapsize - 1)
	{
		xo = x * minimap->mapsize;
		while (xo < x * minimap->mapsize + minimap->mapsize - 1)
			my_mlx_pixel_put(minimap, xo++, yo, 0x7f388b);
		++yo;
	}
	return (0);
}

int	draw_map_0(t_minimap *minimap, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * minimap->mapsize;
	while (yo < y * minimap->mapsize + minimap->mapsize - 1)
	{
		xo = x * minimap->mapsize;
		while (xo < x * minimap->mapsize + minimap->mapsize - 1)
			my_mlx_pixel_put(minimap, xo++, yo, 0xbdabc4);
		++yo;
	}
	return (0);
}

int	draw_map(t_minimap *minimap)
{
	int	y;
	int	x;

	y = 0;
	while (y < minimap->mapy)
	{
		x = 0;
		while (x < minimap->mapx)
		{
			if (minimap->map[y * minimap->mapx + x] == 1)
				draw_map_1(minimap, x, y);
			if (minimap->map[y * minimap->mapx + x] == 0)
				draw_map_0(minimap, x, y);
			++x;
		}
		++y;
	}
	return (0);
}