/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 14:34:00 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_map_3(t_cub *cub, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * cub->ppc;
	while (yo < y * cub->ppc + cub->ppc)
	{
		xo = x * cub->ppc;
		while (xo < x * cub->ppc + cub->ppc)
			my_mlx_pixel_put(cub, xo++, yo, MAPDOOR);
		++yo;
	}
	return (0);
}

static int	draw_map_1(t_cub *cub, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * cub->ppc;
	while (yo < y * cub->ppc + cub->ppc)
	{
		xo = x * cub->ppc;
		while (xo < x * cub->ppc + cub->ppc)
			my_mlx_pixel_put(cub, xo++, yo, MAPWALL);
		++yo;
	}
	return (0);
}

static int	draw_map_0(t_cub *cub, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * cub->ppc;
	while (yo < y * cub->ppc + cub->ppc)
	{
		xo = x * cub->ppc;
		while (xo < x * cub->ppc + cub->ppc)
			my_mlx_pixel_put(cub, xo++, yo, MAPFLOOR);
		++yo;
	}
	return (0);
}

int	draw_full_map(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->mapy)
	{
		x = 0;
		while (x < cub->mapx)
		{
			if (cub->map[y * cub->mapx + x] == 1)
				draw_map_1(cub, x, y);
			if (cub->map[y * cub->mapx + x] == 0
				|| cub->map[y * cub->mapx + x] == 4)
				draw_map_0(cub, x, y);
			if (cub->map[y * cub->mapx + x] == 3)
				draw_map_3(cub, x, y);
			++x;
		}
		++y;
	}
	cub->player_xmini = (cub->player_x / ((float)UNITPC / (float)cub->ppc));
	cub->player_ymini = (cub->player_y / ((float)UNITPC / (float)cub->ppc));
	draw_player(cub, cub->player_xmini, cub->player_ymini);
	return (0);
}

// int	draw_map_2(t_cub *cub, int x, int y)
// {
// 	int	yo;
// 	int	xo;

// 	yo = y * cub->ppc;
// 	while (yo < y * cub->ppc + cub->ppc)
// 	{
// 		xo = x * cub->ppc;
// 		while (xo < x * cub->ppc + cub->ppc)
// 			my_mlx_pixel_put(cub, xo++, yo, 0);
// 		++yo;
// 	}
// 	return (0);
// }

// int	display_back(t_cub *cub)
// {
// 	int	i;
// 	int	j;

// 	if (cub->win == NULL)
// 		return (1);
// 	i = 0;
// 	while (i < SMINIMAPY)
// 	{
// 		j = 0;
// 		while (j < SMINIMAPX)
// 			my_mlx_pixel_put(cub, j++, i, 0x666999);
// 		++i;
// 	}
// 	return (0);
// }

// soustraire -1 aux 2 while pour quadriller la map