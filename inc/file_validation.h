/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:28:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/02 08:45:38 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_VALIDATION_H
# define FILE_VALIDATION_H

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}					t_color;

# define ELEMENTS_NEEDED 6
# define SPAWN_DIRECTION "NSEW"
# define SKIP_WHITE_SPACES 42
# define SKIP_CONSECUTIVE_NEW_LINES 24
# define N 1
# define S 2
# define W 3
# define E 4

typedef enum e_map_tile
{
	FLOOR,
	WALL,
	EMPTY,
	NEW_LINE
}					t_map_tile;

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum e_return_value
{
	SUCCESS,
	FAILURE,
	MALLOC_FAILURE,
	NEED_MAP_CUB_FILE,
	FILE_OPEN_FAILURE,
	FILE_IS_EMPTY,
	MAP_CONTENT_NOT_VALID,
	ELEMENTS_NOT_VALID,
	ELEMENT_NOT_FOUND,
	ELEMENT,
	ELEMENT_FOUND,
	MISSING_ELEMENTS,
	DUPLICATE_ELEMENT,
	NO_ELEMENT_FOUND,
	ALL_ELEMENTS_FOUND,
	PLAYER_DATA_INCORRECT_OR_MISSING,
	INVALID_ARGUMENT,
	GARBAGE_DATA,
	MAP_CONTAINS_EMPTY_LINE,
	WALL_IS_BREACHED,
	INVALID_COLORS,
	MAP_MISSING,
}					t_return_value;

// Structure to hold information extracted from the scene description file
typedef struct s_file_data
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*floor_color;
	char			*ceiling_color;
	char			*file_content_as_string;
	t_map_tile		**map_as_array;
	char			player_spawn_direction[1];
	int				current_position;
	int				last_new_line_position;
	int				map_number_of_lines;
	int				direction_index;
	int				line_count;
	int				elements_found;
	double			player_x;
	double			player_y;
	int				file_descriptor;
	t_color			floor_rgb;
	t_color			ceiling_rgb;
	t_return_value	return_value;
	int				max_map_width;
}					t_file_data;

t_return_value		validate_cub_file(t_file_data *file_data,
						const char **path_to_file);
t_return_value		get_scene_elements_and_map(t_file_data *data);
t_return_value		validate_scene_requirement(t_file_data *data);
t_return_value		get_map_amount_of_lines(t_file_data *data,
						char *map_as_string);
char				*skip_leading_white_spaces(char *string_beginning);
t_return_value		transfer_remaining_string_to_map_array(t_file_data *data,
						char *map_as_string);
t_return_value		initialize_string_buffers(char **line_buffer,
						t_file_data *data);
int					get_max_line_length(char *map_as_string);
t_return_value		map_import_and_preparation(t_file_data *data,
						char *map_as_string);
t_return_value		check_map_does_not_contain_empty_lines(t_file_data *data,
						char *map_as_string);
#endif
