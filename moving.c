/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 17:37:18 by ctruchot         ###   ########.fr       */
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
	collision->ipx_add_xo = (cub->player_x + collision->xo) / cub->unitpc;
	collision->ipx_sub_xo = (cub->player_x - collision->xo) / cub->unitpc;
	collision->ipy_add_yo = (cub->player_y + collision->yo) / cub->unitpc;
	collision->ipy_sub_yo = (cub->player_y - collision->yo) / cub->unitpc;
	// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx + collision->ipx_sub_xo, cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo]);
	// printf("2.cub->map[%d] = %d\n", collision->ipy_sub_yo * cub->mapx + collision->ipx, cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx]);
	// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx + collision->ipx_add_xo, cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo]);
	// printf("2.cub->map[%d] = %d\n", collision->ipy_add_yo * cub->mapx + collision->ipx, cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx]);
	// 	printf("ipx = %d   ipy = %d\n", collision->ipx, collision->ipy);
	// 	printf("case du player %d\n", collision->ipy * cub->mapx + collision->ipx);
	// 	printf("px = %f   py = %f\n", cub->player_x, cub->player_y);
	// 	printf("px - xo = %f   py - yo = %f\n", cub->player_x - collision->xo, cub->player_y - collision->yo);
	if (key == LEFTK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] == 0)
			cub->player_x += cub->pdy;
		if (cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx] == 0)
			cub->player_y -= cub->pdx;
	}
	if (key == RIGHTK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo] == 0)
			cub->player_x -= cub->pdy;
		if (cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx] == 0)
			cub->player_y += cub->pdx;
	}
	return (0);
}
	// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx + collision->ipx_sub_xo, cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo]);
	// printf("2.cub->map[%d] = %d\n", collision->ipy_sub_yo * cub->mapx + collision->ipx, cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx]);
	// printf("1.cub->map[%d] = %d\n", collision->ipy * cub->mapx + collision->ipx_add_xo, cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo]);
	// printf("2.cub->map[%d] = %d\n", collision->ipy_add_yo * cub->mapx + collision->ipx, cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx]);
	// 	printf("ipx = %d   ipy = %d\n", collision->ipx, collision->ipy);
	// 	printf("case du player %d\n", collision->ipy * cub->mapx + collision->ipx);
	// 	printf("px = %f   py = %f\n", cub->player_x, cub->player_y);
	// 	printf("px - xo = %f   py - yo = %f\n", cub->player_x - collision->xo, cub->player_y - collision->yo);

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
	collision->ipx_add_xo = (cub->player_x + collision->xo) / cub->unitpc;
	collision->ipx_sub_xo = (cub->player_x - collision->xo) / cub->unitpc;
	collision->ipy_add_yo = (cub->player_y + collision->yo) / cub->unitpc;
	collision->ipy_sub_yo = (cub->player_y - collision->yo) / cub->unitpc;
	return (0);
}

int	moving_straight(int key, t_cub *cub, t_collision *collision)
{
	init_collision_straight(cub, collision);
	if (key == FORWARDK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] == 0)
			cub->player_x += cub->pdx;
		if (cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx] == 0)
			cub->player_y += cub->pdy;
	}
	if (key == BACKK)
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo] == 0)
			cub->player_x -= cub->pdx;
		if (cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx] == 0)
			cub->player_y -= cub->pdy;
	}
	return (0);
}
	// printf("pdx = %f   pdy = %f\n", cub->pdx, cub->pdy);
		// printf("xo = %d    yo = %d\n", xo, yo);
	// 	printf("ipx_sub_xo = %d    ipy_sub_yo = %d\n", ipx_sub_xo, ipy_sub_yo);

int	keymapping(int key, t_cub *cub)
{
	t_collision	collision;

	collision.ipx = cub->player_x / cub->unitpc;
	collision.ipy = cub->player_y / cub->unitpc;
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
