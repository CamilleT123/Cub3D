/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:02:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/30 18:55:38 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_direction(t_minimap *minimap, float x, float y)
{
	int	xbis;
	int	ybis;
	int	d;

	d = 0;
	while (d < 20)
	{
		xbis = x + cos(minimap->pa) * d;
		ybis = y + sin(minimap->pa) * d;
		my_mlx_pixel_put(minimap, xbis, ybis, 0x00FF0000);
		d++;
	}
	return (0);
}

int	draw_player(t_minimap *minimap, float x, float y)
{
	int	i;
	int	j;

	if (minimap->win == NULL)
		return (1);
	if (x < 0 || x > minimap->xmap || y < 0 || y > minimap->ymap)
		return (1);
	i = y - 5;
	while (i < y + 5)
	{
		j = x - 5;
		while (j < x + 5)
			my_mlx_pixel_put(minimap, j++, i, 0x00FF0000);
		++i;
	}
	draw_direction(minimap, x, y);
	return (0);
}

int	display(t_minimap *minimap)
{
	display_back2(minimap);
	display_back(minimap);
	draw_map(minimap);
	draw_player(minimap, minimap->px, minimap->py);
	draw_rays(minimap);
	mlx_put_image_to_window(minimap->mlx, minimap->win, minimap->img, 0, 0);
	return (0);
}
