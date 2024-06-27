/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:02:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 18:39:12 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_direction(t_cub *cub, float x, float y)
{
	int	xbis;
	int	ybis;
	int	d;

	d = 0;
	while (d < DIRECTIONSIZE)
	{
		xbis = x + cos(cub->player_angle) * d;
		ybis = y + sin(cub->player_angle) * d;
		my_mlx_pixel_put(cub, xbis, ybis, PLAYERCOLOR);
		d++;
	}
	return (0);
}

int	draw_player(t_cub *cub, float x, float y)
{
	int	i;
	int	j;

	if (x < 0 || x > cub->minimapx || y < 0 || y > cub->minimapy)
		return (1);
	i = y - PLAYERSIZE;
	while (i < y + PLAYERSIZE)
	{
		j = x - PLAYERSIZE;
		while (j < x + PLAYERSIZE)
			my_mlx_pixel_put(cub, j++, i, PLAYERCOLOR);
		++i;
	}
	draw_direction(cub, x, y);
	return (0);
}

// int	draw_player_mini(t_cub *cub, float x, float y)
// {
// 	int	i;
// 	int	j;

// 	if (x < 0 || x > cub->minimapx || y < 0 || y > cub->minimapy)
// 		return (1);
// 	i = y - PLAYERSIZE;
// 	while (i < y + PLAYERSIZE)
// 	{
// 		j = x - PLAYERSIZE;
// 		while (j < x + PLAYERSIZE)
// 			my_mlx_pixel_put(cub, j++, i, 0x00FF0000);
// 		++i;
// 	}
// 	draw_direction(cub, x, y);
// 	return (0);
// }
