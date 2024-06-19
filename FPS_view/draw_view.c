/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 19:02:15 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_floor(t_cub *cub) // garder le return et la protection ?
{
	int	i;
	int	j;

	i = WINH / 2;
	while (i < WINH)
	{
		j = 0;
		while (j < WINW)
			my_mlx_pixel_put(cub, j++, i, cub->f_color);
		++i;
	}
}

void	display_ceiling(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINH / 2)
	{
		j = 0;
		while (j < WINW)
			my_mlx_pixel_put(cub, j++, i, cub->c_color);
		++i;
	}
}

int	display(t_cub *cub)
{
	t_rays	rays;
	// t_line	line;

	display_floor(cub);
	display_ceiling(cub);
	rays_init(cub, &rays);
	calculate_rays(cub, &rays);
	draw_map(cub);
	// draw_rays(cub, &rays, &line); //separer les calculs
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
