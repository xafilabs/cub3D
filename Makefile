# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:25:10 by malaakso          #+#    #+#              #
#    Updated: 2023/10/10 19:37:36 by malaakso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
LIBFT			=	libft.a
MINILIBX		=	libmlx42.a
COMPILER		=	cc

H_FOLDER		=	inc
C_FOLDER		=	src
OBJ_FOLDER		=	obj
LIBFT_FOLDER	=	libft
MINILIBX_FOLDER	=	MLX42
MINILIBX_SUBFOL	=	build
FOLDER_LIST		=	$(H_FOLDER) $(C_FOLDER) $(OBJ_FOLDER) \
					$(LIBFT_FOLDER) $(MINILIBX_FOLDER)

H_FILES			=	main.h
C_FILES			=	main.c

H_PATHS			=	$(addprefix $(H_FOLDER)/, $(H_FILES))
C_PATHS			=	$(addprefix $(C_FOLDER)/, $(C_FILES))
OBJ_PATHS		=	$(addprefix $(OBJ_FOLDER)/, \
					$(patsubst %.c, %.o, $(C_FILES)))

C_FLAGS_OBJ		=	-Wall -Wextra -Werror
C_FLAGS_MLX42	=	-framework Cocoa -framework OpenGL -framework IOKit \
					-lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
C_FLAGS_NAME	=	$(C_FLAGS_OBJ) $(C_FLAGS_MLX42) -lm

.PHONY: all
all: $(NAME)

$(NAME): $(FOLDER_LIST) $(OBJ_PATHS) Makefile \
	$(LIBFT_FOLDER)/$(LIBFT) $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX)
	@$(COMPILER) $(C_FLAGS_NAME) $(OBJ_PATHS) $(LIBFT_FOLDER)/$(LIBFT) \
		$(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX) -o $@
	@echo "\033[0;95m~~* Compiled $(NAME) *~~\033[0m"

$(OBJ_PATHS): $(OBJ_FOLDER)/%.o:$(C_FOLDER)/%.c $(H_PATHS) Makefile
	@$(COMPILER) $(C_FLAGS_OBJ) -I $(H_FOLDER) -I $(LIBFT_FOLDER) \
		-I $(MINILIBX_FOLDER) -c $< -o $@
	@echo "\033[0;95m~~* Created object files *~~\033[0m"

$(LIBFT_FOLDER)/$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_FOLDER)
	@echo "\033[0;95m~~* Built libft *~~\033[0m"

$(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX):
	@cmake --log-level=ERROR $(MINILIBX_FOLDER) -B $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@echo "\033[0;95m~~* libmlx42 build files were created *~~\033[0m"
	@cmake --build $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL) -j4 -- -s
	@echo "\033[0;95m~~* Built libmlx42 *~~\033[0m"

$(FOLDER_LIST):
	@mkdir $@
	@echo "\033[0;95m~~* Created missing folders *~~\033[0m"

.PHONY: clean
clean:
	@rm -f $(OBJ_PATHS)
	@echo "\033[0;95m~~* Removed .obj files *~~\033[0m"
	@rm -rf $(OBJ_FOLDER)
	@echo "\033[0;95m~~* Removed obj folder *~~\033[0m"
	@$(MAKE) -s clean -C $(LIBFT_FOLDER)
	@echo "\033[0;95m~~* Cleaned libft *~~\033[0m"
	@mv -f $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX) \
	$(MINILIBX_FOLDER)/$(MINILIBX)
	@rm -rf $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@mkdir -p $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@mv -f $(MINILIBX_FOLDER)/$(MINILIBX) \
	$(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX)
	@echo "\033[0;95m~~* Cleaned libmlx42 *~~\033[0m"

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;95m~~* Removed $(NAME) *~~\033[0m"
	@$(MAKE) -s fclean -C $(LIBFT_FOLDER)
	@echo "\033[0;95m~~* Cleaned libft (removed libft.a) *~~\033[0m"
	@rm -rf $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@echo "\033[0;95m~~* Cleaned libmlx42 (removed libmlx42.a) *~~\033[0m"

.PHONY: re
re: fclean all