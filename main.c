/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/18 14:41:55 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	struct_init(t_cub *cub, char *av)
{
	int	i;

	cub->win_width = 960;
	cub->win_height = 640;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
	cub->addr = NULL;
	cub->xmap = 128;
	cub->ymap = 128;
	cub->txt_size = 128;
	cub->mapx = 8; // x map en cases
	cub->mapy = 8; // y en case
	cub->mapsize = 64; // taille map en cases
	cub->ppc = cub->xmap / cub->mapx; // voir si case pas carree
	cub->px = 1 * cub->ppc + cub->ppc / 2; // x de depart (milieu de case)
	cub->py = 4 * cub->ppc + cub->ppc / 2;
	cub->pa = 0 * DR; // start angle
	cub->pdx = cos(cub->pa) * 5;
	cub->pdy = sin(cub->pa) * 5;
	
	int tableau[64] = { // 
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,1,0,0,1,
		1,0,0,1,0,0,0,1,
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

// int get_adresses(t_cub *cub)
// {
// 	cub->txt_add = (int *)mlx_get_data_addr(cub->txt, &cub->txt_bpp,
// 			&cub->txt_line_length, &cub->txt_edn);
// 	(void)cub;
// 	return (0);
// }

// int get_texture(t_cub *cub)
// {
// 	cub->txt = mlx_xpm_file_to_image(cub->mlx, "./Brick128.xpm",
// 			&cub->txt_width, &cub->txt_height);
// 	return (0);
// }

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
	cub.win = mlx_new_window(cub.mlx, cub.win_width, cub.win_height,
			"Cub3D");
	cub.img = mlx_new_image(cub.mlx, cub.win_width, cub.win_height);
	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel,
			&cub.line_length, &cub.endian);
	cub.txt = mlx_xpm_file_to_image(cub.mlx, "./Brick128.xpm",
			&cub.txt_width, &cub.txt_height);
	cub.txt_add = (int *)mlx_get_data_addr(cub.txt, &cub.txt_bpp,
			&cub.txt_line_length, &cub.txt_edn);
	// get_adresses(&cub);
	display(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &keymapping, &cub);
	mlx_hook(cub.win, DestroyNotify, NoEventMask, &close_win, &cub);
	mlx_loop(cub.mlx);
	(void)av;
}
