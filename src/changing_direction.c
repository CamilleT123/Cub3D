/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_direction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:48:26 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 14:39:57 by ctruchot         ###   ########.fr       */
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
