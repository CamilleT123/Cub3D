/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:33:28 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/18 15:23:46 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_line	wall;
	float	line_off;

	fix_fish_eye(cub, rays);
	wall.lineh = (cub->mapsize * (WINH) / 3) / rays->distt;
	wall.ty_step = cub->txt_size / (float)wall.lineh;
	wall.ty_off = 0;
	if (wall.lineh > WINH)
	{
		wall.ty_off = (wall.lineh - WINH) / 2.0;
		wall.lineh = WINH;
	}	
	line_off = (cub->win_height / 2) - (wall.lineh / 2);
	wall.x1 = rays->r;
	wall.y1 = line_off;
	wall.x2 = rays->r;
	wall.y2 = wall.lineh + line_off;
	// draw_line(cub,rays, &wall);
	draw_line_walls(cub, rays, &wall);
	return (0);
}
