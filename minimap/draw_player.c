/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:02:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/06 12:18:29 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_direction(t_cub *cub, float x, float y)
{
	int	xbis;
	int	ybis;
	int	d;

	d = 0;
	while (d < 20)
	{
		xbis = x + cos(cub->pa) * d;
		ybis = y + sin(cub->pa) * d;
		my_mlx_pixel_put(cub, xbis, ybis, 0x00FF0000);
		d++;
	}
	return (0);
}

int	draw_player(t_cub *cub, float x, float y)
{
	int	i;
	int	j;

	if (cub->win == NULL)
		return (1);
	if (x < 0 || x > cub->xmap || y < 0 || y > cub->ymap)
		return (1);
	i = y - 5;
	while (i < y + 5)
	{
		j = x - 5;
		while (j < x + 5)
			my_mlx_pixel_put(cub, j++, i, 0x00FF0000);
		++i;
	}
	draw_direction(cub, x, y);
	return (0);
}

int	draw_square(t_cub *cub, float x, float y)
{
	int	i;
	int	j;

	if (cub->win == NULL)
		return (1);
	if (x < 0 || x > cub->xmap || y < 0 || y > cub->ymap)
		return (1);
	i = y - 2;
	while (i < y + 2)
	{
		j = x - 2;
		while (j < x + 2)
			my_mlx_pixel_put(cub, j++, i, 0x666999);
		++i;
	}
	// draw_direction(cub, x, y);
	return (0);
}