# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 12:29:55 by ctruchot          #+#    #+#              #
#    Updated: 2024/06/17 11:57:20 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------ NAME -------------#
NAME		= cub3d

CC 			= cc

#------------ SOURCE -------------#
# SRC			= $(addprefix ./src/, )

INIT		= $(addprefix ./init/, init_cub.c exit.c utils.c init_scene.c	\
			  edit_scene.c char_condition.c check_map.c)

# GNL			= $(addprefix ./gnl/, get_next_line.c get_next_line_utils.c)

RAYT		= $(addprefix ./raycasting/, rays.c rays2.c)
FPS			= $(addprefix ./FPS_view/, draw_lines.c draw_walls.c draw_view.c utils.c)
MINIMAP		= $(addprefix ./minimap/, draw_minimap.c draw_player.c)
TEXTURES	= $(addprefix ./textures/, draw_textures.c)

# SRC		= main.c \
# 			draw.c \
# 			draw_map_back.c \
# 			draw_lines.c \
# 			draw_walls.c \
# 			rays.c \
# 			rays2.c \
# 			utils.c \

C_FILES		= $(RAYT) $(FPS) $(MINIMAP) $(TEXTURES) main.c moving.c
# C_FILES		= $(SRC) $(GNL) $(INIT) main.c
# C_FILES		= $(SRC)

#------------ FLAGS + INCLUDE -------------#
CFLAGS		= -Wextra -Wall -Werror -g

# HEADERS		=  -I./include
HEADERS		= -Imlx -I./include

LIBRARIES	= -Lmlx -lmlx -L./libft -lft -lXext -lX11 -lm -lz
# LIBRARIES	= -L./libft -lft

#------------ COMPILING -------------#
OBJ			:= $(C_FILES:.c=.o)

all			: $(NAME)

$(NAME)		: $(OBJ)
	make -C mlx
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIBRARIES) -o $@

%.o			: %.c
	$(CC) $(CFLAGS) $(HEADERS) -O3 -c $< -o $@

clean		:
	rm -f $(OBJ) $(GNL_OBJ)
	make clean -C mlx
	make clean -C libft

fclean		: clean
	rm -f $(NAME)
	make clean -C mlx
	make fclean -C libft
	
re			: fclean all

.PHONY		: all clean fclean re
