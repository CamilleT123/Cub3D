/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 22:49:44 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	struct_init(t_cub *cub, char *av)
{
	int	i;

	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
	cub->addr = NULL;
	// cub->ymap = get_ymap(cub);
	// cub->xmap = get_xmap(cub);
	cub->xmap = 512;
	cub->ymap = 512;
	cub->px = 224;
	cub->py = 224;
	cub->pa = 250 * DR;
	cub->pdx = cos(cub->pa) * 5;
	cub->pdy = sin(cub->pa) * 5;
	cub->mapx = 8;
	cub->mapy = 8;
	cub->mapsize = 64;
	int tableau[64] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,1,0,0,1,
		1,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,1,1,1,1,1,1,1,
	};
	i = 0;
	while (i < 64)
	{
		cub->map[i] = tableau[i];
		i++;
	}
	(void)av;
	return (0);
}

int	close_win(t_cub *cub)
{
	if (cub->img != NULL)
		mlx_destroy_image(cub->mlx, cub->img);
	if (cub->win != NULL)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx != NULL)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	exit(0);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	
	if (ac < 2)
		return (printf("%s", "Error\nNo map"), 0);
	if (ac > 2)
		return (printf("%s", "Error\n include only 1 map"), 0);
	// if (check_map_format(av[1]) == 0)
	// 	return (ft_printf("Error\nError in map format\n"), 0);
	if (struct_init(&cub, av[1]) != 0)
		return (printf("Error\nError in reading map\n"), 0);
	// if (check_map(&game) == 0)
	// 	return (0);
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, cub.xmap * 2, cub.ymap,
			"Cub3D");
	cub.img = mlx_new_image(cub.mlx, 512 * 2, 512);
	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel,
			&cub.line_length, &cub.endian);
	display(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &keymapping, &cub);
	mlx_hook(cub.win, DestroyNotify, NoEventMask, &close_win, &cub);
	mlx_loop(cub.mlx);
	(void)av;
}
