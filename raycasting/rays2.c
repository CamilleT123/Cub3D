/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/18 17:51:47 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_vertical_wall(t_cub *cub, t_rays *rays)
{
	while (rays->ry <= SMINIMAPY && rays->dof < 8)
	{
		rays->mx = (int)(rays->rx) / cub->ppc;
		rays->my = (int)(rays->ry) / cub->ppc;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& cub->map[rays->mp] == 1)
		{
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->distv = distance(cub->px, cub->py, rays->vx,
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
int	check_vertical_lines(t_cub *cub, t_rays *rays)
{
	rays->dof = 0;
	rays->ntan = -tan(rays->ra);
	if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
	{
		rays->rx = (((int)cub->px / cub->ppc) * cub->ppc) - 0.0001;
		rays->ry = (cub->px - rays->rx) * rays->ntan + cub->py;
		rays->xo = -cub->ppc;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra < (PI / 2) || rays->ra > (3 * PI / 2))
	{
		rays->rx = (((int)cub->px / cub->ppc) * cub->ppc) + cub->ppc;
		rays->ry = (cub->px - rays->rx) * rays->ntan + cub->py;
		rays->xo = cub->ppc;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra == (PI / 2) || rays->ra == (3 * PI / 2))
	{
		rays->rx = cub->px;
		rays->ry = cub->py;
		rays->dof = 8;
	}
	check_if_vertical_wall(cub, rays);
	return (0);
}

// compare the distance of the horizontal and vertical walls hit

int	compare_distances(t_rays *rays)
{
	// printf("hx=%f hy=%f\n", rays->hx, rays->hy);
	// printf("vx=%f vy=%f\n", rays->vx, rays->vy);
	// printf("disth=%f distv=%f\n", rays->disth, rays->distv);
	if (rays->disth < rays->distv)
	{
		// printf("ray %d is horizontal\n", rays->r);
		rays->rx = rays->hx;
		rays->ry = rays->hy;
		rays->distt = rays->disth;
		rays->color = 0xB40000;
		if (rays->ra > PI)
			rays->wall = 1;
	}
	if (rays->distv < rays->disth)
	{
		// printf("ray %d is vertical\n", rays->r);
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->distt = rays->distv;
		rays->color = 0xE60000;
		if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
			rays->wall = 2;
		else
			rays->wall = 3;
	}
	// printf("rx=%f ry=%f\n", rays->rx, rays->ry);
	return (0);
}
