/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:33:28 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 18:07:16 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fix_fish_eye(t_cub *cub, t_rays *rays)
{
	float	ca;

	ca = cub->player_angle - rays->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	rays->distt = rays->distt * cos(ca);
}

static void	draw_vertical_line(t_line *line, t_cub *cub, t_rays *rays)
{
	int	y;
	int	pixel;

	pixel = 0;
	y = line->y1;
	while (y != line->y2)
	{
		pixel = (int)line->ty * cub->texture[rays->wall]->width + (int)line->tx;
		line->color = *(unsigned int *)(cub->texture[rays->wall]->addr + pixel);
		my_mlx_pixel_put(cub, line->x1, y, line->color);
		y++;
		line->ty += line->ty_step;
	}
}

static void	get_texture_index(t_line *line, t_cub *cub, t_rays *rays)
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
	draw_vertical_line(line, cub, rays);
}

// ca is use ti fix fish eye effect
// line_height is the line height and lineo is the line offset

int	draw_walls(t_cub *cub, t_rays *rays)
{
	t_line	wall;
	float	line_off;

	fix_fish_eye(cub, rays);
	wall.line_height = (16 * (WINH)) / rays->distt;
	wall.ty_step = cub->texture[rays->wall]->width / (float)wall.line_height;
	wall.ty_off = 0;
	if (wall.line_height > WINH)
	{
		wall.ty_off = (wall.line_height - WINH) / 2.0;
		wall.line_height = WINH;
	}
	line_off = (WINH / 2.0) - (wall.line_height / 2.0);
	wall.x1 = rays->r;
	wall.y1 = line_off;
	wall.x2 = rays->r;
	wall.y2 = wall.line_height + line_off;
	get_texture_index(&wall, cub, rays);
	return (0);
}
