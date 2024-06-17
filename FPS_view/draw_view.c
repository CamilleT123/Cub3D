/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/17 10:23:07 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display_floor(t_cub *cub) // garder le return et la protection ?
{
	int	i;
	int	j;

	if (cub->win == NULL)
		return (1);
	i = cub->win_height / 2;
	while (i < cub->win_height)
	{
		j = 0;
		while (j < cub->win_width)
			my_mlx_pixel_put(cub, j++, i, 0x515072);
			// my_mlx_pixel_put(cub, j++, i, cub->scene->f_color);
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
	while (i < cub->win_height / 2)
	{
		j = 0;
		while (j < cub->win_width)
			my_mlx_pixel_put(cub, j++, i, 0xb3b2dc);
			// my_mlx_pixel_put(cub, j++, i, cub->scene->c_color);
		++i;
	}
	return (0);
}

int	display(t_cub *cub)
{
	t_rays	rays;
	t_line	line;
	display_floor(cub);
	display_ceiling(cub);
	calculate_rays(cub, &rays);
	draw_map(cub);
	draw_rays(cub, &rays, &line);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
