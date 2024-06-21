/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:31:13 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/21 11:36:58 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check where the ray hit the horizontal lines

int	check_if_horizontal_wall_mini(t_cub *cub, t_rays *rays)
{
	while (rays->rx <= (cub->mapx * cub->ppc) && rays->dof < cub->mapmax)
	{
		rays->mx = (int)(rays->rx) / cub->ppc;
		rays->my = (int)(rays->ry) / cub->ppc;
		rays->mp = rays->my * cub->mapx + rays->mx;
		if (rays->mp > 0 && rays->mp < cub->mapx * cub->mapy
			&& cub->map[rays->mp] == 1)
		{
			rays->dof = cub->mapmax;
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->disth = distance(cub->player_xmini, cub->player_ymini, rays->hx,
					rays->hy);
			// if (rays->r == 28)
			// {
			// 	printf("yo");
			// 	printf("hx = %f\n", rays->hx);
			// 	printf("hy = %f\n", rays->hy);
			// }
		}
		else
		{
			rays->rx += rays->xo;
			rays->ry += rays->yo;
			rays->dof += 1;
			// if (rays->r == 28)
			// {
			// 	printf("mapx = %d\n", cub->mapx);
			// 	printf("1.rx = %f\n", rays->rx);
			// 	printf("1.ry = %f\n", rays->ry);
			// 	printf("dof = %d\n", rays->dof);
			// }
		}
	}
	// if (rays->r == 28)
	// {
	// 	printf("1.rx = %f\n", rays->rx);
	// 	printf("1.ry = %f\n", rays->ry);
	// 	printf("rx = %f, MNI= %d, dof = %d, mapx = %d", rays->rx, (cub->mapx * cub->ppc), rays->dof, cub->mapx);
	// }
	return (0);
}

// rays->atan = la pente de la ligne perpendiculaire à la direction du joueur
// check where the ray hit the vertical lines first if player is looking up, 
// then if looking down and finally if looking left or right

int	check_horizontal_lines_mini(t_cub *cub, t_rays *rays)
{
	rays->dof = 0;
	rays->atan = (-1) / (tan(rays->ra));
	// printf("pa = %f\n", cub->pa / DEGTORAD);
	if (rays->ra > PI)
	{
		// if (rays->r == 59 || rays->r == 0)
		// 	printf("\n4ra = %f\n", rays->ra / DEGTORAD);
		rays->ry = (((int)cub->player_ymini / cub->ppc) * cub->ppc) - 0.0001;
		rays->rx = (cub->player_ymini - rays->ry) * rays->atan + cub->player_xmini;
		rays->yo = -cub->ppc;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra < PI && rays->ra > 0)
	{
		// if (rays->r == 59 || rays->r == 0)
		// 	printf("\n5ra = %f\n", rays->ra / DEGTORAD);
		rays->ry = (((int)cub->player_ymini / cub->ppc) * cub->ppc) + cub->ppc;
		rays->rx = (cub->player_ymini - rays->ry) * rays->atan + cub->player_xmini;
		rays->yo = cub->ppc;
		rays->xo = -rays->yo * rays->atan;
		// if (rays->r == 59)
		// {
		// 	printf("if ra < %f et ra > 0 , ra = %f\n", PI, rays->ra / DEGTORAD);
		// 	printf("rx = %f\n", rays->rx);
		// 	printf("ry = %f\n", rays->ry);
		// }
	}
	if (rays->ra == 0 || rays->ra == PI)
	{
		// printf("if ra = 0 ou ra = %f, ra = %f\n", PI, rays->ra);
		// if (rays->r == 59 || rays->r == 0)
		// 	printf("\n6ra = %f\n", rays->ra / DEGTORAD);
		rays->rx = cub->player_xmini;
		rays->ry = cub->player_ymini;
		rays->dof = cub->mapmax;
	}
	check_if_horizontal_wall_mini(cub, rays);
	// if (rays->r == 59)
	// {
	// 	printf("hx = %f\n", rays->hx);
	// 	printf("hy = %f\n", rays->hy);
	// }
	return (0);
}

int	rays_init_mini(t_cub *cub, t_rays *rays)
{
	rays->r = 0;
	rays->rx = 0;
	rays->ry = 0;
	rays->ra = cub->pa - ((FIELDOFVIEW / 2) * DEGTORAD);
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

int	init_each_ray_mini(t_cub *cub, t_rays *rays)
{
	rays->hx = cub->player_xmini;
	rays->hy = cub->player_ymini;
	rays->vx = cub->player_xmini;
	rays->vy = cub->player_ymini;
	rays->disth = 1000000;
	rays->distv = 1000000;
	rays->wall = 0;
	return (0);
}

int	calculate_rays_mini(t_cub *cub, t_rays *rays)
{
	while (rays->r < WINW)
	{
		init_each_ray(cub, rays);
		check_horizontal_lines(cub, rays);
		check_vertical_lines(cub, rays);
		compare_distances(rays);
		draw_walls(cub, rays);
		rays->ra += 0.075 * DEGTORAD;
		if (rays->ra < 0)
			rays->ra += 2 * PI;
		if (rays->ra > 2 * PI)
			rays->ra -= 2 * PI;
		rays->r++;
	}
	return (0);
}
