/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 10:29:28 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_if_vertical_wall(t_cub *cub, t_rays *rays)
{
	while (rays->ry <= (cub->mapy * UNITPC) && rays->dof < cub->mapmax)
	{
		rays->mx = (int)(rays->rx) / UNITPC;
		rays->my = (int)(rays->ry) / UNITPC;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& (cub->map[rays->mp] == WALL || cub->map[rays->mp] == DOOR))
		{
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->distv = distance(cub->player_x, cub->player_y, rays->vx,
					rays->vy);
			rays->dof = cub->mapmax;
			if (cub->map[rays->mp] == DOOR)
				rays->wall = WDOOR;
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
int	check_vertical_lines(t_cub *cub, t_rays *rays)
{
	rays->dof = 0;
	rays->ntan = -tan(rays->ra);
	if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
	{
		rays->rx = (((int)cub->player_x / UNITPC) * UNITPC) - 0.0001;
		rays->ry = (cub->player_x - rays->rx) * rays->ntan + cub->player_y;
		rays->xo = -UNITPC;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra < (PI / 2) || rays->ra > (3 * PI / 2))
	{
		rays->rx = (((int)cub->player_x / UNITPC)
				* UNITPC) + UNITPC;
		rays->ry = (cub->player_x - rays->rx) * rays->ntan + cub->player_y;
		rays->xo = UNITPC;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra == (PI / 2) || rays->ra == (3 * PI / 2))
	{
		rays->rx = cub->player_x;
		rays->ry = cub->player_y;
		rays->dof = cub->mapmax;
	}
	check_if_vertical_wall(cub, rays);
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
		if (rays->ra > PI && rays->wall != WDOOR)
			rays->wall = SOUTH;
	}
	if (rays->distv < rays->disth)
	{
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->distt = rays->distv;
		rays->color = 0xE60000;
		if (rays->ra > PI / 2 && rays->ra < (3 * PI / 2) && rays->wall != WDOOR)
			rays->wall = WEST;
		else if (rays->wall != WDOOR)
			rays->wall = EAST;
	}
	return (0);
}

// if (rays->r == (WINW / 2))
	// {
	// 	printf("WALLS\nhx=%f hy=%f\n", rays->hx, rays->hy);
	// 	printf("vx=%f vy=%f\n", rays->vx, rays->vy);
	// 	printf("disth=%f distv=%f\n", rays->disth, rays->distv);	
	// }
