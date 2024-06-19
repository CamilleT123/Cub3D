/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 16:35:00 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	changing_direction(int key, t_cub *cub)
{
	if (key == 65361)
	{
		cub->pa -= 0.1;
		if (cub->pa < 0)
			cub->pa += 2 * PI;
		cub->pdx = cos(cub->pa) * 1;
		cub->pdy = sin(cub->pa) * 1;
	}
	if (key == 65363)
	{
		cub->pa += 0.1;
		if (cub->pa > 2 * PI)
			cub->pa -= 2 * PI;
		cub->pdx = cos(cub->pa) * 1;
		cub->pdy = sin(cub->pa) * 1;
	}
}

int	init_collision_side(t_cub *cub, t_collision *collision)
{
	if (cub->pdx < -0.000005)
	{
		if (cub->pdy < -0.000005)
		{
			collision->xo = -SECDIST;
			collision->yo = SECDIST;
		}
		else
		{
			collision->xo = SECDIST;
			collision->yo = SECDIST;
		}
	}
	else
	{
		collision->yo = -SECDIST;
		if (cub->pdy < -0.000005)
			collision->xo = -SECDIST;
		else
			collision->xo = SECDIST;
	}
	return (0);
}

int	moving_side(int key, t_cub *cub, t_collision *collision)
{
	init_collision_side(cub, collision);
	collision->ipx_add_xo = (cub->px + collision->xo) / cub->ppc;
	collision->ipx_sub_xo = (cub->px - collision->xo) / cub->ppc;
	collision->ipy_add_yo = (cub->py + collision->yo) / cub->ppc;
	collision->ipy_sub_yo = (cub->py - collision->yo) / cub->ppc;
	if (key == LEFTK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] == 0)
			cub->px += cub->pdy;
		if (cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx] == 0)
			cub->py -= cub->pdx;
	}
	if (key == RIGHTK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo] == 0)
			cub->px -= cub->pdy;
		if (cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx] == 0)
			cub->py += cub->pdx;
	}
	return (0);
}
	// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx + collision->ipx_sub_xo, cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo]);
	// printf("2.cub->map[%d] = %d\n", collision->ipy_sub_yo * cub->mapx + collision->ipx, cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx]);
	// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx + collision->ipx_add_xo, cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo]);
	// printf("2.cub->map[%d] = %d\n", collision->ipy_add_yo * cub->mapx + collision->ipx, cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx]);
	// 	printf("ipx = %d   ipy = %d\n", collision->ipx, collision->ipy);
	// 	printf("case du player %d\n", collision->ipy * cub->mapx + collision->ipx);
	// 	printf("px = %f   py = %f\n", cub->px, cub->py);
	// 	printf("px - xo = %f   py - yo = %f\n", cub->px - collision->xo, cub->py - collision->yo);

int	init_collision_straight(t_cub *cub, t_collision *collision)
{
	if (cub->pdx < 0)
		collision->xo = -SECDIST;
	else
		collision->xo = SECDIST;
	if (cub->pdy < 0)
		collision->yo = -SECDIST;
	else
		collision->yo = SECDIST;
	collision->ipx_add_xo = (cub->px + collision->xo) / cub->ppc;
	collision->ipx_sub_xo = (cub->px - collision->xo) / cub->ppc;
	collision->ipy_add_yo = (cub->py + collision->yo) / cub->ppc;
	collision->ipy_sub_yo = (cub->py - collision->yo) / cub->ppc;
	return (0);
}

int	moving_straight(int key, t_cub *cub, t_collision *collision)
{
	init_collision_straight(cub, collision);
	if (key == FORWARDK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] == 0)
			cub->px += cub->pdx;
		if (cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx] == 0)
			cub->py += cub->pdy;
	}
	if (key == BACKK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo] == 0)
			cub->px -= cub->pdx;
		if (cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx] == 0)
			cub->py -= cub->pdy;
	}
	return (0);
}
	// printf("pdx = %f   pdy = %f\n", cub->pdx, cub->pdy);
		// printf("xo = %d    yo = %d\n", xo, yo);
	// 	printf("ipx_sub_xo = %d    ipy_sub_yo = %d\n", ipx_sub_xo, ipy_sub_yo);

int	keymapping(int key, t_cub *cub)
{
	t_collision	collision;

	collision.ipx = cub->px / cub->ppc;
	collision.ipy = cub->py / cub->ppc;
	if (key == 65307)
		close_win(cub);
	if (key == 65363 || key == 65361)
		changing_direction(key, cub);
	if (key == FORWARDK || key == BACKK)
		moving_straight(key, cub, &collision);
	if (key == LEFTK || key == RIGHTK)
		moving_side(key, cub, &collision);
	display(cub);
	return (0);
}
/*
int init_collision_side(t_cub *cub, t_collision *collision)
{
	if (cub->pdx < -0.000005) // cos negatif donc angle entre 90 et 270
	{
		if (cub->pdy < -0.000005) // si sin negatif donc angle entre 180 et 270
		{
			collision->xo = -SECDIST;
			collision->yo = SECDIST;
		}
		else // donc si positif ou proche de null donc angle entre 90 et 180
		{
			collision->xo = +SECDIST; // pour 100
			collision->yo = +SECDIST;
		}
	}
	else // donc si cos positif ou proche de null donc angle entre 0 et 90 ou 270 et 360
	{
		collision->yo = -SECDIST;// pour 300
		if (cub->pdy < -0.000005) // donc angle entre 270 et 360
			collision->xo = -SECDIST; // ici 270
		else
			collision->xo = SECDIST; // ici 90
	}
	return (0);
}
*/
