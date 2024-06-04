/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:31:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/30 18:36:36 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check where the ray hit the horizontal lines

int	check_if_horizontal_wall(t_minimap *minimap, t_rays *rays)
{
	while (rays->rx <= minimap->xmap && rays->dof < 8)
	{
		rays->mx = (int)(rays->rx) / 64;
		rays->my = (int)(rays->ry) / 64;
		rays->mp = rays->my * minimap->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < minimap->mapx * minimap->mapy
			&& minimap->map[rays->mp] == 1)
		{
			rays->dof = 8;
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->disth = distance(minimap->px, minimap->py, rays->hx,
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

int	check_horizontal_lines(t_minimap *minimap, t_rays *rays)
{
	rays->dof = 0;
	rays->atan = (-1) / (tan(rays->ra));
	if (rays->ra > PI)
	{
		rays->ry = (((int)minimap->py / 64) * 64) - 0.0001;
		rays->rx = (minimap->py - rays->ry) * rays->atan + minimap->px;
		rays->yo = -64;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra < PI && rays->ra > 0)
	{
		rays->ry = (((int)minimap->py / 64) * 64) + 64;
		rays->rx = (minimap->py - rays->ry) * rays->atan + minimap->px;
		rays->yo = 64;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra == 0 || rays->ra == PI)
	{
		rays->rx = minimap->px;
		rays->ry = minimap->py;
		rays->dof = 8;
	}
	check_if_horizontal_wall(minimap, rays);
	return (0);
}

int	rays_init(t_minimap *minimap, t_rays *rays)
{
	rays->rx = 0;
	rays->ry = 0;
	rays->ra = minimap->pa - (30 * DR);
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
	return (0);
}

int	init_each_ray(t_minimap *minimap, t_rays *rays)
{
	rays->hx = minimap->px;
	rays->hy = minimap->py;
	rays->vx = minimap->px;
	rays->vy = minimap->py;
	rays->disth = 1000000;
	rays->distv = 1000000;
	return (0);
}

int	draw_rays(t_minimap *minimap)
{
	t_rays	rays;
	t_line	line;
	int		r;

	rays_init(minimap, &rays);
	r = 0;
	while (r < 60)
	{
		init_each_ray(minimap, &rays);
		check_horizontal_lines(minimap, &rays);
		check_vertical_lines(minimap, &rays);
		compare_distances(&rays);
		init_line(minimap, &rays, &line);
		draw_line(minimap, &rays, &line);
		draw_walls(minimap, &rays, r);
		rays.ra += DR;
		if (rays.ra < 0)
			rays.ra += 2 * PI;
		if (rays.ra > 2 * PI)
			rays.ra -= 2 * PI;
		r++;
	}
	return (0);
}
