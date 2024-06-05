/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 23:10:33 by ctruchot         ###   ########.fr       */
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


// int	keymapping(int key, t_cub *cub)
// {
// 	if (key == 65307)
// 		close_win(cub);
// 	if (key == 65363 || key == 65361)
// 		changing_direction(key, cub);
// 	// int xo; // offset = la boule de securite
// 	// int yo;
// 	int ipx; // player's position sur la grille
// 	int ipx_add_xo; // player's position + the offset
// 	// int ipx_sub_xo; // player's position - the offset
// 	int ipy;
// 	int ipy_add_yo;
// 	// int ipy_sub_yo;
// 	// pour pa = 0;
// 	int x_boule_devant = 20; 
// 	int y_boule_devant = 0;
// 	int x_boule_droite = 0;
// 	int y_boule_droite = 20;
// 	// int x_boule_derriere = -20; 
// 	// int y_boule_derriere = 0;
// 	int x_boule_gauche = 0;
// 	int y_boule_gauche = -20;

// 	// si j'avance 
	
// 	if (key == 119) // avance
// 	{
// 		ipx = cub->px / 64.0; // la case de mon player
// 		ipx_add_xo = (cub->px + x_boule_devant) / 64.0; // dans quelle case est ma boule
// 		ipy = cub->py / 64.0; // la case de mon player
// 		ipy_add_yo = (cub->py + y_boule_devant) / 64.0;
// 			printf("1.cub->map[%d] = %d\n", ipy * cub->mapx + ipx_add_xo, cub->map[ipy * cub->mapx + ipx_add_xo]);
// 			printf("ipy = %d\n", ipy);
// 			printf("ipx_add_xo = %d\n", ipx_add_xo);
// 		if (cub->map[ipy * cub->mapx + ipx_add_xo] == 0)
// 		{
// 			// printf("px + xo = %f\n", cub->px + xo);
// 			// draw_square(cub, ipx_add_xo * 64, ipy_add_yo * 64);
// 			// draw_line(cub, cub->px, cub->py, cub->px + xo, cub->py);
// 			// my_mlx_pixel_put(cub, ipx_add_xo, ipy_add_yo, 0x00FFFF);
// 			// printf("xo = %d\n", xo);
// 			cub->px += cub->pdx;
// 		}
// 			printf("2.cub->map[%d] = %d\n", ipy_add_yo * cub->mapx + ipx, cub->map[ipy_add_yo * cub->mapx + ipx]);
// 			printf("ipx = %d\n", ipx);
// 			printf("ipy_add_xo = %d\n", ipy_add_yo);
// 		if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 		{
// 			// printf("ipy_add_xo = %d\n", ipx_add_yo);
// 			// printf("yo = %d\n", yo);
// 			cub->py += cub->pdy;
// 		}
// 		// cub->px += cub->pdx;
// 		// cub->py += cub->pdy;
// 	}
// 	if (key == 115) // recule
// 	{
// 		if (cub->map[ipy * cub->mapx + ipx_sub_xo] == 0)
// 			cub->px -= cub->pdx;
// 		if (cub->map[ipy_sub_yo * cub->mapx + ipx] == 0)
// 			cub->py -= cub->pdy;
// 		// cub->px -= cub->pdx;
// 		// cub->py -= cub->pdy;
// 	}
// 	if (key == 97) // vers la gauche
// 	{
// 		ipx = cub->px / 64.0; // la case de mon player
// 		ipx_add_xo = (cub->px + x_boule_gauche) / 64.0; // dans quelle case est ma boule
// 		ipy = cub->py / 64.0; // la case de mon player
// 		ipy_add_yo = (cub->py + y_boule_gauche) / 64.0;
// 			printf("1.cub->map[%d] = %d\n", ipy * cub->mapx + ipx_add_xo, cub->map[ipy * cub->mapx + ipx_add_xo]);
// 			printf("ipy = %d\n", ipy);
// 			printf("ipx_add_xo = %d\n", ipx_add_xo);
// 		if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 			cub->px += cub->pdy;
// 		printf("2.cub->map[%d] = %d\n", ipy_add_yo * cub->mapx + ipx, cub->map[ipy_add_yo * cub->mapx + ipx]);
// 		printf("ipx = %d\n", ipx);
// 		printf("ipy_add_yo = %d\n", ipy_add_yo);
// 		if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 			cub->py -= cub->pdx;
// 	}
// 	if (key == 100) // droite
// 	{
// 		ipx = cub->px / 64.0; // la case de mon player
// 		ipx_add_xo = (cub->px + x_boule_droite) / 64.0; // dans quelle case est ma boule
// 		ipy = cub->py / 64.0; // la case de mon player
// 		ipy_add_yo = (cub->py + y_boule_droite) / 64.0;
// 			printf("1.cub->map[%d] = %d\n", ipy * cub->mapx + ipx_add_xo, cub->map[ipy * cub->mapx + ipx_add_xo]);
// 			printf("ipy = %d\n", ipy);
// 			printf("ipx_add_xo = %d\n", ipx_add_xo);
// 		if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 			cub->px -= cub->pdy;
// 		printf("2.cub->map[%d] = %d\n", ipy_add_yo * cub->mapx + ipx, cub->map[ipy_add_yo * cub->mapx + ipx]);
// 		printf("ipx = %d\n", ipx);
// 		printf("ipy_add_yo = %d\n", ipy_add_yo);
// 		if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 			cub->py += cub->pdx;
// 	}
// 	display(cub);
// 	return (0);
// }

typedef struct s_collision
{
	int xo; // offset = la boule de securite
	int yo;
	int ipx; // player's position sur la grille
	int ipx_add_xo; // player's position + the offset
	int ipx_sub_xo; // player's position - the offset
	int ipy;
	int ipy_add_yo;
	int ipy_sub_yo;
} t_collision;

int init_collision_side(t_cub *cub, t_collision *collision)
{
	if (cub->pdx < -0.000010) // cos negatif donc angle entre 90 et 270
	{
		if (cub->pdy < -0.000010) // si sin negatif donc angle entre 180 et 270
		{
			collision->xo = -20;
			collision->yo = 20;
		}
		else // donc si positif ou proche de null donc angle entre 90 et 180
		{
			collision->xo = +20; // pour 100
			collision->yo = +20;
		}
	}
	else // donc si cos positif ou proche de null donc angle entre 0 et 90 ou 270 et 360
	{
		collision->yo = -20;// pour 300
		if (cub->pdy < -0.000010) // donc angle entre 270 et 360
			collision->xo = -20; // ici 270
		else
			collision->xo = 20; // ici 90
	}
	return (0);
}

int moving_side(int key, t_cub *cub, t_collision *collision)
{
	init_collision_side(cub, collision);
	collision->ipx_add_xo = (cub->px + collision->xo) / 64.0;
	collision->ipx_sub_xo = (cub->px - collision->xo) / 64.0;
	collision->ipy_add_yo = (cub->py + collision->yo) / 64.0;
	collision->ipy_sub_yo = (cub->py - collision->yo) / 64.0;
	if (key == 97) // vers la gauche
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] == 0)
			cub->px += cub->pdy;
		if (cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx] == 0)
			cub->py -= cub->pdx;
	}
	if (key == 100) // droite
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo] == 0)
			cub->px -= cub->pdy;
		if (cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx] == 0)
			cub->py += cub->pdx;
	}
	return (0);
}

int init_collision_straight(t_cub *cub, t_collision *collision)
{
	if (cub->pdx < 0)
		collision->xo = -20;
	else
		collision->xo = 20;
	if (cub->pdy < 0)
		collision->yo = -20;
	else
		collision->yo = 20;

	collision->ipx_add_xo = (cub->px + collision->xo) / 64.0;
	collision->ipx_sub_xo = (cub->px - collision->xo) / 64.0;
	collision->ipy_add_yo = (cub->py + collision->yo) / 64.0;
	collision->ipy_sub_yo = (cub->py - collision->yo) / 64.0;
	return (0);
}

int moving_straight(int key, t_cub *cub, t_collision *collision)
{
	init_collision_straight(cub, collision);
	if (key == 119) // avance
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_add_xo] == 0)
			cub->px += cub->pdx;
		if (cub->map[collision->ipy_add_yo * cub->mapx + collision->ipx] == 0)
			cub->py += cub->pdy;
	}
	if (key == 115) // recule
	{
		if (cub->map[collision->ipy * cub->mapx + collision->ipx_sub_xo] == 0)
			cub->px -= cub->pdx;
		if (cub->map[collision->ipy_sub_yo * cub->mapx + collision->ipx] == 0)
			cub->py -= cub->pdy;
	}
	return (0);
	// printf("pdx = %f   pdy = %f\n", cub->pdx, cub->pdy);
	// 	printf("xo = %d    yo = %d\n", xo, yo);
	// 	printf("1.cub->map[%d] = %d\n", ipy * cub->mapx + ipx_sub_xo, cub->map[ipy * cub->mapx + ipx_sub_xo]);
	// 	printf("2.cub->map[%d] = %d\n", ipy_sub_yo * cub->mapx + ipx, cub->map[ipy_sub_yo * cub->mapx + ipx]);
	// 	printf("ipx = %d   ipy = %d\n", ipx, ipy);
	// 	printf("ipx_sub_xo = %d    ipy_sub_yo = %d\n", ipx_sub_xo, ipy_sub_yo);
	// 	printf("px = %f   py = %f\n", cub->px, cub->py);
	// 	printf("px - xo = %f   py - yo = %f\n", cub->px - xo, cub->py - yo);
}

int	keymapping(int key, t_cub *cub)
{
	t_collision collision;

	collision.ipx = cub->px / 64.0;
	collision.ipy = cub->py / 64.0;
	if (key == 65307)
		close_win(cub);
	if (key == 65363 || key == 65361)
		changing_direction(key, cub);
	if (key == 119 || key == 115)
		moving_straight(key, cub, &collision);
	if (key == 97 || key == 100)
		moving_side(key, cub, &collision);
	display(cub);
	return (0);
}


// int	keymapping_cotedroit(int key, t_cub *cub)
// {
// 	int xo; // offset = la boule de securite
// 	int yo;
// 	int ipx; // player's position sur la grille
// 	int ipx_add_xo; // player's position + the offset
// 	int ipx_sub_xo; // player's position - the offset
// 	int ipy;
// 	int ipy_add_yo;
// 	int ipy_sub_yo;
	
// 	// if (cub->pa > PI)
// 	if (cub->pdy < 0)
// 		xo = -20;
// 	else if (cub->pdy >= 0)
// 		xo = 20;
// 	if (cub->pdx < 0)
// 		yo = -20;
// 	else if (cub->pdx >= 0)
// 		yo = 20;
// 	ipx = cub->px / 64.0;
// 	ipx_add_xo = (cub->px + xo) / 64.0;
// 	// 
// 	ipx_sub_xo = (cub->px - xo) / 64.0;
// 	ipy = cub->py / 64.0;
// 	ipy_add_yo = (cub->py + yo) / 64.0;
// 	ipy_sub_yo = (cub->py - yo) / 64.0;
	
// 	// if (key == 65307)
// 	// 	close_win(cub);
// 	// if (key == 65363 || key == 65361)
// 	// 	changing_direction(key, cub);
// 	// if (key == 119) // avance
// 	// {
		
// 	// 	if (cub->map[ipy * cub->mapx + ipx_add_xo] == 0)
// 	// 		cub->px += cub->pdx;
// 	// 	if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 	// 		cub->py += cub->pdy;
// 	// 	// cub->px += cub->pdx;
// 	// 	// cub->py += cub->pdy;
// 	// }
// 	// if (key == 115) // recule
// 	// {
// 	// 	if (cub->map[ipy * cub->mapx + ipx_sub_xo] == 0)
// 	// 		cub->px -= cub->pdx;
// 	// 	if (cub->map[ipy_sub_yo * cub->mapx + ipx] == 0)
// 	// 		cub->py -= cub->pdy;
// 	// 	// cub->px -= cub->pdx;
// 	// 	// cub->py -= cub->pdy;
// 	// }
// 	// if (key == 97) // vers la gauche
// 	// {
// 	// 	cub->px += cub->pdy;
// 	// 	cub->py -= cub->pdx;
// 	// }
// 	if (key == 100) // d 
// 	{
// 		if (cub->map[ipy * cub->mapx + ipx_add_xo] == 0) 
// 			cub->px -= cub->pdy;
// 		if (cub->map[ipy_add_yo * cub->mapx + ipx] == 0)
// 			cub->py += cub->pdx;
// 		// cub->px -= cub->pdy;
// 		// cub->py += cub->pdx;
// 	}
// 	display(cub);
// 	return (0);
// }
