# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:25:10 by malaakso          #+#    #+#              #
#    Updated: 2023/11/02 15:11:26 by malaakso         ###   ########.fr        #
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

H_FILES			=	main.h \
					file_validation.h

C_FILES			=	main.c \
					utils.c \
					parsing_file_operations.c \
					parsing_map_elements.c \
					parsing_scene_elements.c \
					render.c \
					render_utils.c \
					mlx_hooks.c \
					raycasting_movement.c \
					migration.c \
					raycasting.c \
					raycasting_init.c \
					parsing_colors.c \
					parsing_utils.c \
					parsing_map_and_player_import.c \
					exit_utils.c

H_PATHS			=	$(addprefix $(H_FOLDER)/, $(H_FILES))
C_PATHS			=	$(addprefix $(C_FOLDER)/, $(C_FILES))
OBJ_PATHS		=	$(addprefix $(OBJ_FOLDER)/, \
					$(patsubst %.c, %.o, $(C_FILES)))

C_FLAGS_OBJ		=	-Wall -Wextra -Werror \
					-Wpedantic -Wunreachable-code -Wtype-limits \
					-Ofast

C_FLAGS_MLX42	=	-framework Cocoa -framework OpenGL -framework IOKit \
					-lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

C_FLAGS_NAME	=	$(C_FLAGS_OBJ) $(C_FLAGS_MLX42) -lm

C_FLAGS_DEBUG	=	-g -fsanitize=address,undefined

.PHONY: all
all: $(NAME)

$(NAME): $(FOLDER_LIST) $(OBJ_PATHS) Makefile \
	$(LIBFT_FOLDER)/$(LIBFT) $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX)
	@echo "\033[0;95m~~* Compiling $(NAME) *~~\033[0m"
	@$(COMPILER) $(C_FLAGS_NAME) $(OBJ_PATHS) $(LIBFT_FOLDER)/$(LIBFT) \
		$(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX) -o $@

$(OBJ_PATHS): $(OBJ_FOLDER)/%.o:$(C_FOLDER)/%.c $(H_PATHS) Makefile
	@echo "\033[0;95m~~* Creating object file $@ *~~\033[0m"
	@$(COMPILER) $(C_FLAGS_OBJ) -I $(H_FOLDER) -I $(LIBFT_FOLDER) \
		-I $(MINILIBX_FOLDER) -c $< -o $@

$(LIBFT_FOLDER)/$(LIBFT):
	@echo "\033[0;95m~~* Building libft *~~\033[0m"
	@$(MAKE) -s -C $(LIBFT_FOLDER)

$(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX):
	@echo "\033[0;95m~~* Creating libmlx42 build files *~~\033[0m"
	@cmake -DCMAKE_RULE_MESSAGES=OFF -DCMAKE_TARGET_MESSAGES=OFF \
	-DCMAKE_MESSAGE_LOG_LEVEL=ERROR -DCMAKE_INSTALL_MESSAGE=NEVER \
	$(MINILIBX_FOLDER) -B $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@echo "\033[0;95m~~* Building libmlx42 *~~\033[0m"
	@cmake --build $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL) -j4 -- -s

$(FOLDER_LIST):
	@echo "\033[0;95m~~* Creating missing folder $@ *~~\033[0m"
	@mkdir $@

.PHONY: clean
clean:
	@echo "\033[0;95m~~* Removing .obj files *~~\033[0m"
	@rm -f $(OBJ_PATHS)
	@echo "\033[0;95m~~* Removing obj folder *~~\033[0m"
	@rm -rf $(OBJ_FOLDER)
	@echo "\033[0;95m~~* Cleaning libft *~~\033[0m"
	@$(MAKE) -s clean -C $(LIBFT_FOLDER)
	@echo "\033[0;95m~~* Cleaning libmlx42 *~~\033[0m"
	@(test -s $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX) && \
	mv -f $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX) \
	$(MINILIBX_FOLDER)/$(MINILIBX)) || true
	@rm -rf $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@mkdir -p $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)
	@(test -s $(MINILIBX_FOLDER)/$(MINILIBX) && \
	mv -f $(MINILIBX_FOLDER)/$(MINILIBX) \
	$(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)/$(MINILIBX)) || true

.PHONY: fclean
fclean: clean
	@echo "\033[0;95m~~* Removing $(NAME) *~~\033[0m"
	@rm -f $(NAME)
	@echo "\033[0;95m~~* Cleaning libft (removing libft.a) *~~\033[0m"
	@$(MAKE) -s fclean -C $(LIBFT_FOLDER)
	@echo "\033[0;95m~~* Cleaning libmlx42 (removing libmlx42.a) *~~\033[0m"
	@rm -rf $(MINILIBX_FOLDER)/$(MINILIBX_SUBFOL)

.PHONY: re
re: fclean all

.PHONY: debug
debug: C_FLAGS_OBJ += $(C_FLAGS_DEBUG)
debug: debug_clean all

.PHONY: debug_clean
debug_clean: clean
	@rm -f $(NAME)

.PHONY: lldb
lldb: C_FLAGS_NAME += -g
lldb: all
