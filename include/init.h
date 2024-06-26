/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:24:10 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/19 15:27:04 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <fcntl.h>

/*------------ MACROS -------------*/
# define IS_DIR ": is a directory"
# define MALLOC " cannot allocate memory"
# define NO_FILE ": no path to texture"
# define TM_FILE ": too many paths to texture"
# define TM_ELEMENT ": element defined two times"
# define TF_ELEMENT "not enough scene elements"
# define LINES "the map don't accept empty lines"
# define BIG_NUM ": is a too big number (max 255,255,255)"
# define INVALID_NUM ": is not a valid color number (0 to 255)"
# define TM_NUM "wrong color format (R,G,B): too many colors"
# define TF_NUM "wrong color format: (R,G,B) not enough colors"
# define FORBIDDEN_CHAR "wrong map format (check accepted char !!)"
# define NO_START "no start position on the map"
# define WALLS "map is not surrounded by walls"
# define TOO_SMALL "the map is too small"
# define TM_START "too many starting position"
# define VALID_COORD ": is not a valid scene element (NO,SO,EA,WE,C,F)"

# define NB_ELEMENT 6

/*------------ STRUCT -------------*/
typedef struct s_scene
{
	char		**map;
	float		start_x;
	float		start_y;
	float		start_angle;
	int			f_color;
	int			c_color;
	char		*east;
	char		*west;
	char		*north;
	char		*south;
}			t_scene;

/*------------ EDIT -------------*/
int		edit_wall(char **path, char *info);
int		edit_back(int *color, char *info);
int		only_goodchar(t_scene *scene);
int		check_walls(char **map);

/*------------ CHAR-COND -------------*/
int		is_mapchar(char c);
int		is_startchar(char c);
int		cub_isspace(char c);

/*------------ UTILS -------------*/
int		check_file(char *file, char *ext);
int		check_extension(char *file, char *ext);
char	**tab_dup(char **tab);
char	*get_all_lines(char *ber);
char	*get_path(char *str, int skip);
int		map_error(char *s1, char *s2, int status);
int		map_ext_error(char *s1, char *s2, int status);

#endif
