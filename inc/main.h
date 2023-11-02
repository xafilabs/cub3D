/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:06:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/11/02 17:21:03 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// Preprocessor definitions
# define WINDOW_WIDTH 720
# define WINDOW_HEIGHT 480
# define PLAYER_FOV 65
// PLAYER_MOVE_SPEED in map squares
# define PLAYER_MOVE_SPEED 0.025
// PLAYER_ROTATE_SPEED in radians
# define PLAYER_ROTATE_SPEED 0.03
# define TEXTURE_SIZE_MIN 1
# define TEXTURE_SIZE_MAX 64
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define HUGE_NUMBER 100000000
# define NEGATIVE -1
# define POSITIVE 1
# define COLOR_BLACK 0x000000FF
# define COLOR_WHITE 0xFFFFFFFF
# define COLOR_GREEN 0x90FD90FF
# define COLOR_RED 0xCC3636FF
# define COLOR_PINK 0xE97FC2FF
# define COLOR_BLUE 0x35CFE4FF
# define COLOR_GRAY 0x5F574FFF

// Include system headers
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Include user headers
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "file_validation.h"

// Type definitions
typedef enum e_program_phase
{
	PHASE_PARSING,
	PHASE_RENDERING
}					t_program_phase;

typedef struct s_dvec
{
	double			x;
	double			y;
}					t_dvec;

/**
 * @brief Contains player position information
 * @param pos position vector
 * @param dir direction vector
 * @param plane camera plane vector
 */
typedef struct s_player
{
	t_dvec			pos;
	t_dvec			dir;
	t_dvec			plane;
}					t_player;

// color is stored in rgba format encoded into an int
// int get_rgba(int r, int g, int b, int a) can be used for encoding
// int get_r(int rgba) for decoding a single channel, r in this case
typedef struct s_color_data
{
	int				floor;
	int				ceiling;
}					t_color_data;

typedef struct s_texture_data
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
}					t_texture_data;

typedef struct s_map
{
	int				width;
	int				height;
	int				**content;
}					t_map;

typedef struct s_data
{
	t_player		player;
	t_color_data	color;
	t_texture_data	texture;
	t_map			map;
	mlx_t			*mlx;
	mlx_image_t		*img;
}					t_data;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_line
{
	t_point			start;
	t_point			end;
	unsigned int	color;
}					t_line;

/**
 * @brief Represents a single cast ray
 * @param dir ray direction vector
 * @param cam_x x coordinate on the camera plane for current window x
 * coordinate
 * @param map current map square
 * @param side_dist ray length from current position to next x or y map side
 * @param delta_dist ray length from one x or y map side to the next x or y
 * @param normal_wall_distance length of the ray from the camera plane
 * to the wall point hit
 * @param step direction the ray steps in x and y direction
 * @param hit flag for the ray hitting a wall
 * @param side which side of the wall did the ray hit North/South/X
 * or East/West/Y (x hit or y hit)
 * @param line_height height of the line to draw on screen to represent the ray
 * @param draw_start y coordinate from where to start drawing
 * @param draw_end y coordinate where to stop drawing (inclusive)
 * @param wall_hit_dec the decimal value of the point where the ray
 * hit the wall
 */
typedef struct s_ray
{
	t_dvec			dir;
	double			cam_x;
	t_point			map;
	t_dvec			side_dist;
	t_dvec			delta_dist;
	double			normal_wall_distance;
	t_point			step;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_hit_dec;
	mlx_texture_t	*texture;
	t_point			tex_pos;
}					t_ray;

// Function declarations
void				initialize_struct(t_file_data *structure_pointer);
void				print_parsing_error_message(t_return_value error);
t_return_value		check_file_type(t_file_data *data,
						const char **path_to_file);
t_return_value		get_file_content_to_string(t_file_data *data,
						const char **path);
void				clean_up_parsing(t_file_data *data);
t_return_value		validate_scene_requirement(t_file_data *data);
void				render(t_data *d);
void				loop_hook(void *data_param);
void				close_hook(void *data_param);
void				key_hook(mlx_key_data_t keydata, void *data_param);
void				clean_exit(t_data *d, int exit_status);
double				deg_to_rad(double degrees);
unsigned int		get_texture_pixel(mlx_texture_t *texture, unsigned int x,
						unsigned int y);
void				init_player_dir_plane(t_data *d, int player_angle_deg,
						int fov);
unsigned int		convert_abgr_to_rgba(unsigned int agbr);
void				put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
						uint32_t color);
void				render_ceiling_floor(t_data *d);
void				update_player_location(t_data *d);
void				migrate_player_direction(t_file_data *file_data,
						t_data *render_data);
void				cast_rays(t_data *d);
void				draw_texture(t_data *d, t_ray *ray, int x);
void				init_ray_base_values(t_data *d, t_ray *ray, int x);
void				init_ray_delta(t_ray *ray);
void				init_ray_side_distance(t_data *d, t_ray *ray);
t_return_value		get_rgb_colors(t_file_data *data);
t_bool				ft_is_numerical(char *str);
void				exit_parsing(t_file_data *file_data, int return_value);
void				exit_mlx_parsing(t_file_data *file_data,
						int return_value, mlx_t *mlx);
void				free_file_data_not_map(t_file_data *data);
void				migrate_colors(t_file_data *file_data, t_data *render_data);
void				exit_invalid_argc(void);
void				validate_textures(t_data *render_data);

#endif
