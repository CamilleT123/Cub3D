/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/21 11:44:51 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	struct_init(t_cub *cub, char **av)
{
	if (init_cub(av[1], cub))
		return (exit_map(cub, 1));
	if (init_map(cub))
		return (1);
	cub->ppc = SMINIMAPX / cub->mapx; // voir si case pas carree
	// cub->ppc = 16;
	if (cub->ppc < PPCMIN)
	{
		cub->ppc = SMINIMAPX / cub->mapy; // voir si case pas carree
		if (cub->ppc < PPCMIN)
			cub->ppc = PPCMIN;
	}
	cub->minimapx = cub->ppc * cub->mapx;
	cub->minimapy = cub->ppc * cub->mapy;
	// else
	// {
	// 	cub->minimapx = SMINIMAPX;
	// 	cub->minimapy = SMINIMAPY;
	// }
	// printf("mapx = %d\n", cub->mapx);
	// printf("mapy = %d\n", cub->mapy);
	printf("ppc = %d\n", cub->ppc);
	// printf("minimapx = %d\n", cub->minimapx);
	// printf("minimapy = %d\n", cub->minimapy);
	cub->unitpc = 16;
	if (cub->mapx >= cub->mapy)
		cub->mapmax = cub->mapx;
	else
		cub->mapmax = cub->mapy;
	// printf("unitpc = %d\n", cub->unitpc);
	// cub->player_xmini = cub->scene.start_x;
	// cub->player_ymini = cub->scene.start_y;
	// printf("player_xmini = %d\n", cub->player_xmini);
	// printf("player_ymini = %d\n", cub->player_ymini);
	// printf("start_x = %f\n", cub->scene.start_x);
	// printf("start_y = %f\n", cub->scene.start_y);
	cub->player_x = cub->scene.start_x * cub->unitpc + cub->unitpc / 2;
	cub->player_y = cub->scene.start_y * cub->unitpc + cub->unitpc / 2;
	cub->player_xmini = (cub->player_x / ((float)cub->unitpc / (float)cub->ppc));
	cub->player_ymini = (cub->player_y /  ((float)cub->unitpc / (float)cub->ppc));
	// printf("unitpc = %d\n", cub->unitpc);
	// printf("ppc = %d\n", cub->ppc);
	// printf("player_xmini = %f\n", cub->player_xmini);
	// printf("player_ymini = %f\n", cub->player_ymini);
	cub->pa = cub->scene.start_angle + PI;
	if (cub->pa > 2 * PI)
		cub->pa -= 2 * PI;
	// printf("pa=%f\n", cub->pa / DR);
	cub->pdx = cos(cub->pa) * 5;
	cub->pdy = sin(cub->pa) * 5;
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

static void	destroy_tex(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->texture[i]->img)
		{
			mlx_destroy_image(cub->mlx, cub->texture[i]->img);
			free(cub->texture[i]);
		}
		i++;
	}
	free(cub->texture);
}

int	close_win(t_cub *cub)
{
	if (cub->texture)
		destroy_tex(cub);
	if (cub->map)
		free(cub->map);
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

int	test_map(t_cub *cub)
{
	int	i;

	i = 0;
	ft_putar(cub->scene.map);
	printf("long: %d larg: %d total: %d\n", cub->mapx, cub->mapy, cub->mapsize);
	while (i < cub->mapsize)
	{
		printf("%d", cub->map[i]);
		if (i == cub->mapx - 1)
			printf("\n");
		if (i > cub->mapx && (i + 1) % cub->mapx == 0)
			printf("\n");
		i++;
	}
	return (0);
}
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
	printf("ok\n");
	test_map(&cub);
	printf("player_x = %f\n", cub.player_x);
	printf("player_y = %f\n", cub.player_y);
	// printf("player_xmini = %f\n", cub.player_xmini);
	// printf("player_ymini = %f\n", cub.player_ymini);
	display(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &keymapping, &cub);
	mlx_hook(cub.win, DestroyNotify, NoEventMask, &close_win, &cub);
	mlx_loop(cub.mlx);
	close_win(&cub);
}
//	test_map(&cub);
