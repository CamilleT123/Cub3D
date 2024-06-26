/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_direction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/26 22:56:20 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	changing_direction(int key, t_cub *cub)
{
	if (key == ARIGHTK)
	{
		cub->player_angle -= 0.1;
		if (cub->player_angle < 0)
			cub->player_angle += 2 * PI;
		cub->pdx = cos(cub->player_angle) * 1;
		cub->pdy = sin(cub->player_angle) * 1;
	}
	else if (key == ALEFTK)
	{
		cub->player_angle += 0.1;
		if (cub->player_angle > 2 * PI)
			cub->player_angle -= 2 * PI;
		cub->pdx = cos(cub->player_angle) * 1;
		cub->pdy = sin(cub->player_angle) * 1;
	}
}

void	changing_direction_mouse(int x, t_cub *cub)
{
	if (x <= (cub->oldx - 10))
	{
		cub->player_angle -= 0.1;
		if (cub->player_angle < 0)
			cub->player_angle += 2 * PI;
		cub->pdx = cos(cub->player_angle);
		cub->pdy = sin(cub->player_angle);
		cub->oldx = x;
	}
	if (x > (cub->oldx + 10))
	{
		cub->player_angle += 0.1;
		if (cub->player_angle > 2 * PI)
			cub->player_angle -= 2 * PI;
		cub->pdx = cos(cub->player_angle);
		cub->pdy = sin(cub->player_angle);
		cub->oldx = x;
	}
}
