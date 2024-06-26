/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/26 21:53:41 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_coll(t_cub *cub, t_collision *coll)
{
	coll->ax = coll->ipy * cub->mapx + ((cub->player_x + coll->xo) / UNITPC);
	coll->sx = coll->ipy * cub->mapx + ((cub->player_x - coll->xo) / UNITPC);
	coll->ay = ((cub->player_y + coll->yo) / UNITPC) * cub->mapx + coll->ipx;
	coll->sy = ((cub->player_y - coll->yo) / UNITPC) * cub->mapx + coll->ipx;
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
		if (cub->map[coll->ax] == FLOOR || cub->map[coll->ax] == ODOOR)
			cub->player_x += cub->pdy;
		if (cub->map[coll->ay] == FLOOR || cub->map[coll->ay] == ODOOR)
			cub->player_y -= cub->pdx;
	}
	if (key == RIGHTK)
	{
		if (cub->map[coll->sx] == FLOOR || cub->map[coll->sx] == ODOOR)
			cub->player_x -= cub->pdy;
		if (cub->map[coll->sy] == FLOOR || cub->map[coll->sy] == ODOOR)
			cub->player_y += cub->pdx;
	}
	return (0);
}

/*
int	moving_side(int key, t_cub *cub, t_collision *coll)
{
	init_collision_side(cub, coll);
	coll->ipx_add_xo = (cub->player_x + coll->xo) / UNITPC;
	coll->ipx_sub_xo = (cub->player_x - coll->xo) / UNITPC;
	coll->ipy_add_yo = (cub->player_y + coll->yo) / UNITPC;
	coll->ipy_sub_yo = (cub->player_y - coll->yo) / UNITPC;
	if (key == LEFTK)
	{
		if (cub->map[coll->ipy * cub->mapx + coll->ipx_add_xo] == FLOOR)
			cub->player_x += cub->pdy;
		if (cub->map[coll->ipy_add_yo * cub->mapx + coll->ipx] == FLOOR)
			cub->player_y -= cub->pdx;
	}
	if (key == RIGHTK)
	{
		if (cub->map[coll->ipy * cub->mapx + coll->ipx_sub_xo] == FLOOR)
			cub->player_x -= cub->pdy;
		if (cub->map[coll->ipy_sub_yo * cub->mapx + coll->ipx] == FLOOR)
			cub->player_y += cub->pdx;
	}
	return (0);
}
*/
// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx
	// + collision->ipx_sub_xo, cub->map[collision->ipy * cub->mapx
	// + collision->ipx_sub_xo]);
// printf("2.cub->map[%d] = %d\n", collision->ipy_sub_yo * cub->mapx
	// + collision->ipx, cub->map[collision->ipy_sub_yo * cub->mapx
	// + collision->ipx]);
// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx
	// + collision->ipx_add_xo, cub->map[collision->ipy * cub->mapx
	// + collision->ipx_add_xo]);
// printf("2.cub->map[%d] = %d\n", collision->ipy_add_yo * cub->mapx
	// + collision->ipx, cub->map[collision->ipy_add_yo * cub->mapx
	// + collision->ipx]);
// 	printf("ipx = %d   ipy = %d\n", collision->ipx, collision->ipy);
// 	printf("case du player %d\n", collision->ipy * cub->mapx + collision->ipx);
// 	printf("px = %f   py = %f\n", cub->player_x, cub->player_y);
// 	printf("px - xo = %f   py - yo = %f\n", cub->player_x - collision->xo,
		// cub->player_y - collision->yo);

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
		if (cub->map[coll->ax] == DOOR)
			cub->map[coll->ax] = ODOOR;
		if (cub->map[coll->ay] == DOOR)
			cub->map[coll->ay] = ODOOR;
		if (cub->map[coll->ax] == FLOOR || cub->map[coll->ax] == ODOOR)
			cub->player_x += cub->pdx;
		if (cub->map[coll->ay] == FLOOR || cub->map[coll->ay] == ODOOR)
			cub->player_y += cub->pdy;
	}
	if (key == BACKK)
	{
		if (cub->map[coll->sx] == FLOOR || cub->map[coll->sx] == ODOOR)
			cub->player_x -= cub->pdx;
		if (cub->map[coll->sy] == FLOOR || cub->map[coll->sy] == ODOOR)
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
		// donc si cos positif ou proche de null donc angle entre 0 et 90 ou 270 et 360
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
