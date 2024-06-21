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

int	draw_minimap_1(t_cub *cub, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * 16;
	while (yo < y * 16 + 16 -1)
	{
		xo = x * 16;
		while (xo < x * 16 + 16 -1)
			my_mlx_pixel_put(cub, xo++, yo, 0x7f388b);
		++yo;
	}
	return (0);
}

int	draw_minimap_0(t_cub *cub, int x, int y)
{
	int	yo;
	int	xo;

	yo = y * 16;
	while (yo < y * 16 + 16 -1)
	{
		xo = x * 16;
		while (xo < x * 16 + 16 -1)
			my_mlx_pixel_put(cub, xo++, yo, 0xbdabc4);
		++yo;
	}
	return (0);
}

int	draw_miniplayer(t_cub *cub, float x, float y)
{
	// int	yo;
	// int	xo;

	// yo = y * 16;
	// while (yo < y * 16 + 16 -1)
	// {
	// 	xo = x * 16;
	// 	while (xo < x * 16 + 16 -1)
	// 		my_mlx_pixel_put(cub, xo++, yo, 0xbdabc4);
	// 	++yo;
	// }
	// return (0);
	
	int	i;
	int	j;

	if (x < 0 || x > cub->minimapx || y < 0 || y > cub->minimapy)
		return (1);
	i = y - PLAYERSIZE;
	while (i < y + PLAYERSIZE)
	{
		j = x - PLAYERSIZE;
		while (j < x + PLAYERSIZE)
			my_mlx_pixel_put(cub, j++, i, 0x00FF0000);
		++i;
	}
	// draw_direction(cub, x, y);
	return (0);
}


int	draw_cropped_map(t_cub *cub)
{
	int	y;
	int	x;
	y = 0;
	while (y < 128)
	{
		x = 0;
		while (x < 128)
		{
			my_mlx_pixel_put(cub, x, y, 0);
			++x;
		}
		++y;
	}

	int case_x_player;
	int case_y_player;
	
	case_x_player = cub->player_x / UNITPC;
	case_y_player = cub->player_y / UNITPC;
	// printf("case_x_player = %d\n", case_x_player);
	// printf("case_y_player = %d\n", case_y_player);
	int case_x_min = case_x_player - 4;
	int case_x_max = case_x_player + 4;
	int case_y_min = case_y_player - 4;
	int case_y_max = case_y_player + 4;
	// printf("case_x_min = %d\n", case_x_min);
	// printf("case_x_max = %d\n", case_x_max);
	// printf("case_y_min = %d\n", case_y_min);
	// printf("case_y_max = %d\n", case_y_max);
	int case_x;
	int case_y;
	// printf("ppc=%d\n", cub->ppc);
	// case_player = (cub->player_y / UNITPC) * cub->mapx + (cub->player_x / UNITPC);
	int case_player = case_y_player * cub->mapx + (case_x_player);
	printf("case_player = %d\n", case_player);
	case_y = case_y_min;
	y = 0;
	while (case_y < case_y_max)
	{
		case_x = case_x_min;
		x = 0;
		while (case_x < case_x_max)
		{
			if (case_x >= 0)
			{
				// printf("case_y = %d\n", case_y);
				// printf("case_x = %d\n", case_x);
				// printf("case_y * cub->mapx + case_x = %d\n", case_y * cub->mapx + case_x);
				if (cub->map[case_y * cub->mapx + case_x] == 1)
					draw_minimap_1(cub, x, y);
				if (cub->map[case_y * cub->mapx + case_x] == 0)
				{
					// printf("x = %d\n", x);
					// printf("y = %d\n", y);
					draw_minimap_0(cub, x, y);
				}
				if (case_y * cub->mapx + case_x == case_player)
				{
					// printf("PLAYER\nx = %d\n", x);
					// printf("y = %d\n", y);
					draw_miniplayer(cub, (float)((x * 16) + 8), (float)((y * 16) + 8));
				}
				// if (((case_y * cub->mapx + case_x) >= 0) && (cub->map[case_y * cub->mapx + case_x] == 0 || cub->map[case_y * cub->mapx + case_x] == 2))
				// 	draw_map_0(cub, x, y);
			}
			++case_x;
			++x;
		}
		++case_y;
		++y;
	}
	// cub->player_xmini = (cub->player_x / ((float)UNITPC / (float)cub->ppc));
	// cub->player_ymini = (cub->player_y /  ((float)UNITPC / (float)cub->ppc));
	// int player_x_map = 
	// draw_player(cub, cub->player_xmini, cub->player_ymini);
	return (0);
}

int	draw_minimap(t_cub *cub)
{
	cub->ppc = SMINIMAPX / cub->mapx;
	if (cub->ppc < PPCMIN)
	{
		cub->ppc = SMINIMAPX / cub->mapy; // voir si case pas carree
		if (cub->ppc < PPCMIN)
			cub->ppc = cub->ppc;
	}
	cub->minimapx = cub->ppc * cub->mapx;
	cub->minimapy = cub->ppc * cub->mapy;
	// printf("ppc = %d\n", cub->ppc);
	// printf("minimapx = %d\n", cub->minimapx);
	// printf("minimapy = %d\n", cub->minimapy);
	if (cub->mapsize > 3600 || cub->mapx > 80 || cub->mapy > 80)
		draw_cropped_map(cub);
	else
		draw_full_map(cub);
	return (0);
}
