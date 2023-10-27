/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:28:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/27 11:47:23 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_VALIDATION_H
# define FILE_VALIDATION_H

// Structure to hold RGB color components
typedef struct s_color
{
	int red;   // Red component (0-255)
	int green; // Green component (0-255)
	int blue;  // Blue component (0-255)
}					t_color;

# define ELEMENTS_NEEDED			6
# define SPAWN_DIRECTION			"NSEW"
# define SKIP_WHITE_SPACES			42
# define SKIP_CONSECUTIVE_NEW_LINES 24
# define N							1
# define S							2
# define W							3
# define E							4

typedef	enum e_map_tile
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
	NO_ELEMENT_FOUND,
	ALL_ELEMENTS_FOUND,
	PLAYER_DATA_INCORRECT_OR_MISSING,
	INVALID_ARGUMENT,
	GARBAGE_DATA,
	MAP_CONTAINS_EMPTY_LINE,
	WALL_IS_BREACHED,

}						t_return_value;

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
	int				map_number_of_lines;
	int				elements_found;
	double			player_x;
	double			player_y;
	int				file_descriptor;
	t_color			floor_rgb;
	t_color			ceiling_rgb;
	t_return_value	return_value;
}					t_file_data;

t_return_value	validate_cub_file(t_file_data *file_data, const char **path_to_file);
t_return_value	get_scene_elements_and_map(t_file_data *data);
t_return_value	validate_scene_requirement(t_file_data *data);
int				get_map_amount_of_lines(t_file_data *data, char *map_as_string);
char			*remove_leading_white_spaces(char *string_beginning);
t_return_value	transfer_remaining_string_to_map_array(t_file_data *data, char *map_as_string);
#endif
