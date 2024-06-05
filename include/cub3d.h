/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:24:59 by ctruchot          #+#    #+#             */
/*   Updated: 2024/06/05 17:54:29 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "init.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/*------------ MACROS -------------*/
# define PI 3.1415926535
# define DR 0.0174533 // 1 degree in radian

/*------------ STRUCT -------------*/
typedef struct s_cub
{
	void	*mlx;
	void	*win;
	t_scene	*scene;
	int		xmap;
	int		ymap;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	int		mapx;
	int		mapy;
	int		map[64];
	int		mapsize;
}			t_cub;
// ry et rx sont les coordonnées du point d'intersection
// yo et xo sont les valeurs d'incrémentation pour les coordonnées x et y
// mx et my sont les coordonnées de la carte, mp est l'index de la carte
// dof = depth of field meaning how far the ray can go

typedef struct s_rays
{
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	disth;
	float	distv;
	float	distt;
	float	xstep;
	float	ystep;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		color;
	float	atan;
	float	ntan;
}			t_rays;

typedef struct s_line
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
}			t_line;

typedef struct s_bres
{
	int		dx;
	int		dy;
	int		incx;
	int		incy;
	int		x2;
	int		y2;
}			t_bres;

int	init_cub(char *map, t_cub *cub);
int	close_win(t_cub *cub);

// moving.c
void	changing_direction(int key, t_cub *cub);
int	keymapping(int key, t_cub *cub);

// draw_visual.c
int			display(t_cub *cub);

// cub/draw_minimap.c
int	display_back(t_cub *cub);
int	draw_map(t_cub *cub);

// cub/draw_player.c
int			draw_player(t_cub *cub, float x, float y);
int	draw_square(t_cub *cub, float x, float y);

// rays.c
int			draw_rays(t_cub *cub);

// rays2.c
int			check_vertical_lines(t_cub *cub, t_rays *rays);
int			compare_distances(t_rays *rays);

// draw_lines
int			draw_line(t_cub *cub, t_rays *rays, t_line *line);

// draw_walls.c
int			draw_walls(t_cub *cub, t_rays *rays, int r);
int			init_line(t_cub *cub, t_rays *rays, t_line *line);

// utils.c
int			ft_abs(int n);
int			ft_sign(int n);
float		distance(float x1, float y1, float x2, float y2);
void		my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

#endif
