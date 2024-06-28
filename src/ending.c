/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/28 16:45:44 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_tex(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->texture[i] && cub->texture[i]->img)
		{
			mlx_destroy_image(cub->mlx, cub->texture[i]->img);
			free(cub->texture[i]);
		}
		i++;
	}
	free(cub->texture);
	cub->texture = NULL;
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
