/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 17:59:14 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display_floor(t_cub *cub) // garder le return et la protection ?
{
	int	i;
	int	j;

	if (cub->win == NULL)
		return (1);
	i = cub->ymap / 2;
	while (i < cub->ymap)
	{
		j = 523;
		while (j < cub->xmap * 2 && j < 1011)
			my_mlx_pixel_put(cub, j++, i, 0x515072);
		++i;
	}
	return (0);
}

int	display_ceiling(t_cub *cub)
{
	int	i;
	int	j;

	if (cub->win == NULL)
		return (1);
	i = 0;
	while (i < cub->ymap / 2)
	{
		j = 523;
		while (j < cub->xmap * 2 && j < 1011)
			my_mlx_pixel_put(cub, j++, i, 0xb3b2dc);
		++i;
	}
	return (0);
}

int	display(t_cub *cub)
{
	display_back(cub);
	display_floor(cub);
	display_ceiling(cub);
	draw_map(cub);
	draw_player(cub, cub->px, cub->py);
	draw_rays(cub);
	draw_square(cub, cub->px + 20, cub->py + 20);
	draw_square(cub, cub->px + 20, cub->py);
	draw_square(cub, cub->px, cub->py + 20);

	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
