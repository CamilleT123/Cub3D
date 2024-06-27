/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 15:57:18 by aduvilla         ###   ########.fr       */
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
