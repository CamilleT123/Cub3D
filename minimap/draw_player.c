/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:02:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/07 16:15:52 by ctruchot         ###   ########.fr       */
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

	if (cub->win == NULL)
		return (1);
	if (x < 0 || x > cub->xmap || y < 0 || y > cub->ymap)
		return (1);
	i = y - 4; // reduire
	while (i < y + 4)
	{
		j = x - 4;
		while (j < x + 4)
			my_mlx_pixel_put(cub, j++, i, 0x00FF0000);
		++i;
	}
	draw_direction(cub, x, y);
	return (0);
}

int	init_line(t_cub *cub, t_rays *rays, t_line *line)
{
	line->x1 = cub->px;
	line->y1 = cub->py;
	line->x2 = rays->rx;
	line->y2 = rays->ry;
	return (0);
}

int draw_rays(t_cub *cub, t_rays *rays, t_line *line)
{
	rays->r = 0;
	rays->ra = cub->pa - (30 * DR);
	while (rays->r < 120)
	{
		init_each_ray(cub, rays);
		check_horizontal_lines(cub, rays);
		check_vertical_lines(cub, rays);
		compare_distances(rays);
		init_line(cub, rays, line);
		draw_line(cub, rays, line);
		rays->ra += 0.5 * DR;
		if (rays->ra < 0)
			rays->ra += 2 * PI;
		if (rays->ra > 2 * PI)
			rays->ra -= 2 * PI;
		rays->r++;
	}
	return (0);
}
// int	draw_square(t_cub *cub, float x, float y)
// {
// 	int	i;
// 	int	j;

// 	if (cub->win == NULL)
// 		return (1);
// 	if (x < 0 || x > cub->xmap || y < 0 || y > cub->ymap)
// 		return (1);
// 	i = y - 2;
// 	while (i < y + 2)
// 	{
// 		j = x - 2;
// 		while (j < x + 2)
// 			my_mlx_pixel_put(cub, j++, i, 0x666999);
// 		++i;
// 	}
// 	// draw_direction(cub, x, y);
// 	return (0);
// }