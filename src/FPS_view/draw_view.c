/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 15:19:31 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_floor(t_cub *cub)
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

static void	display_ceiling(t_cub *cub)
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
	time_t	t;

	t = get_time();
	while (t < cub->t_update + DELAY)
	{
		t = get_time();
	}
	cub->t_update = t;
	display_floor(cub);
	display_ceiling(cub);
	calculate_rays(cub, &rays);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}
