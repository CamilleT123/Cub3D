/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:08:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/30 18:48:13 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_more_horizontal(t_minimap *minimap, t_rays *rays, t_bres *bres,
		t_line *line)
{
	int	slope;
	int	error;
	int	errorinc;
	int	y;
	int	x;

	slope = 2 * bres->dy;
	error = -bres->dx;
	errorinc = -2 * bres->dx;
	y = line->y1;
	x = line->x1;
	while (x != line->x2 + bres->incx)
	{
		my_mlx_pixel_put(minimap, x, y, rays->color);
		error += slope;
		if (error >= 0)
		{
			y += bres->incy;
			error += errorinc;
		}
		x += bres->incx;
	}
	return (0);
}

int	draw_more_vertical(t_minimap *minimap, t_rays *rays, t_bres *bres,
		t_line *line)
{
	int	slope;
	int	error;
	int	errorinc;
	int	y;
	int	x;

	slope = 2 * bres->dx;
	error = -bres->dy;
	errorinc = -2 * bres->dy;
	x = line->x1;
	y = line->y1;
	while (y != line->y2 + bres->incy)
	{
		my_mlx_pixel_put(minimap, x, y, rays->color);
		error += slope;
		if (error >= 0)
		{
			x += bres->incx;
			error += errorinc;
		}
		y += bres->incy;
	}
	return (0);
}

int	draw_horizontal(t_line *line, t_bres *bres, t_minimap *minimap,
		t_rays *rays)
{
	int	x;

	x = line->x1;
	while (x != line->x2 + bres->incx)
	{
		my_mlx_pixel_put(minimap, x, line->y1, rays->color);
		x += bres->incx;
	}
	return (0);
}

int	draw_vertical(t_line *line, t_bres *bres, t_minimap *minimap, t_rays *rays)
{
	int	y;

	{
		y = line->y1;
		while (y != line->y2 + bres->incy)
		{
			my_mlx_pixel_put(minimap, line->x1, y, rays->color);
			y += bres->incy;
		}
	}
	return (0);
}

int	draw_line(t_minimap *minimap, t_rays *rays, t_line *line)
{
	t_bres	bres;

	bres.dx = line->x2 - line->x1;
	bres.dy = line->y2 - line->y1;
	bres.incx = ft_sign(bres.dx);
	bres.incy = ft_sign(bres.dy);
	bres.dx = ft_abs(bres.dx);
	bres.dy = ft_abs(bres.dy);
	if (bres.dy == 0)
		draw_horizontal(line, &bres, minimap, rays);
	else if (bres.dx == 0)
		draw_vertical(line, &bres, minimap, rays);
	else if (bres.dx >= bres.dy)
		draw_more_horizontal(minimap, rays, &bres, line);
	else
		draw_more_vertical(minimap, rays, &bres, line);
	return (0);
}
