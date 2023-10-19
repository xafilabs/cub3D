/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:06:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/18 15:40:13 by lclerc           ###   ########.fr       */
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
# include <math.h>
# include <stdio.h>
# include <limits.h>

// Include user headers
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "utils.h"
# include "file_validation.h"
# include "map_validation.h"

// Type definitions
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		fov;
	double	half_fov;
}	t_player;

typedef struct s_screen
{
	int		width;
	int		height;
	double	half_width;
	double	half_height;
	int		refresh_rate;
}	t_screen;

typedef struct s_raycast
{
	double	increment_angle;
	int		precision;
}	t_raycast;

// color is stored in rgba format encoded into an int
// int get_rgba(int r, int g, int b, int a) can be used for encoding
// int get_r(int rgba) for decoding a single channel, r in this case
typedef struct s_color_data
{
	int	floor;
	int	ceiling;
}	t_color_data;

typedef struct s_texture_data
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
}	t_texture_data;

typedef struct s_map
{
	int	width;
	int	height;
	int	**content;
}	t_map;

typedef struct s_data
{
	t_player		player;
	t_screen		screen;
	t_raycast		raycast;
	t_color_data	color;
	t_texture_data	texture;
	t_map			map;
}	t_data;

// Function declarations
void			initialize_struct(t_file_data *structure_pointer);
void			print_error_message(t_return_value error);
t_return_value	check_file_type(t_file_data *data, const char **path_to_file);
t_return_value	get_file_content_to_string(t_file_data *data, const char **path);
void			clean_up(t_file_data *data);
t_return_value	validate_scene_requirement(t_file_data *data);

// to be deleted
void			print_struct(t_file_data *data);
void			print_elements(t_file_data *data); 
#endif
