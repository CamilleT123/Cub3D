/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:08:43 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/18 14:39:40 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include "../textures/text4.ppm"
// #include "../textures/text128.ppm"

static int	get_color_texture(t_texture *texture, int texture_y,
		int texture_index_x)
{
	int	color = 0;
	int	index;
	int	y_offset;

	y_offset = texture_y * texture->line_length;
	index = y_offset + (texture_index_x * (texture->bits_per_pixel / 8));
	if (index < 16500 && index >= 0) // revoir limite
	{
		printf("ty=%d\n", texture_y);
		printf("tx=%d\n", texture_index_x);
		printf("index=%d\n", index);
		color = *(unsigned int *)(texture->addr + index);
		printf("color=%d\n", color);
	}
	// else
	// 	color = BLACK;
	return (color);
}

// static void	ft_draw_walls(t_cub *cub, t_line *line)
// {
// 	line->x1 = line->nb_pixel;
// 	line->y1 = line->wall_offset;
// 	line->texture_y = line->y_offset * line->step_y;
// 	line->texture_x = cub->wall->index_texture_x;
// 	line->y = 0;
// 	while (line->y < line->wall_height)
// 	{
// 		line->color = get_color_texture(texture, line->texture_y,
// 				line->texture_x);
// 		my_mlx_pixel_put(cub, line->start_x, line->start_y + line->y, line->color);
// 		(t_cub *cub, int x, int y, int color)
// 		line->texture_y += line->step_y;
// 		line->y++;
// 	}
// }
int	draw_vertical_walls(t_line *line, t_bres *bres, t_cub *cub, t_rays *rays)
{
	int	y;
	// int pixel;
	// int red;
	// int green;
	// int blue;
	
	// char    *pixel;
	// pixel = NULL;

	// line->x1 = line->nb_pixel;
	// line->y1 = line->wall_offset;
	// line->ty = line->y_offset * line->step_y;
	// line->texture_x = cub->wall->index_texture_x;
    line->ty = line->ty_off * line->ty_step; // ty = texture y / ty_step = 32/lineh / on ajoute le step a chaque loop
	// ty_off = offset = libeh - 320 / 2
	if (rays->disth < rays->distv) // si mur horizontal
	{
		// line->tx = (int)(rays->rx / 2.0) % 128;
		line->tx = (int)(rays->rx) % 128;
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
	// if (rays->wall == 1 || rays->wall == 3)
		// line->ty +=32;
	y = line->y1; // y = y du point 1
	while (y < line->lineh)
	{
		line->color = get_color_texture(bres->ptr_texture, line->ty,
				line->tx);
		my_mlx_pixel_put(cub, line->x1, y, line->color);
		// (t_cub *cub, int x, int y, int color)
		y++;
		line->ty += line->ty_step;
	}
	
	printf("tx=%f\n", line->tx);

	while (y != line->y2 + bres->incy) // tant qu'on n'atteind pas le y du point 2
	{
		line->color = get_color_texture(bres->ptr_texture, line->ty,
				line->ty);
		// printf("ty=%f\n", line->ty);
		// printf("tx=%f\n", line->tx);
		// printf("color=%d\n", line->color);
		// pixel = line->ty * bres->ptr_texture->line_length / 4 + line->tx;
		// printf("ty=%f\n", line->ty);

		// pixel =  line->tx * 4 + 4 * bres->ptr_texture->line_length * line->ty;
		// printf("pixel=%d\n", pixel);
		// printf("text=%d\n", bres->ptr_texture->addr[pixel]);


		// rays->color = bres->ptr_texture->addr[pixel];
		// printf("color=%d\n", rays->color);
		my_mlx_pixel_put(cub, line->x1, y, rays->color); // on imprime le pixel en x1 (ligne verticale x ne bouge pas) et y qui bouge
		// y += bres->incy;
		y++;
		line->ty += line->ty_step; // on deplace le curseur de texture
	}
	return (0);
}

// void	img_pix_put(t_texture *texture, int x, int y, int color)
// {
//     char    *pixel;

//     pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
//     *(int *)pixel = color;
// }

int get_adresses(t_cub *cub, t_texture *texture)
{
	texture->addr = (int *)mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	(void)cub;
	return (0);
}

int get_texture(t_cub *cub, t_texture *texture)
{
	int	img_width = 0;
	int	img_height = 0;
	texture->img = mlx_xpm_file_to_image(cub->mlx, "./Brick64.xpm",
			&img_width, &img_height);
	return (0);
}

int	draw_line_walls(t_cub *cub, t_rays *rays, t_line *line)
{
	t_bres	bres;
	t_texture	texture;

	get_texture(cub, &texture);
	get_adresses(cub, &texture);
	bres.dx = line->x2 - line->x1;
	bres.dy = line->y2 - line->y1;
	bres.incx = ft_sign(bres.dx);
	bres.incy = ft_sign(bres.dy);
	bres.dx = ft_abs(bres.dx);
	bres.dy = ft_abs(bres.dy);
	bres.ptr_texture = &texture;	
	if (bres.dx == 0)
		draw_vertical_walls(line, &bres, cub, rays);
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
