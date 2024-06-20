/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:24:59 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/20 20:22:19 by ctruchot         ###   ########.fr       */
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

/*------------ CLOSING -------------*/
int		close_win(t_cub *cub);

/*------------ MOVING -------------*/
void	changing_direction(int key, t_cub *cub);
int		keymapping(int key, t_cub *cub);
int		moving_straight(int key, t_cub *cub, t_collision *collision);
int		moving_side(int key, t_cub *cub, t_collision *collision);

/*------------ DRAWING FPS VIEW -------------*/
int		display(t_cub *cub);
int		draw_line(t_cub *cub, t_rays *rays, t_line *line);
int		draw_walls(t_cub *cub, t_rays *rays);
int		init_line(t_cub *cub, t_rays *rays, t_line *line);
int		bresenham_walls(t_cub *cub, t_rays *rays, t_line *line);

/*------------ RAYCASTING -------------*/
int		rays_init(t_cub *cub, t_rays *rays);
int		calculate_rays(t_cub *cub, t_rays *rays);
int		draw_rays(t_cub *cub, t_rays *rays, t_line *line);
int		check_horizontal_lines(t_cub *cub, t_rays *rays);
int		init_each_ray(t_cub *cub, t_rays *rays);
int		check_vertical_lines(t_cub *cub, t_rays *rays);
int		compare_distances(t_rays *rays);

/*------------ DRAWING MINIMAP -------------*/
int		display_back(t_cub *cub);
int		draw_map(t_cub *cub);
int		draw_minimap(t_cub *cub);
int		draw_player(t_cub *cub, float x, float y);
int		draw_square(t_cub *cub, float x, float y);

int		rays_init_mini(t_cub *cub, t_rays *rays);
int		calculate_rays_mini(t_cub *cub, t_rays *rays);
int		draw_rays_mini(t_cub *cub, t_rays *rays, t_line *line);
int		check_horizontal_lines_mini(t_cub *cub, t_rays *rays);
int		init_each_ray_mini(t_cub *cub, t_rays *rays);

int		check_vertical_lines_mini(t_cub *cub, t_rays *rays);
int		compare_distances_mini(t_rays *rays);

/*------------ UTILS -------------*/

int		ft_abs(int n);
int		ft_sign(int n);
float	distance(float x1, float y1, float x2, float y2);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

#endif
