/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:24:10 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/06 08:56:53 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <fcntl.h>
# include "get_next_line.h"

/*------------ MACROS -------------*/
# define IS_DIR ": is a directory"
# define EXTENSION ": is not .cub extension"
# define MALLOC " cannot allocate memory"
# define NO_FILE ": no path to xpm"
# define TM_FILE ": too many paths to xpm"
# define TM_ELEMENT ": wall defined two times"
# define TF_ELEMENT ": too few elements"
# define LINES "the map don't accept empty lines"
# define BIG_NUM ": is a too big number (max 255,255,255)"
# define INVALID_NUM ": is an invalid number"
# define TM_NUM ": too many numbers"
# define TF_NUM ": too few numbers"
# define FORBIDDEN_CHAR "wrong map format (check accepted char !!)"
# define NO_START "no start position on the map"
# define WALLS "map is not surrounded by walls"
# define TOO_SMALL "the map is too small"

# define NB_ELEMENT 6

/*------------ STRUCT -------------*/
typedef struct s_scene

{
	char 		**map;
	float		start_x;
	float		start_y;
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

int		check_walls(char **map);
int		is_mapchar(char c);
/*------------ UTILS -------------*/
char	**tab_dup(char **tab);
int		cub_isspace(char c);
char	*get_all_lines(char *ber);
char	*get_path(char *str, int skip);
int		map_error(char *s1, char *s2, int status);

#endif
