/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:31:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/18 17:51:34 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check where the ray hit the horizontal lines

int	check_if_horizontal_wall(t_cub *cub, t_rays *rays)
{
	while (rays->rx <= SMINIMAPX && rays->dof < 8)
	{
		rays->mx = (int)(rays->rx) / cub->ppc;
		rays->my = (int)(rays->ry) / cub->ppc;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& cub->map[rays->mp] == 1)
		{
			rays->dof = 8;
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->disth = distance(cub->px, cub->py, rays->hx,
					rays->hy);
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

// rays->atan = la pente de la ligne perpendiculaire à la direction du joueur
// check where the ray hit the vertical lines first if player is looking up, 
// then if looking down and finally if looking left or right

int	check_horizontal_lines(t_cub *cub, t_rays *rays)
{
	rays->dof = 0;
	rays->atan = (-1) / (tan(rays->ra));
	if (rays->ra > PI)
	{
		rays->ry = (((int)cub->py / cub->ppc) * cub->ppc) - 0.0001;
		rays->rx = (cub->py - rays->ry) * rays->atan + cub->px;
		rays->yo = -cub->ppc;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra < PI && rays->ra > 0)
	{
		rays->ry = (((int)cub->py / cub->ppc) * cub->ppc) + cub->ppc;
		rays->rx = (cub->py - rays->ry) * rays->atan + cub->px;
		rays->yo = cub->ppc;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra == 0 || rays->ra == PI)
	{
		rays->rx = cub->px;
		rays->ry = cub->py;
		rays->dof = 8;
	}
	check_if_horizontal_wall(cub, rays);
	return (0);
}

int	rays_init(t_cub *cub, t_rays *rays)
{
	rays->r = 0;
	rays->rx = 0;
	rays->ry = 0;
	rays->ra = cub->pa - (36 * DR);
	if (rays->ra < 0)
		rays->ra += 2 * PI;
	if (rays->ra > 2 * PI)
		rays->ra -= 2 * PI;
	rays->xo = 0;
	rays->yo = 0;
	rays->disth = 0;
	rays->distv = 0;
	rays->xstep = 0;
	rays->ystep = 0;
	rays->mp = 0;
	rays->mx = 0;
	rays->my = 0;
	rays->dof = 0;
	rays->nb_rays = 60;
	return (0);
}

int	init_each_ray(t_cub *cub, t_rays *rays)
{
	rays->hx = cub->px;
	rays->hy = cub->py;
	rays->vx = cub->px;
	rays->vy = cub->py;
	rays->disth = 1000000;
	rays->distv = 1000000;
	rays->wall = 0;
	return (0);
}

int	calculate_rays(t_cub *cub, t_rays *rays)
{
	rays_init(cub, rays);
	while (rays->r < WINW)
	{
		init_each_ray(cub, rays);
		check_horizontal_lines(cub, rays);
		check_vertical_lines(cub, rays);
		compare_distances(rays);
		draw_walls(cub, rays);
		rays->ra += 0.075 * DR;
		if (rays->ra < 0)
			rays->ra += 2 * PI;
		if (rays->ra > 2 * PI)
			rays->ra -= 2 * PI;
		rays->r++;
	}
	return (0);
}
