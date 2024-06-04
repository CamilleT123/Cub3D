/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:24:59 by ctruchot          #+#    #+#             */
/*   Updated: 2024/05/30 18:56:40 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.1415926535
# define DR 0.0174533 // 1 degree in radian

typedef struct s_minimap
{
	void	*mlx;
	void	*win;
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
}			t_minimap;
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

// draw.c
int			display(t_minimap *minimap);
int			draw_player(t_minimap *minimap, float x, float y);

// draw_map_back.c
int	display_back(t_minimap *minimap);
int	display_back2(t_minimap *minimap);
int	draw_map(t_minimap *minimap);

// rays.c
int			draw_rays(t_minimap *minimap);

// rays2.c
int			check_vertical_lines(t_minimap *minimap, t_rays *rays);
int			compare_distances(t_rays *rays);

// draw_lines
int			draw_line(t_minimap *minimap, t_rays *rays, t_line *line);

// draw_walls.c
int			draw_walls(t_minimap *minimap, t_rays *rays, int r);
int			init_line(t_minimap *minimap, t_rays *rays, t_line *line);

// utils.c
int			ft_abs(int n);
int			ft_sign(int n);
float		distance(float x1, float y1, float x2, float y2);
void		my_mlx_pixel_put(t_minimap *minimap, int x, int y, int color);

#endif