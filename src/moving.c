/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 15:27:58 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_coll(t_cub *cub, t_collision *coll)
{
	int	addx;
	int	subx;
	int	addy;
	int	suby;

	addx = (int)((cub->player_x + coll->xo) / UNITPC);
	addy = (int)((cub->player_y + coll->yo) / UNITPC);
	subx = (int)((cub->player_x - coll->xo) / UNITPC);
	suby = (int)((cub->player_y - coll->yo) / UNITPC);
	coll->ax = coll->ipy * cub->mapx + addx;
	coll->sx = coll->ipy * cub->mapx + subx;
	coll->ay = addy * cub->mapx + coll->ipx;
	coll->sy = suby * cub->mapx + coll->ipx;
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
	init_coll(cub, collision);
	return (0);
}

int	moving_side(int key, t_cub *cub, t_collision *coll)
{
	init_collision_side(cub, coll);
	if (key == LEFTK)
	{
		if (cub->map[coll->ax] == FLOOR)
			cub->player_x += cub->pdy;
		if (cub->map[coll->ay] == FLOOR)
			cub->player_y -= cub->pdx;
	}
	if (key == RIGHTK)
	{
		if (cub->map[coll->sx] == FLOOR)
			cub->player_x -= cub->pdy;
		if (cub->map[coll->sy] == FLOOR)
			cub->player_y += cub->pdx;
	}
	return (0);
}

int	init_collision_straight(t_cub *cub, t_collision *coll)
{
	if (cub->pdx < 0)
		coll->xo = -SECDIST;
	else
		coll->xo = SECDIST;
	if (cub->pdy < 0)
		coll->yo = -SECDIST;
	else
		coll->yo = SECDIST;
	cub->player_xmini = (cub->player_x / ((float)UNITPC
				/ (float)cub->ppc));
	cub->player_ymini = (cub->player_y / ((float)UNITPC
				/ (float)cub->ppc));
	init_coll(cub, coll);
	return (0);
}

int	moving_straight(int key, t_cub *cub, t_collision *coll)
{
	init_collision_straight(cub, coll);
	if (key == FORWARDK)
	{
		if (cub->map[coll->ax] == FLOOR)
			cub->player_x += cub->pdx;
		if (cub->map[coll->ay] == FLOOR)
			cub->player_y += cub->pdy;
	}
	if (key == BACKK)
	{
		if (cub->map[coll->sx] == FLOOR)
			cub->player_x -= cub->pdx;
		if (cub->map[coll->sy] == FLOOR)
			cub->player_y -= cub->pdy;
	}
	return (0);
}

// printf("cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] = %d\n",
	// collision->ipy * cub->mapx + collision->ipx_add_xo);
// printf("pdx = %f   pdy = %f\n", cub->pdx, cub->pdy);
// printf("xo = %d    yo = %d\n", xo, yo);
// 	printf("ipx_sub_xo = %d    ipy_sub_yo = %d\n", ipx_sub_xo, ipy_sub_yo);

/*
int	init_collision_side(t_cub *cub, t_collision *collision)
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
	else
		// donc si cos positif ou proche de null donc angle entre 0 et 
		// 90 ou 270 et 360
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
