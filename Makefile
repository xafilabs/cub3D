# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:25:10 by malaakso          #+#    #+#              #
#    Updated: 2023/09/28 15:18:58 by malaakso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
LIBFT			=	libft.a
MINILIBX		=	build/libmlx42.a
COMPILER		=	cc

H_FOLDER		=	includes
C_FOLDER		=	src
OBJ_FOLDER		=	obj
LIBFT_FOLDER	=	libft
MINILIBX_FOLDER	=	MLX42
FOLDER_LIST		=	$(H_FOLDER) $(C_FOLDER) $(OBJ_FOLDER) \
					$(LIBFT_FOLDER) $(MINILIBX_FOLDER)

H_FILES			=	fdf.h
C_FILES			=	fdf.c read_file.c check_file.c cleaner.c \
					draw.c draw_modifiers.c offset.c image.c

H_PATHS			=	$(addprefix $(H_FOLDER)/, $(H_FILES))
C_PATHS			=	$(addprefix $(C_FOLDER)/, $(C_FILES))
OBJ_PATHS		=	$(addprefix $(OBJ_FOLDER)/, \
					$(patsubst %.c, %.o, $(C_FILES)))

C_FLAGS_OBJ		=	-Wall -Wextra -Werror
C_FLAGS_NAME	=	$(C_FLAGS_OBJ) -lm -framework Cocoa -framework OpenGL -framework IOKit

.PHONY: all
all: $(NAME)

$(NAME): $(FOLDER_LIST) $(OBJ_PATHS) Makefile \
	$(LIBFT_FOLDER)/$(LIBFT) $(MINILIBX_FOLDER)/$(MINILIBX)
	$(COMPILER) $(C_FLAGS_NAME) $(OBJ_PATHS) $(LIBFT_FOLDER)/$(LIBFT) \
		$(MINILIBX_FOLDER)/$(MINILIBX) -o $@

$(OBJ_PATHS): $(OBJ_FOLDER)/%.o:$(C_FOLDER)/%.c $(H_PATHS) Makefile
	$(COMPILER) $(C_FLAGS_OBJ) -I $(H_FOLDER) -I $(LIBFT_FOLDER) \
		-I $(MINILIBX_FOLDER) -c $< -o $@

$(LIBFT_FOLDER)/$(LIBFT):
	$(MAKE) -C $(LIBFT_FOLDER)

$(MINILIBX_FOLDER)/$(MINILIBX):
	$(MAKE) -C $(MINILIBX_FOLDER)

$(FOLDER_LIST):
	mkdir $@

.PHONY: clean
clean:
	rm -f $(OBJ_PATHS)
	rm -rf $(OBJ_FOLDER)
	$(MAKE) fclean -C $(LIBFT_FOLDER)
	$(MAKE) clean -C $(MINILIBX_FOLDER)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all