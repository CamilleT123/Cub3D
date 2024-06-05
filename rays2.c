/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/04 16:13:29 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_vertical_wall(t_minimap *minimap, t_rays *rays)
{
	while (rays->ry <= minimap->ymap && rays->dof < 8)
	{
		rays->mx = (int)(rays->rx) / 64;
		rays->my = (int)(rays->ry) / 64;
		rays->mp = rays->my * minimap->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < minimap->mapx * minimap->mapy
			&& minimap->map[rays->mp] == 1)
		{
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->distv = distance(minimap->px, minimap->py, rays->vx,
					rays->vy);
			rays->dof = 8;
		}
		else
		{
			rays->rx += rays->xo;
			rays->ry += rays->yo;
			rays->dof += 1;
		}
	}
	return (0);
}

// check where the ray hit the vertical lines first if player is looking left, 
// then if looking right and finally if looking up or down
int	check_vertical_lines(t_minimap *minimap, t_rays *rays)
{
	rays->dof = 0;
	rays->ntan = -tan(rays->ra);
	if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
	{
		rays->rx = (((int)minimap->px / 64) * 64) - 0.0001;
		rays->ry = (minimap->px - rays->rx) * rays->ntan + minimap->py;
		rays->xo = -64;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra < (PI / 2) || rays->ra > (3 * PI / 2))
	{
		rays->rx = (((int)minimap->px / 64) * 64) + 64;
		rays->ry = (minimap->px - rays->rx) * rays->ntan + minimap->py;
		rays->xo = 64;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra == (PI / 2) || rays->ra == (3 * PI / 2))
	{
		rays->rx = minimap->px;
		rays->ry = minimap->py;
		rays->dof = 8;
	}
	check_if_vertical_wall(minimap, rays);
	return (0);
}

// compare the distance of the horizontal and vertical walls hit

int	compare_distances(t_rays *rays)
{
	if (rays->disth < rays->distv)
	{
		rays->rx = rays->hx;
		rays->ry = rays->hy;
		rays->distt = rays->disth;
		rays->color = 0xB40000;
	}
	if (rays->distv < rays->disth)
	{
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->distt = rays->distv;
		rays->color = 0xE60000;
	}
	return (0);
}
