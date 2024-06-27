/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:31:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 18:03:28 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check where the ray hit the horizontal lines

static int	check_if_horizontal_wall(t_cub *cub, t_rays *rays)
{
	while (rays->rx <= (cub->mapx * UNITPC) && rays->dof < cub->mapmax)
	{
		rays->mx = (int)(rays->rx) / UNITPC;
		rays->my = (int)(rays->ry) / UNITPC;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& (cub->map[rays->mp] == WALL))
		{
			rays->dof = cub->mapmax;
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->disth = distance(cub->player_x, cub->player_y, rays->hx,
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
		rays->ry = (((int)cub->player_y / UNITPC) * UNITPC) - 0.0001;
		rays->rx = (cub->player_y - rays->ry) * rays->atan + cub->player_x;
		rays->yo = -UNITPC;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra < PI && rays->ra > 0)
	{
		rays->ry = (((int)cub->player_y / UNITPC)
				* UNITPC) + UNITPC;
		rays->rx = (cub->player_y - rays->ry) * rays->atan + cub->player_x;
		rays->yo = UNITPC;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra == 0 || rays->ra == PI)
	{
		rays->rx = cub->player_x;
		rays->ry = cub->player_y;
		rays->dof = cub->mapmax;
	}
	check_if_horizontal_wall(cub, rays);
	return (0);
}

static int	init_each_ray(t_cub *cub, t_rays *rays)
{
	rays->hx = cub->player_x;
	rays->hy = cub->player_y;
	rays->vx = cub->player_x;
	rays->vy = cub->player_y;
	rays->disth = 1000000;
	rays->distv = 1000000;
	rays->wall = 0;
	return (0);
}

static int	rays_init(t_cub *cub, t_rays *rays)
{
	rays->r = 0;
	rays->rx = 0;
	rays->ry = 0;
	rays->ra = cub->player_angle - ((FIELDOFVIEW / 2) * DEGTORAD);
	if (rays->ra < 0)
		rays->ra += 2 * PI;
	if (rays->ra > 2 * PI)
		rays->ra -= 2 * PI;
	rays->xo = 0;
	rays->yo = 0;
	rays->disth = 0;
	rays->distv = 0;
	rays->mp = 0;
	rays->mx = 0;
	rays->my = 0;
	rays->dof = 0;
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
		compare_distances(cub, rays);
		draw_walls(cub, rays);
		rays->ra += (FIELDOFVIEW / WINW) * DEGTORAD;
		if (rays->ra < 0)
			rays->ra += 2 * PI;
		if (rays->ra > 2 * PI)
			rays->ra -= 2 * PI;
		rays->r++;
	}
	return (0);
}
