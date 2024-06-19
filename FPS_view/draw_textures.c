/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:14:16 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 16:16:22 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_vertical_wall(t_line *line, t_bres *bres, t_cub *cub, t_rays *rays)
{
	int	y;
	int	pixel;

	pixel = 0;
	// printf("texture = %p\n", cub->texture[0]->img);
	// printf("text size = %d\n", cub->texture[0]->width);
	line->ty = line->ty_off * line->ty_step;
	if (rays->disth < rays->distv)
	{
		line->tx = (int)(rays->rx * (cub->texture[rays->wall]->width / 16.0)) % cub->texture[rays->wall]->width;
		// line->tx = (int)(rays->rx * 16) % cub->texture[rays->wall]->width;

		// printf("line->tx = %f\n", line->tx);
		// printf("rays->rx = %f * 4 / cub->texture[rays->wall]->width = %d\n", rays->rx, cub->texture[rays->wall]->width);
		// printf("ra = %f\n", rays->ra);
		// (*2) pour 32
		// (* 4) car (/ 2 * 8) pour passer de 120 rays a 960 pour 64 et 128
		// (*8) pour 128
		// (*16) pour 	
		//	(*32) en 512
		if (rays->ra < 180 * DR)
			line->tx = (cub->texture[rays->wall]->width - 1) - line->tx;
		// printf("line->tx = %f\n\n", line->tx);
	}
	else
	{
		// printf("cub->texture[rays->wall]->width = %d\n", cub->texture[rays->wall]->width);
		// printf("line->tx = %f\n", line->tx);
		// printf("rays->rx = %f * 4 / cub->texture[rays->wall]->width = %d\n", rays->rx, cub->texture[rays->wall]->width);
		// printf("ra = %f\n", rays->ra);
		line->tx = (int)(rays->ry * (cub->texture[rays->wall]->width / 16.0)) % cub->texture[rays->wall]->width;
		// line->tx = (int)(rays->ry * 16.0) % cub->texture[rays->wall]->width;

		if (rays->ra > (90 * DR) && rays->ra < (270 * DR))
			line->tx = (cub->texture[rays->wall]->width - 1) - line->tx;
		// printf("line->tx = %f\n\n", line->tx);

	}
	y = line->y1;
	while (y != line->y2 + bres->incy)
	{
		pixel = (int)line->ty * cub->texture[rays->wall]->width + (int)line->tx;
		line->color = *(unsigned int *)(cub->texture[rays->wall]->addr + pixel);
		my_mlx_pixel_put(cub, line->x1, y, line->color);
		y += bres->incy;
		line->ty += line->ty_step;
	}
	return (0);
}

int	draw_line_walls(t_cub *cub, t_rays *rays, t_line *line)
{
	t_bres	bres;

	bres.dx = line->x2 - line->x1;
	bres.dy = line->y2 - line->y1;
	bres.incx = ft_sign(bres.dx);
	bres.incy = ft_sign(bres.dy);
	bres.dx = ft_abs(bres.dx);
	bres.dy = ft_abs(bres.dy);
	if (bres.dx == 0)
		draw_vertical_wall(line, &bres, cub, rays);
	else
		printf("\nERROR\n");
	return (0);
}
