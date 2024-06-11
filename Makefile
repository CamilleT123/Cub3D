#------------ NAME -------------#
NAME		= cub3d

CC 			= cc

#------------ SOURCE -------------#
SRC			= $(addprefix ./src/, )

INIT		= $(addprefix ./init/, init_cub.c exit.c utils.c init_scene.c	\
			  edit_scene.c char_condition.c check_map.c main.c)

GNL			= $(addprefix ./gnl/, get_next_line.c get_next_line_utils.c)

C_FILES		= $(SRC) $(GNL) $(INIT)

#------------ FLAGS + INCLUDE -------------#
CFLAGS		= -Wextra -Wall -Werror -g

HEADERS		=  -I./include
#HEADERS		= -Imlx -I./include

#LIBRARIES	= -Lmlx -lmlx -L./libft -lft -lXext -lX11 -lm -lz
LIBRARIES	= -L./libft -lft

#------------ COMPILING -------------#
OBJ			:= $(C_FILES:.c=.o)

all			: $(NAME)

$(NAME)		: $(OBJ)
#	make -C mlx
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIBRARIES) -o $@

%.o			: %.c
	$(CC) $(CFLAGS) $(HEADERS) -O3 -c $< -o $@

clean		:
	rm -f $(OBJ) $(GNL_OBJ)
#	make clean -C mlx
	make clean -C libft

fclean		: clean
	rm -f $(NAME)
#	make clean -C mlx
	make fclean -C libft
	
re			: fclean all

.PHONY		: all clean fclean re
