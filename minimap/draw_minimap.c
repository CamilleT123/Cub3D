/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:55:08 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 14:34:00 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cropped_map(t_cub *cub, t_minimap *mini)
{
	int	x;

	x = 0;
	mini->xmin = (cub->player_x / 2) - (SMINIMAPX / 2);
	while (x < SMINIMAPX && mini->xmin < mini->xmax)
	{
		if (mini->xmin >= 0 && mini->ymin >= 0)
		{
			if (cub->map[(mini->ymin / 8) * cub->mapx + (mini->xmin / 8)] == 1)
				my_mlx_pixel_put(cub, x, mini->y, 0x7f388b);
			if (cub->map[(mini->ymin / 8) * cub->mapx + (mini->xmin / 8)] == 0)
				my_mlx_pixel_put(cub, x, mini->y, 0xbdabc4);
		}
		++mini->xmin;
		++x;
	}
}

int	crop_map(t_cub *cub)
{
	t_minimap	mini;

	mini.xmin = (cub->player_x / 2) - (SMINIMAPX / 2);
	mini.ymin = (cub->player_y / 2) - (SMINIMAPY / 2);
	mini.xmax = (cub->player_x / 2) + (SMINIMAPX / 2);
	mini.ymax = (cub->player_y / 2) + (SMINIMAPY / 2);
	mini.y = 0;
	while (mini.y < SMINIMAPY && mini.ymin < mini.ymax)
	{
		draw_cropped_map(cub, &mini);
		++mini.ymin;
		++mini.y;
	}
	draw_player(cub, (SMINIMAPX / 2), (SMINIMAPY / 2));
	return (0);
}

int	draw_minimap(t_cub *cub)
{
	cub->ppc = PPCMIN;
	while (cub->ppc < PPCMAX && ((cub->mapx * cub->ppc) < MINIMAPMIN
			|| (cub->mapy * cub->ppc) < MINIMAPMIN)
		&& ((cub->mapx * cub->ppc) < MINIMAPMAX
			&& (cub->mapy * cub->ppc) < MINIMAPMAX))
		cub->ppc++;
	if (cub->mapx * cub->ppc > 480 || cub->mapy * cub->ppc > 480
		|| cub->mapsize * cub->ppc > 65536)
	{
		cub->ppc = MINIMAPPPC;
		cub->minimapx = cub->ppc * 8;
		cub->minimapy = cub->ppc * 8;
		crop_map(cub);
	}
	else
	{
		cub->minimapx = cub->ppc * cub->mapx;
		cub->minimapy = cub->ppc * cub->mapy;
		draw_full_map(cub);
	}
	return (0);
}
