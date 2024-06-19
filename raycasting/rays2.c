/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 17:23:31 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_vertical_wall(t_cub *cub, t_rays *rays)
{
	while (rays->ry <= (cub->mapy * cub->unitpc) && rays->dof < cub->mapx)
	{
		rays->mx = (int)(rays->rx) / cub->unitpc;
		rays->my = (int)(rays->ry) / cub->unitpc;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& cub->map[rays->mp] == 1)
		{
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->distv = distance(cub->player_x, cub->player_y, rays->vx,
					rays->vy);
			rays->dof = cub->mapx;
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
		rays->rx = (((int)cub->player_x / cub->unitpc) * cub->unitpc) - 0.0001;
		rays->ry = (cub->player_x - rays->rx) * rays->ntan + cub->player_y;
		rays->xo = -cub->unitpc;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra < (PI / 2) || rays->ra > (3 * PI / 2))
	{
		rays->rx = (((int)cub->player_x / cub->unitpc) * cub->unitpc) + cub->unitpc;
		rays->ry = (cub->player_x - rays->rx) * rays->ntan + cub->player_y;
		rays->xo = cub->unitpc;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra == (PI / 2) || rays->ra == (3 * PI / 2))
	{
		rays->rx = cub->player_x;
		rays->ry = cub->player_y;
		rays->dof = cub->mapx;
	}
	check_if_vertical_wall(cub, rays);
	return (0);
}

// compare the distance of the horizontal and vertical walls hit

int	compare_distances(t_rays *rays)
{
	if (rays->r == 0)
	{
		printf("hx=%f hy=%f\n", rays->hx, rays->hy);
		printf("vx=%f vy=%f\n", rays->vx, rays->vy);
		printf("disth=%f distv=%f\n", rays->disth, rays->distv);	
	}
	if (rays->disth < rays->distv)
	{
		// printf("ray %d is horizontal\n", rays->r);
		rays->rx = rays->hx;
		rays->ry = rays->hy;
		rays->distt = rays->disth;
		rays->color = 0xB40000;
		if (rays->ra > PI)
			rays->wall = SOUTH;
	}
	if (rays->distv < rays->disth)
	{
		// printf("ray %d is vertical\n", rays->r);
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->distt = rays->distv;
		rays->color = 0xE60000;
		if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
			rays->wall = WEST;
		else
			rays->wall = EAST;
	}
	// printf("rx=%f ry=%f\n", rays->rx, rays->ry);
	return (0);
}
