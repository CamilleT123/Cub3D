/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 14:19:43 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	struct_init(t_cub *cub, char **av)
{
	if (init_cub(av[1], cub))
		return (1);
	if (init_map(cub))
		return (1);
	cub->ppc = SMINIMAPX / cub->mapx; // voir si case pas carree
	cub->px = cub->scene.start_x * cub->ppc + cub->ppc / 2;
	cub->py = cub->scene.start_y * cub->ppc + cub->ppc / 2;
	cub->pa = cub->scene.start_angle + PI;
	if (cub->pa > 2 * PI)
		cub->pa -= 2 * PI;
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
	ft_putar(cub->scene.map);
	printf("long: %d larg: %d total: %d\n", cub->mapx, cub->mapy, cub->mapsize);
	int	i;

	i = 0;
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

int	main(int ac, char **av)
{
	t_cub	cub;
	
	if (ac < 2)
		return (ft_putstr_fd("Error\nNo map", 2), 0);
	if (ac > 2)
		return (ft_putstr_fd("Error\ninclude only 1 map", 2), 0);
	if (struct_init(&cub, av))
		return (exit_map(&cub, 1));
	cub.img = mlx_new_image(cub.mlx, WINW, WINH);
	cub.addr = mlx_get_data_addr(cub.img, &cub.bits_per_pixel,
			&cub.line_length, &cub.endian);
	printf("ok\n");
	printf("px=%f py=%f\n", cub.px, cub.py);
	test_map(&cub);
	display(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &keymapping, &cub);
	mlx_hook(cub.win, DestroyNotify, NoEventMask, &close_win, &cub);
	mlx_loop(cub.mlx);
	close_win(&cub);
}
