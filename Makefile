# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 12:29:55 by ctruchot          #+#    #+#              #
#    Updated: 2024/06/27 15:45:39 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------ NAME -------------#
NAME		= cub3D

CC 			= cc

#------------ SOURCE MANDATORY -------------#
SRC			= $(addprefix ./src/, main.c moving.c fps.c ending.c			\
			  changing_direction.c)

INIT		= $(addprefix ./src/init/, init_cub.c exit.c utils.c			\
			  init_scene.c edit_scene.c char_condition.c check_map.c init_map.c)

GNL			= $(addprefix ./gnl/, get_next_line.c get_next_line_utils.c)

RAYT		= $(addprefix ./src/raycasting/, rays.c rays2.c)

FPS			= $(addprefix ./src/FPS_view/, draw_lines.c draw_walls.c		\
			  draw_view.c utils.c draw_textures.c)

C_FILES		= $(SRC) $(GNL) $(INIT) $(RAYT) $(FPS)

#------------ SOURCE BONUS -------------#
BSRC			= $(addprefix ./src_bonus/, main.c moving.c fps.c ending.c			\
			  changing_direction.c)

BINIT		= $(addprefix ./src_bonus/init/, init_cub.c exit.c utils.c			\
			  init_scene.c edit_scene.c char_condition.c check_map.c init_map.c)

GNL			= $(addprefix ./gnl/, get_next_line.c get_next_line_utils.c)

BRAYT		= $(addprefix ./src_bonus/raycasting/, rays.c rays2.c)

BFPS			= $(addprefix ./src_bonus/FPS_view/, draw_lines.c draw_walls.c		\
			  draw_view.c utils.c draw_textures.c)

BMINIMAP		= $(addprefix ./src_bonus/minimap/, draw_minimap.c draw_fullmap.c		\
			  draw_player.c)

B_FILES		= $(BSRC) $(GNL) $(BINIT) $(BRAYT) $(BFPS) $(BMINIMAP)

#------------ FLAGS + INCLUDE -------------#
CFLAGS		= -Wextra -Wall -Werror -g

# HEADERS		=  -I./include
HEADERS		= -Imlx -I./include

LIBRARIES	= -Lmlx -lmlx -L./libft -lft -lXext -lX11 -lm -lz
# LIBRARIES	= -L./libft -lft

#------------ COMPILING -------------#
OBJ			:= $(C_FILES:.c=.o)

OBJ_BONUS	:= $(B_FILES:.c=.o)

all			: $(NAME)

$(NAME)		: $(OBJ)
	make -C mlx
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIBRARIES) -o $@

%.o			: %.c
	$(CC) $(CFLAGS) $(HEADERS) -O3 -c $< -o $@

bonus		: $(OBJ_BONUS)
	make -C mlx
	make -C libft
	$(CC) $(BFLAGS) $^ $(LIBRARIES) -o cub3D

clean		:
	rm -f $(OBJ) $(GNL_OBJ) $(OBJ_BONUS)
	make clean -C mlx
	make clean -C libft

fclean		: clean
	rm -f $(NAME)
	make clean -C mlx
	make fclean -C libft
	
re			: fclean all

.PHONY		: all clean fclean re
