/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:24:10 by aduvilla          #+#    #+#             */
/*   Updated: 2024/06/05 11:31:13 by aduvilla         ###   ########.fr       */
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

# define NB_ELEMENT 6

/*------------ STRUCT -------------*/
typedef struct s_scene

{
	char 		**map;
	float		start_x;
	float		start_y;
	int			f_color;
	int			c_color;
	void		*east;
	void		*west;
	void		*north;
	void		*south;
}			t_scene;


/*------------ UTILS -------------*/
char	*get_all_lines(char *ber);
int		map_error(char *s1, char *s2, int status);

#endif
