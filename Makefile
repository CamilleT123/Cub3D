# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctruchot <ctruchot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:07:39 by ctruchot          #+#    #+#              #
#    Updated: 2024/05/30 18:57:09 by ctruchot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3D
SRC		= main.c \
			draw.c \
			draw_map_back.c \
			draw_lines.c \
			draw_walls.c \
			rays.c \
			rays2.c \
			utils.c \

CC		= cc
CFLAGS = -Wall -Werror -Wextra -g3
# includes = 

OBJ		= $(SRC:%.c=%.o)
# DEP		= 
# DEP 	= $(OBJ:.o=.d)

all: makelib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@
#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lz -o $(NAME) 
# $(DEP)

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

makelib:
	make -C mlx

clean:
	rm -f $(OBJ)
	make clean -C mlx


fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) makelib
	$(MAKE) $(NAME)

.PHONY: clean all fclean re all so

