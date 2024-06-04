/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:33:28 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/30 18:58:40 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_line(t_minimap *minimap, t_rays *rays, t_line *line)
{
	line->x1 = minimap->px;
	line->y1 = minimap->py;
	line->x2 = rays->rx;
	line->y2 = rays->ry;
	return (0);
}

int	fix_fish_eye(t_minimap *minimap, t_rays *rays)
{
	float	ca;

	ca = minimap->pa - rays->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	rays->distt = rays->distt * cos(ca);
	return (0);
}

// ca is use ti fix fish eye effect
// lineh is the line height and lineo is the line offset

int	draw_walls(t_minimap *minimap, t_rays *rays, int r)
{
	t_line	wall;
	float	lineh;
	int		i;
	float	lineo;

	fix_fish_eye(minimap, rays);
	lineh = (minimap->mapsize * 320) / rays->distt;
	if (lineh > 512)
		lineh = 512;
	lineo = 256 - (lineh / 2);
	i = 0;
	while (i < 16)
	{
		wall.x1 = 523 + (r * 8) + i;
		wall.y1 = lineo;
		wall.x2 = 523 + (r * 8) + i;
		wall.y2 = lineh + lineo;
		draw_line(minimap, rays, &wall);
		i++;
	}
	return (0);
}
