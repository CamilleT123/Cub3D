/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:24:59 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/27 17:59:16 by ctruchot         ###   ########.fr       */
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
# include <sys/time.h>

/*------------ ENUM -------------*/
typedef enum s_walls
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	WDOOR
}			t_walls;

typedef enum s_tile
{
	FLOOR,
	WALL,
	HOLE,
	DOOR,
	ODOOR
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
void	changing_direction_mouse(int x, t_cub *cub);
int		keymapping(int key, t_cub *cub);
int		moving_straight(int key, t_cub *cub, t_collision *collision);
int		moving_side(int key, t_cub *cub, t_collision *collision);

/*------------ DRAWING FPS VIEW -------------*/
int		display(t_cub *cub);
int		draw_line(t_cub *cub, t_rays *rays, t_line *line);
int		draw_walls(t_cub *cub, t_rays *rays);
int		init_line(t_cub *cub, t_rays *rays, t_line *line);
void	vertical_wall(t_line *line, t_cub *cub, t_rays *rays);

/*------------ RAYCASTING -------------*/
int		calculate_rays(t_cub *cub, t_rays *rays);
int		draw_rays(t_cub *cub, t_rays *rays, t_line *line);
int		check_vertical_lines(t_cub *cub, t_rays *rays);
int		compare_distances(t_cub *cub, t_rays *rays);

/*------------ DRAWING MINIMAP -------------*/
int		draw_minimap(t_cub *cub);
int		draw_full_map(t_cub *cub);
int		draw_player(t_cub *cub, float x, float y);

/*------------ UTILS -------------*/
time_t	get_time(void);
int		ft_abs(int n);
int		ft_sign(int n);
float	distance(float x1, float y1, float x2, float y2);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

#endif
