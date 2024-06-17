/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:04:05 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/07 17:20:47 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int get_adresses(cub);
{
	cub->texture[0]->addr = mlx_get_data_addr(cub->img, cub->bits_per_pixel,
			cub->line_length, cub->endian);
	return (0);
}

int get_texture(cub)
{
	int	img_width;
	int	img_height;

	cub->texture[0]->img = mlx_xpm_file_to_image(cub->mlx, "../textures/text128.xpm", &img_width, &img_height);
	return (0);
}
