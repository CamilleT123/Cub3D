/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubstruct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:56:52 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/27 16:53:52 by ctruchot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBSTRUCT_H
# define CUBSTRUCT_H

# include "init.h"

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}			t_texture;

typedef struct s_minimap
{
	int	xmin;
	int	ymin;
	int	xmax;
	int	ymax;
	int	y;
	int	x;
}			t_minimap;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_scene		scene;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	float		player_x;
	float		player_y;
	float		player_xmini;
	float		player_ymini;
	float		pdx;
	float		pdy;
	float		player_angle;
	int			f_color;
	int			c_color;
	int			mapx;
	int			mapy;
	int			mapsize;
	int			mapmax;
	int			*map;
	time_t		t_update;
	int			minimapx;
	int			minimapy;
	int			unitpc;
	int			ppc;
	int			oldx;
	t_texture	**texture;
}			t_cub;

// ry et rx sont les coordonnées du point d'intersection
// yo et xo sont les valeurs d'incrémentation pour les coordonnées x et y
// mx et my sont les coordonnées de la carte, mp est l'index de la carte
// dof = depth of field meaning how far the ray can go

typedef struct s_rays
{
	int		r;
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
	int		mpv;
	int		mph;
	int		dof;
	int		color;
	float	atan;
	float	ntan;
	int		wall;
	int		nb_rays;
}			t_rays;

typedef struct s_line
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	float	line_height;
	float	ty_step;
	float	ty_off;
	float	ty;
	float	tx;
	int		color;
}			t_line;

typedef struct s_bres
{
	int			dx;
	int			dy;
	int			incx;
	int			incy;
	int			x2;
	int			y2;
	t_texture	*ptr_texture;
}			t_bres;

/*
xo offset = la boule de securite
ipx player's position on the grid
ipx_add_xo player's position - the offset
*/
typedef struct s_collision
{
	int	xo;
	int	yo;
	int	ipx;
	int	ipy;
	int	ax;
	int	ay;
	int	sx;
	int	sy;
}		t_collision;

#endif
