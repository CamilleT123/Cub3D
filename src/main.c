/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 15:27:54 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_init(t_cub *cub)
{
	cub->player_x = cub->scene.start_x * UNITPC + UNITPC / 2;
	cub->player_y = cub->scene.start_y * UNITPC + UNITPC / 2;
	cub->player_xmini = (cub->player_x / ((float)UNITPC / (float)cub->ppc));
	cub->player_ymini = (cub->player_y / ((float)UNITPC / (float)cub->ppc));
	cub->player_angle = cub->scene.start_angle + PI;
	if (cub->player_angle > 2 * PI)
		cub->player_angle -= 2 * PI;
	cub->pdx = cos(cub->player_angle) * 5;
	cub->pdy = sin(cub->player_angle) * 5;
}

static int	struct_init(t_cub *cub, char **av)
{
	if (init_cub(av[1], cub))
		return (exit_map(cub, 1));
	if (init_map(cub))
		return (1);
	if (cub->mapx >= cub->mapy)
		cub->mapmax = cub->mapx;
	else
		cub->mapmax = cub->mapy;
	cub->oldx = WINW / 2;
	player_init(cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (free(cub->map), exit_map(cub, 1), 1);
	cub->win = mlx_new_window(cub->mlx, WINW, WINH, av[0]);
	if (!cub->win)
		return (close_win(cub), exit_map(cub, 1), 1);
	if (init_textures(cub))
		return (close_win(cub), exit_map(cub, 1), 1);
	exit_map(cub, 0);
	return (0);
}

int	keymapping(int key, t_cub *cub)
{
	t_collision	collision;

	collision.ipx = cub->player_x / UNITPC;
	collision.ipy = cub->player_y / UNITPC;
	if (key == ESCK)
		close_win(cub);
	if (key == ALEFTK || key == ARIGHTK)
		changing_direction(key, cub);
	if (key == FORWARDK || key == BACKK)
		moving_straight(key, cub, &collision);
	if (key == LEFTK || key == RIGHTK)
		moving_side(key, cub, &collision);
	display(cub);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac < 2)
		return (ft_putstr_fd("Error\nNo map", 2), 0);
	if (ac > 2)
		return (ft_putstr_fd("Error\ninclude only 1 map", 2), 0);
	if (struct_init(&cub, av))
		return (1);
	cub.img = mlx_new_image(cub.mlx, WINW, WINH);
	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel,
			&cub.line_length, &cub.endian);
	display(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &keymapping, &cub);
	mlx_hook(cub.win, DestroyNotify, NoEventMask, &close_win, &cub);
	mlx_loop(cub.mlx);
	close_win(&cub);
}

//	test_map(&cub);

// int	test_map(t_cub *cub)
// {
// 	int	i;

// 	i = 0;
// 	ft_putar(cub->scene.map);
// 	printf("long: %d larg: %d total: %d\n", cub->mapx, cub->mapy, cub->mapsize);
// 	while (i < cub->mapsize)
// 	{
// 		printf("%d", cub->map[i]);
// 		if (i == cub->mapx - 1)
// 			printf("\n");
// 		if (i > cub->mapx && (i + 1) % cub->mapx == 0)
// 			printf("\n");
// 		i++;
// 	}
// 	return (0);
// }
	// printf("unitpc = %d\n", UNITPC);
	// cub->player_xmini = cub->scene.start_x;
	// cub->player_ymini = cub->scene.start_y;
	// printf("player_xmini = %d\n", cub->player_xmini);
	// printf("player_ymini = %d\n", cub->player_ymini);
	// printf("start_x = %f\n", cub->scene.start_x);
	// printf("start_y = %f\n", cub->scene.start_y);
	// printf("unitpc = %d\n", UNITPC);
	// printf("ppc = %d\n", cub->ppc);
	// printf("player_xmini = %f\n", cub->player_xmini);
	// printf("player_ymini = %f\n", cub->player_ymini);
