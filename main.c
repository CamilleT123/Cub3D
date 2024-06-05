/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 19:12:29 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	struct_init(t_minimap *minimap, char *av)
{
	int	i;

	minimap->mlx = NULL;
	minimap->win = NULL;
	minimap->img = NULL;
	minimap->addr = NULL;
	// minimap->ymap = get_ymap(minimap);
	// minimap->xmap = get_xmap(minimap);
	minimap->xmap = 512;
	minimap->ymap = 512;
	minimap->px = 200;
	minimap->py = 200;
	minimap->pa = 0 * DR;
	minimap->pdx = cos(minimap->pa) * 5;
	minimap->pdy = sin(minimap->pa) * 5;
	minimap->mapx = 8;
	minimap->mapy = 8;
	minimap->mapsize = 64;
	int tableau[64] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,1,1,1,1,1,1,1,
	};
	i = 0;
	while (i < 64)
	{
		minimap->map[i] = tableau[i];
		i++;
	}
	(void)av;
	return (0);
}

int	close_win(t_minimap *minimap)
{
	if (minimap->img != NULL)
		mlx_destroy_image(minimap->mlx, minimap->img);
	if (minimap->win != NULL)
		mlx_destroy_window(minimap->mlx, minimap->win);
	if (minimap->mlx != NULL)
	{
		mlx_destroy_display(minimap->mlx);
		free(minimap->mlx);
	}
	exit(0);
}

int	changing_direction(int key, t_minimap *minimap)
{
	if (key == 65361)
	{
		minimap->pa -= 0.1;
		if (minimap->pa < 0)
			minimap->pa += 2 * PI;
		minimap->pdx = cos(minimap->pa) * 1;
		minimap->pdy = sin(minimap->pa) * 1;
	}
	if (key == 65363)
	{
		minimap->pa += 0.1;
		if (minimap->pa > 2 * PI)
			minimap->pa -= 2 * PI;
		minimap->pdx = cos(minimap->pa) * 1;
		minimap->pdy = sin(minimap->pa) * 1;
	}
	return (0);
}

int	keymapping(int key, t_minimap *minimap)
{
	if (key == 65307)
		close_win(minimap);
	if (key == 65363 || key == 65361)
		changing_direction(key, minimap);
	if (key == 119) // avance
	{
		minimap->px += minimap->pdx;
		minimap->py += minimap->pdy;
	}
	if (key == 115) // recule
	{
		minimap->px -= minimap->pdx;
		minimap->py -= minimap->pdy;
	}
	if (key == 97) // vers la gauche
	{
		minimap->px += minimap->pdy;
		minimap->py -= minimap->pdx;
	}
	if (key == 100) // d 
	{
		minimap->px -= minimap->pdy;
		minimap->py += minimap->pdx;
	}
	display(minimap);
	// (void)minimap;
	return (1);
}

int	main(int ac, char **av)
{
	t_minimap	minimap;
	
	if (ac < 2)
		return (printf("%s", "Error\nNo map"), 0);
	if (ac > 2)
		return (printf("%s", "Error\n include only 1 map"), 0);
	if (struct_init(&minimap, av[1]) != 0)
		return (printf("Error\nError in reading map\n"), 0);
	// if (check_map(&game) == 0)
	// 	return (0);
	minimap.mlx = mlx_init();
	minimap.win = mlx_new_window(minimap.mlx, minimap.xmap * 2, minimap.ymap,
			"Cub3D");
	minimap.img = mlx_new_image(minimap.mlx, 512 * 2, 512);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel,
			&minimap.line_length, &minimap.endian);
	display(&minimap);
	
	mlx_key_hook(minimap.win, &keymapping, &minimap);
	// mlx_hook(minimap.win, 02, (1L << 0), &keymaping, &minimap);
	mlx_hook(minimap.win, 17, (1L << 17), &close_win, &minimap);
	mlx_loop(minimap.mlx);
	(void)av;
}
