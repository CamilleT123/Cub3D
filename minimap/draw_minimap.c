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

	yo = y * MINIMAPPPC;
	while (yo < y * MINIMAPPPC + MINIMAPPPC -1)
	{
		xo = x * MINIMAPPPC;
		while (xo < x * MINIMAPPPC + MINIMAPPPC -1)
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

void	draw_background(t_cub *cub)
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
}

void	draw_cropped_map(t_cub *cub, t_minimap *mini)
{
	int y;
	int x;

	y = 0;
	while (mini->case_y < mini->y_max)
	{
		mini->case_x = mini->x_min;
		x = 0;
		while (mini->case_x < mini->x_max)
		{
			if (mini->case_x >= 0 && mini->case_y >= 0)
			{
				if (cub->map[mini->case_y * cub->mapx + mini->case_x] == 1)
					draw_minimap_1(cub, x, y);
				if (cub->map[mini->case_y * cub->mapx + mini->case_x] == 0)
					draw_minimap_0(cub, x, y);
			}
			++mini->case_x;
			++x;
		}
		++mini->case_y;
		++y;
	}
}

int	crop_map(t_cub *cub)
{
	int xmin;
	int ymin;
	int xmax;
	int ymax;
	int y;
	int x;

	cub->player_xmini = (SMINIMAPX / 2);
	cub->player_ymini = (SMINIMAPY / 2);
	xmin = (cub->player_x / 2) - cub->player_xmini;
	ymin = (cub->player_y / 2) - cub->player_ymini;
	xmax = (cub->player_x / 2) + cub->player_xmini;
	ymax = (cub->player_y / 2) + cub->player_ymini;
	// printf("xmin = %d\n", xmin);
	// printf("ymin = %d\n", ymin);
	// printf("xmax = %d\n", xmax);
	// printf("ymax = %d\n", ymax);
	// printf("player_x = %f\n", cub->player_x);
	// printf("player_y = %f\n", cub->player_y);
	y = 0;
	while (y < SMINIMAPY && ymin < ymax)
	{
		x = 0;
		xmin = cub->player_x - cub->player_xmini;
		while (x < SMINIMAPX && xmin < xmax)
		{
			if (xmin >= 0 && ymin >= 0)
			{
				if (cub->map[(ymin / 8) * cub->mapx + (xmin / 8)] == 1)
					my_mlx_pixel_put(cub, x, y, 0x7f388b);
				if (cub->map[(ymin / 8) * cub->mapx + (xmin / 8)] == 0)
					my_mlx_pixel_put(cub, x, y, 0xbdabc4);
			}
			++xmin;
			++x;
		}
		++ymin;
		++y;
	}
	// printf("player_xmini = %f\n", cub->player_xmini);
	// printf("player_ymini = %f\n", cub->player_ymini);
	draw_player(cub, (SMINIMAPX / 2), (SMINIMAPY / 2));
	return (0);
}

// int	crop_map(t_cub *cub)
// {
// 	// t_minimap	mini;

// 	// draw_background(cub);
// 	// mini.case_x_player = cub->player_x / UNITPC;
// 	// mini.case_y_player = cub->player_y / UNITPC;
// 	// mini.index_player = mini.case_y_player * cub->mapx + mini.case_x_player;
// 	// mini.x_min = mini.case_x_player - 4;
// 	// mini.x_max = mini.case_x_player + 4;
// 	// mini.y_min = mini.case_y_player - 4;
// 	// mini.y_max = mini.case_y_player + 4;
// 	// mini.case_y = mini.y_min;
// 	// draw_cropped_map(cub, &mini);

// 	// cub->player_xmini = (cub->player_x / ((float)UNITPC / (float)cub->ppc)) - (mini.x_min * cub->ppc);
// 	// cub->player_ymini = (cub->player_y / ((float)UNITPC / (float)cub->ppc)) - (mini.y_min * cub->ppc);
// 	cub->player_xmini = (SMINIMAPX / 2);
// 	cub->player_ymini = (SMINIMAPY / 2);

// 	int xmin = (cub->player_x / 2) - cub->player_xmini;
// 	int ymin = (cub->player_y / 2) - cub->player_ymini;
// 	int xmax = (cub->player_x / 2) + cub->player_xmini;
// 	int ymax = (cub->player_y / 2) + cub->player_ymini;
// 	printf("xmin = %d\n", xmin);
// 	printf("ymin = %d\n", ymin);
// 	printf("xmax = %d\n", xmax);
// 	printf("ymax = %d\n", ymax);
// 	printf("player_xmini = %f\n", cub->player_xmini);
// 	printf("player_ymini = %f\n", cub->player_ymini);
// 	printf("player_x = %f\n", cub->player_x);
// 	printf("player_y = %f\n", cub->player_y);
// 	int y;
// 	int x;

// 	y = 0;
// 	while (y < SMINIMAPY && ymin < ymax)
// 	{
// 		x = 0;
// 		xmin = cub->player_x - cub->player_xmini;
// 		while (x < SMINIMAPX && xmin < xmax)
// 		{
// 			if (xmin >= 0 && ymin >= 0)
// 			{
// 				if (cub->map[(ymin / 8) * cub->mapx + (xmin / 8)] == 1)
// 					my_mlx_pixel_put(cub, x, y, 0x7f388b);
// 				if (cub->map[(ymin / 8) * cub->mapx + (xmin / 8)] == 0)
// 					my_mlx_pixel_put(cub, x, y, 0xbdabc4);
// 			}
// 			++xmin;
// 			++x;
// 		}
// 		++ymin;
// 		++y;
// 	}
// 	// printf("player_xmini = %f\n", cub->player_xmini);
// 	// printf("player_ymini = %f\n", cub->player_ymini);
// 	draw_player(cub, (SMINIMAPX / 2), (SMINIMAPY / 2));
// 	return (0);
// }

	//
	// printf("case_x_player = %d\n", case_x_player);
	// printf("case_y_player = %d\n", case_y_player);
	// printf("case_x_min = %d\n", case_x_min);
	// printf("case_x_max = %d\n", case_x_max);
	// printf("case_y_min = %d\n", case_y_min);
	// printf("case_y_max = %d\n", case_y_max);
	// printf("ppc=%d\n", cub->ppc);
	// case_player = (cub->player_y / UNITPC) * cub->mapx + (cub->player_x / UNITPC);
	// int case_player = case_y_player * cub->mapx + (case_x_player);
	// printf("case_player = %d\n", case_player);
				// if (case_y * cub->mapx + case_x == case_player)
				// {
				// 	// printf("PLAYER\nx = %d\n", x);
				// 	// printf("y = %d\n", y);
				// 	draw_miniplayer(cub, (float)((x * 16) + 8), (float)((y * 16) + 8));
				// }
				// if (((case_y * cub->mapx + case_x) >= 0) && (cub->map[case_y * cub->mapx + case_x] == 0 || cub->map[case_y * cub->mapx + case_x] == 2))
				// 	draw_map_0(cub, x, y);
	// cub->player_xmini = (cub->player_x / ((float)UNITPC / (float)cub->ppc));
	// cub->player_ymini = (cub->player_y /  ((float)UNITPC / (float)cub->ppc));
	// int player_x_map = 

int	draw_minimap(t_cub *cub)
{
	cub->ppc = PPCMIN;
	while (cub->ppc < PPCMAX && ((cub->mapx * cub->ppc) < MINIMAPMIN
			|| (cub->mapy * cub->ppc) < MINIMAPMIN)
		&& ((cub->mapx * cub->ppc) < MINIMAPMAX
			&& (cub->mapy * cub->ppc) < MINIMAPMAX))
		cub->ppc++;
	if (cub->mapx * cub->ppc > 480 || cub->mapy * cub->ppc > 480
		|| cub->mapsize * cub->ppc > 65536)
	{
		cub->ppc = MINIMAPPPC;
		cub->minimapx = cub->ppc * 8;
		cub->minimapy = cub->ppc * 8;
		crop_map(cub);
	}
	else
	{
	cub->minimapx = cub->ppc * cub->mapx;
	cub->minimapy = cub->ppc * cub->mapy;	
	draw_full_map(cub);
	}
	return (0);
}

	// printf("ppc = %d\n", cub->ppc);
	// // // printf("minimapx = %d\n", cub->minimapx);
	// // // printf("minimapy = %d\n", cub->minimapy);