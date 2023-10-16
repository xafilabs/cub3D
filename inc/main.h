/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:06:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/16 17:49:44 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// Preprocessor definitions
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 720
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 480
# endif
# ifndef MINIMAP_WIDTH
#  define MINIMAP_WIDTH 160
# endif
# ifndef MINIMAP_HEIGHT
#  define MINIMAP_HEIGHT 120
# endif
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TRUE 1
# define FALSE 0
# define COLOR_BLACK 0x000000FF
# define COLOR_WHITE 0xFFFFFFFF
# define COLOR_GREEN 0x90FD90FF
# define COLOR_RED 0xCC3636FF
# define COLOR_PINK 0xE97FC2FF
# define COLOR_BLUE 0x35CFE4FF
# define COLOR_GRAY 0x5F574FFF

// Include system headers
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <limits.h>
# include <assert.h>

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
	mlx_t			*mlx;
	mlx_image_t		*img;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// Function declarations
void			initialize_struct(t_file_data *structure_pointer);
void			print_error_message(t_return_value error);
t_return_value	check_file_type(t_file_data *data, const char **path_to_file);
t_return_value	get_file_content_to_string(t_file_data *data, const char **path);
void			clean_up(t_file_data *data);
t_return_value	validate_scene_requirement(t_file_data *data);
void			game(t_data *d);
void			loop_hook(void *data_param);
void			close_hook(void *data_param);
void			key_hook(mlx_key_data_t keydata, void *data_param);
void			draw_line(mlx_image_t *image, t_point start, t_point end, int color);
t_point			new_point(int x, int y);
void			clean_exit(t_data *d);

#endif
