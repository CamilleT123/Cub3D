/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:33:28 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/20 20:14:51 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fix_fish_eye(t_cub *cub, t_rays *rays)
{
	float	ca;

	ca = cub->pa - rays->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	rays->distt = rays->distt * cos(ca);
}

// ca is use ti fix fish eye effect
// line_height is the line height and lineo is the line offset

// @Cam - line-off - verifier si le 2 est int ou float 

int	draw_walls(t_cub *cub, t_rays *rays)
{
	t_line	wall;
	float	line_off;

	fix_fish_eye(cub, rays);
	wall.line_height = (cub->mapy * (WINH)) / rays->distt;
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
	bresenham_walls(cub, rays, &wall);
	return (0);
}
