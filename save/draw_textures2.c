/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:50:52 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 15:27:38 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_vertical_wall(t_line *line, t_bres *bres, t_cub *cub, t_rays *rays)
{
	int	y;
	
    line->ty = line->ty_off * line->ty_step; 
	// ty = texture y / ty_step = 32/lineh / on ajoute le step a chaque loop
	// ty_off = offset = libeh - 320 / 2
	if (rays->disth < rays->distv) // si mur horizontal
	{
		line->tx = (int)(rays->rx / 2.0) % 128;
		// line->tx = (int)(rays->rx) % 128;
		// pourquoi /2 since texture is half the size  of what?? // size of the texture
		// 128 is image size remplacer par bres->ptr_texture->width; 
		if (rays->ra < 180 * DR)
			line->tx = 127 - line->tx; // remplacer par bres->ptr_texture->width; 
	}
	else
	{
		line->tx = (int)(rays->ry / 2.0) % 128; // remplacer par bres->ptr_texture->width; 
		if (rays->ra > (90 * DR) && rays->ra < (270 * DR))
			line->tx = 127 - line->tx;	// remplacer par bres->ptr_texture->width; 
	}
	y = line->y1; // y = y du point 1
	// while (y < line->lineh)
	// {
	// 	line->color = get_color_texture(bres->ptr_texture, line->ty,
	// 			line->tx);
	// 	my_mlx_pixel_put(cub, line->x1, y, line->color);
	// 	// (t_cub *cub, int x, int y, int color)
	// 	y++;
	// 	line->ty += line->ty_step;
	// }
	
	while (y != line->y2 + bres->incy) // tant qu'on n'atteind pas le y du point 2
	{
		int	color = 0;
		int	pixel;

		pixel = (line->ty * line->lineh) + (line->tx * (cub->txt_bpp / 8));
		// pixel = line->ty * cub->txt_line_length / 4 + line->tx;
		// pixel =  (line->tx * 4) + (4 * cub->txt_line_length * line->ty);
		printf("pixel = %d\n", pixel);
		if (pixel < 16500 && pixel >= 0) // revoir limite
			color = *(unsigned int *)(cub->txt_add + pixel);
		printf("color = %d\n", color);


		// line->color = get_color_texture(bres->ptr_texture, line->ty,
		// 		line->ty);
	
		// rays->color = bres->ptr_texture->addr[pixel];
		my_mlx_pixel_put(cub, line->x1, y, color); 
		// on imprime le pixel en x1 (ligne verticale x ne bouge pas) et y qui bouge
		y += bres->incy;
		// y++;
		line->ty += line->ty_step; // on deplace le curseur de texture
	}
	return (0);
}


int	draw_line_walls(t_cub *cub, t_rays *rays, t_line *line)
{
	t_bres	bres;

	bres.dx = line->x2 - line->x1;
	bres.dy = line->y2 - line->y1;
	bres.incx = ft_sign(bres.dx);
	bres.incy = ft_sign(bres.dy);
	bres.dx = ft_abs(bres.dx);
	bres.dy = ft_abs(bres.dy);
	if (bres.dx == 0)
		draw_vertical_wall(line, &bres, cub, rays);
	else
		printf("\nERROR\n");
	// if (bres.dy == 0)
	// 	draw_horizontal(line, &bres, cub, rays);
	// else if (bres.dx >= bres.dy)
	// 	draw_more_horizontal(cub, rays, &bres, line);
	// else
	// 	draw_more_vertical(cub, rays, &bres, line);
	return (0);
}