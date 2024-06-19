/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:14:16 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/18 17:44:22 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_vertical_wall(t_line *line, t_bres *bres, t_cub *cub, t_rays *rays)
{
	int	y;
	int	pixel;

	pixel = 0;
	printf("texture = %p\n", cub->texture[0].img);
	line->ty = line->ty_off * line->ty_step;
	if (rays->disth < rays->distv)
	{
		line->tx = (int)(rays->rx * 4.0) % cub->txt_size;
		if (rays->ra < 180 * DR)
			line->tx = (cub->txt_size - 1) - line->tx;
	}
	else
	{
		line->tx = (int)(rays->ry * 4.0) % cub->txt_size;
		if (rays->ra > (90 * DR) && rays->ra < (270 * DR))
			line->tx = (cub->txt_size - 1) - line->tx;
	}
	y = line->y1;
	while (y != line->y2 + bres->incy)
	{
		pixel = (int)line->ty * cub->txt_size + (int)line->tx;
		line->color = *(unsigned int *)(cub->txt_add + pixel);
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
