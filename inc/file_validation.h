/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:28:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/16 15:32:48 by lclerc           ###   ########.fr       */
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

# define ELEMENTS_NEEDED 6

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
	INVALID_ARGUMENT,
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
	char			**map_as_array;
	char			player_spawn_direction;
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

#endif
