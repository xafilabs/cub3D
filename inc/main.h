/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:06:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/11 18:34:48 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// Preprocessor definitions
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 720
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 480
# endif

// Include system headers
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

// DEBUG headers
# include <stdio.h>

// Include user headers
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "utils.h"
# include "file_validation.h"
# include "map_validation.h"

// Function declarations
void			initialize_struct(t_file_data *structure_pointer);
void			print_error_message(t_return_value error);
t_return_value	check_file_type(t_file_data *data, const char **path_to_file);
t_return_value	get_file_content_to_string(t_file_data *data, const char **path);
void			clean_up(t_file_data *data);
t_return_value	validate_scene_requirement(t_file_data *data);

#endif