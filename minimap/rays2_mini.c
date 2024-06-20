/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:33 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/20 18:46:47 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_vertical_wall_mini(t_cub *cub, t_rays *rays)
{
	while (rays->ry <= (cub->mapy * cub->ppc) && rays->dof < cub->mapmax)
	{
		rays->mx = (int)(rays->rx) / cub->ppc;
		rays->my = (int)(rays->ry) / cub->ppc;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& cub->map[rays->mp] == 1)
		{
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->distv = distance(cub->player_xmini, cub->player_ymini, rays->vx,
					rays->vy);
			rays->dof = cub->mapmax;
			// if (rays->r == 30)
			// {
			// 	printf("FOUND1\nvx = %f\n", rays->vx);
			// 	printf("vy = %f\n", rays->vy);
			// }
		}
		else
		{
			rays->rx += rays->xo;
			rays->ry += rays->yo;
			rays->dof += 1;
			// if (rays->r == 30)
			// {
			// 	printf("ELSE\nmapx = %d\n", cub->mapx);
			// 	printf("1.rx = %f\n", rays->rx);
			// 	printf("1.ry = %f\n", rays->ry);
			// 	printf("dof = %d\n", rays->dof);
			// }
		}
	}
	return (0);
}

// check where the ray hit the vertical lines first if player is looking left, 
// then if looking right and finally if looking up or down
int	check_vertical_lines_mini(t_cub *cub, t_rays *rays)
{
	rays->dof = 0;
	rays->ntan = -tan(rays->ra);
	if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
	{
		// if (rays->r == 59)
		// 	printf("\n0ra = %f\n", rays->ra / DegtoRad);
		rays->rx = (((int)cub->player_xmini / cub->ppc) * cub->ppc) - 0.0001;
		rays->ry = (cub->player_xmini - rays->rx) * rays->ntan + cub->player_ymini;
		rays->xo = -cub->ppc;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra < (PI / 2) || rays->ra > (3 * PI / 2))
	{
		// if (rays->r == 59)
		// 	printf("\n1ra = %f\n", rays->ra / DegtoRad);
		rays->rx = (((int)cub->player_xmini / cub->ppc) * cub->ppc) + cub->ppc;
		rays->ry = (cub->player_xmini - rays->rx) * rays->ntan + cub->player_ymini;
		rays->xo = cub->ppc;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra == (PI / 2) || rays->ra == (3 * PI / 2))
	{
		// if (rays->r == 59)
		// 	printf("\n3ra = %f\n", rays->ra / DegtoRad);
		rays->rx = cub->player_xmini;
		rays->ry = cub->player_ymini;
		rays->dof = cub->mapmax;
	}
	// if (rays->r == 30)
	// {
	// 	printf("1.vx = %f\n", rays->hx);
	// 	printf("1.vy = %f\n", rays->hy);
	// }
	check_if_vertical_wall_mini(cub, rays);
	// if (rays->r == 30)
	// {
	// 	printf("2.vx = %f\n", rays->vx);
	// 	printf("2.vy = %f\n", rays->vy);
	// }
	return (0);
}

// compare the distance of the horizontal and vertical walls hit

int	compare_distances_mini(t_rays *rays)
{
	// if (rays->r == 30)
	// {
		printf("MINI\nhx=%f hy=%f\n", rays->hx, rays->hy);
		printf("vx=%f vy=%f\n", rays->vx, rays->vy);
		printf("disth=%f distv=%f\n", rays->disth, rays->distv);	
	// }
	if (rays->disth < rays->distv)
	{
		rays->rx = rays->hx;
		rays->ry = rays->hy;
		rays->distt = rays->disth;
		rays->color = 0xB40000;
		if (rays->ra > PI)
			rays->wall = SOUTH;
		// printf("rx=%f ry=%f\n", rays->rx, rays->ry);
	}
	if (rays->distv < rays->disth)
	{
		// printf("yo\n");
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->distt = rays->distv;
		rays->color = 0xE60000;
		if (rays->ra > (PI / 2) && rays->ra < (3 * PI / 2))
			rays->wall = WEST;
		else
			rays->wall = EAST;
	}
	return (0);
}
