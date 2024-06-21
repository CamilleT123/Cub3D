/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:02:48 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/21 12:08:03 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_direction(t_cub *cub, float x, float y)
{
	int	xbis;
	int	ybis;
	int	d;

	d = 0;
	while (d < 10) // reduire
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
	line->x1 = (cub->player_x / ((float)cub->unitpc / (float)cub->ppc));
	line->y1 = (cub->player_y /  ((float)cub->unitpc / (float)cub->ppc));
	// if (rays->r == 59)
	// 	printf("rx=%f, ry=%f\n", rays->rx, rays->ry);
	line->x2 = rays->rx;
	line->y2 = rays->ry;
	// if (rays->r == 30)
	// {
	// 	printf("x1=%d, y1=%d, x2=%d, y2=%d\n", line->x1, line->y1, line->x2, line->y2);
	// 	printf("player_xmini=%f, player_ymini=%f\n", cub->player_xmini, cub->player_ymini);
	// }
	return (0);
}

int	init_line_mini(t_cub *cub, t_rays *rays, t_line *line)
{
	line->x1 = cub->player_xmini;
	line->y1 = cub->player_ymini;
	// if (rays->r == 59)
	// 	printf("rx=%f, ry=%f\n", rays->rx, rays->ry);
	line->x2 = rays->rx;
	line->y2 = rays->ry;
	if (rays->r == 30)
	{
		printf("x1=%d, y1=%d, x2=%d, y2=%d\n", line->x1, line->y1, line->x2, line->y2);
		// printf("player_xmini=%f, player_ymini=%f\n", cub->player_xmini, cub->player_ymini);
	}
	return (0);
}

int	draw_rays(t_cub *cub, t_rays *rays, t_line *line)
{
	rays->r = 0;
	// rays->ra = cub->pa;
	rays->ra = cub->pa - ((FIELDOFVIEW / 2) * DEGTORAD);
	if (rays->ra < 0)
		rays->ra += 2 * PI;
	if (rays->ra > 2 * PI)
		rays->ra -= 2 * PI;
	// rays_init(cub, rays);
	while (rays->r < rays->nb_rays)
	{
		// printf("rayon %d\n", rays->r);
		init_each_ray_mini(cub, rays);
		check_horizontal_lines_mini(cub, rays);
		check_vertical_lines_mini(cub, rays);
		compare_distances_mini(rays);
			// init_line(cub, rays, line);
		printf("ra=%f\n", rays->ra / DEGTORAD);
		printf("rx=%f\n", rays->rx);
		printf("ry=%f\n", rays->ry);
		init_line_mini(cub, rays, line);
		draw_line(cub, rays, line);
		rays->ra += (FIELDOFVIEW / rays->nb_rays) * DEGTORAD;
		// printf("(FIELDOFVIEW / rays->nb_rays)=%d\n", (FIELDOFVIEW / rays->nb_rays));
		if (rays->ra < 0)
			rays->ra += 2 * PI;
		if (rays->ra > 2 * PI)
			rays->ra -= 2 * PI;
		rays->r++;
	}
	return (0);
}
