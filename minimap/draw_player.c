/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:02:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 19:52:04 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_direction(t_cub *cub, float x, float y)
{
	int	xbis;
	int	ybis;
	int	d;

	d = 0;
	while (d < 15) // reduire
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
	draw_direction(cub, x, y);
	return (0);
}

int	init_line(t_cub *cub, t_rays *rays, t_line *line)
{
	line->x1 = cub->player_x;
	line->y1 = cub->player_y;
	line->x2 = rays->rx;
	line->y2 = rays->ry;
	return (0);
}

int	draw_rays(t_cub *cub, t_rays *rays, t_line *line)
{
	rays->r = 0;
	rays->ra = cub->pa - ((FIELDOFVIEW / 2) * DegtoRad);
	while (rays->r < rays->nb_rays)
	{
		init_each_ray(cub, rays);
		check_horizontal_lines(cub, rays);
		check_vertical_lines(cub, rays);
		compare_distances(rays);
		init_line(cub, rays, line);
		draw_line(cub, rays, line);
		rays->ra += ((FIELDOFVIEW / 2) / rays->nb_rays) * DegtoRad;
		if (rays->ra < 0)
			rays->ra += 2 * PI;
		if (rays->ra > 2 * PI)
			rays->ra -= 2 * PI;
		rays->r++;
	}
	return (0);
}
