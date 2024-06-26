/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:12:53 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/26 19:36:37 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	ft_sign(int n)
{
	if (n < 0)
		return (-1);
	else if (n > 0)
		return (1);
	return (0);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINW || y < 0 || y >= WINH)
		return ;
	dst = cub->addr + (y * cub->line_length + x
			* (cub->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
