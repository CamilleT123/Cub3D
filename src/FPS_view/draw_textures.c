/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:14:16 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 17:45:01 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vert_wall(t_line *line, t_bres *bres, t_cub *cub, t_rays *rays)
{
	int	y;
	int	pixel;

	pixel = 0;
	y = line->y1;
	while (y != line->y2 + bres->incy)
	{
		pixel = (int)line->ty * cub->texture[rays->wall]->width + (int)line->tx;
		line->color = *(unsigned int *)(cub->texture[rays->wall]->addr + pixel);
		my_mlx_pixel_put(cub, line->x1, y, line->color);
		y += bres->incy;
		line->ty += line->ty_step;
	}
}

static void	vertical_wall(t_line *line, t_bres *bres, t_cub *cub, t_rays *rays)
{
	line->ty = line->ty_off * line->ty_step;
	if (rays->disth < rays->distv)
	{
		line->tx = (int)(rays->rx * (cub->texture[rays->wall]->width / 16.0))
			% cub->texture[rays->wall]->width;
		if (rays->ra < 180 * DEGTORAD)
			line->tx = (cub->texture[rays->wall]->width - 1) - line->tx;
	}
	else
	{
		line->tx = (int)(rays->ry * (cub->texture[rays->wall]->width / 16.0))
			% cub->texture[rays->wall]->width;
		if (rays->ra > (90 * DEGTORAD) && rays->ra < (270 * DEGTORAD))
			line->tx = (cub->texture[rays->wall]->width - 1) - line->tx;
	}
	draw_vert_wall(line, bres, cub, rays);
}

int	bresenham_walls(t_cub *cub, t_rays *rays, t_line *line)
{
	t_bres	bres;

	bres.dx = line->x2 - line->x1;
	bres.dy = line->y2 - line->y1;
	bres.incx = ft_sign(bres.dx);
	bres.incy = ft_sign(bres.dy);
	bres.dx = ft_abs(bres.dx);
	bres.dy = ft_abs(bres.dy);
	if (bres.dx == 0)
		vertical_wall(line, &bres, cub, rays);
	// else if (bres.dx == 0)
	// 	draw_vertical(line, &bres, cub, rays);
	// else if (bres.dx >= bres.dy)
	// 	draw_more_horizontal(cub, rays, &bres, line);
	// else
	// 	draw_more_vertical(cub, rays, &bres, line);
	return (0);
}
