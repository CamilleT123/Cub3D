/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:24:59 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/19 17:11:27 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "cubstruct.h"
# include "cubsetup.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/*------------ MACROS -------------*/
# define PI 3.1415926535
# define DR 0.0174533

/*------------ ENUM -------------*/
typedef enum s_walls
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}			t_walls;

typedef enum s_tile
{
	FLOOR,
	WALL,
	HOLE
}		t_tile;

/*------------ PARSING/INIT -------------*/
int		init_cub(char *map, t_cub *cub);
int		init_scene(t_cub *cub, char **ar_scene);
int		init_map(t_cub *cub);
int		exit_map(t_cub *cub, int status);
int		init_textures(t_cub *cub);

// main.c
int		close_win(t_cub *cub);

// moving.c
void	changing_direction(int key, t_cub *cub);
int		keymapping(int key, t_cub *cub);

// draw.c
int		display(t_cub *minimap);
int		draw_player(t_cub *minimap, float x, float y);

// draw_visual.c
int		display(t_cub *cub);

// cub/draw_minimap.c
int		display_back(t_cub *cub);
int		draw_map(t_cub *cub);

// cub/draw_player.c
int		draw_player(t_cub *cub, float x, float y);
int		draw_square(t_cub *cub, float x, float y);

// rays.c
int		rays_init(t_cub *cub, t_rays *rays);
int		calculate_rays(t_cub *cub, t_rays *rays);
int		draw_rays(t_cub *cub, t_rays *rays, t_line *line);
int		check_horizontal_lines(t_cub *cub, t_rays *rays);
int		init_each_ray(t_cub *cub, t_rays *rays);

// rays2.c
int		check_vertical_lines(t_cub *cub, t_rays *rays);
int		compare_distances(t_rays *rays);

// draw_lines
int		draw_line(t_cub *cub, t_rays *rays, t_line *line);

// draw_walls.c
int		draw_walls(t_cub *cub, t_rays *rays);
int		init_line(t_cub *cub, t_rays *rays, t_line *line);
int		draw_line_walls(t_cub *cub, t_rays *rays, t_line *line);

// utils.c
int		ft_abs(int n);
int		ft_sign(int n);
float	distance(float x1, float y1, float x2, float y2);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

#endif
