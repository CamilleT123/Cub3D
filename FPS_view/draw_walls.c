/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:33:28 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/07 11:09:29 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	init_line(t_cub *cub, t_rays *rays, t_line *line)
{
	line->x1 = cub->px;
	line->y1 = cub->py;
	line->x2 = rays->rx;
	line->y2 = rays->ry;
	return (0);
}

int	fix_fish_eye(t_cub *cub, t_rays *rays)
{
	float	ca;

	ca = cub->pa - rays->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	rays->distt = rays->distt * cos(ca);
	return (0);
}

// ca is use ti fix fish eye effect
// lineh is the line height and lineo is the line offset

int	draw_walls(t_cub *cub, t_rays *rays)
{
 // appelee pour chaqun des 60 rays
	t_line	wall;
	int		i;
	float	line_off;

	fix_fish_eye(cub, rays);
	wall.lineh = (cub->mapsize * 320) / rays->distt;
	wall.ty_step = 32.0 / (float)wall.lineh;
	wall.ty_off = 0;
	if (wall.lineh > 512) // dans tuto utilise un affichage de 320
	{
		wall.ty_off = (wall.lineh - 512) / 2.0;
		wall.lineh = 512;
	}	
	line_off = 256 - (wall.lineh / 2); // 160
	i = 0;
	while (i < 4)
	{
		wall.x1 = 523 + (rays->r * 4) + i;
		wall.y1 = line_off;
		wall.x2 = 523 + (rays->r * 4) + i;
		wall.y2 = wall.lineh + line_off;
		draw_line_walls(cub, rays, &wall); // plutot que tirer un trait, imprimer chaque pixel
		i++;
	}
	return (0);
}
