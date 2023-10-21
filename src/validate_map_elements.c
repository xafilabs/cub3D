/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:42:34 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/21 13:36:30 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
* @brief Remove leading white spaces from a string.
*
* This function removes leading white spaces (spaces and tabs) from a string.
*
* @param string_beginning The beginning of the string to process.
*/
static char	*remove_leading_white_spaces(char *string_beginning)
{
	return (ft_strtrim(string_beginning, " \t\v\f\r\n"));
}

static int	get_map_amount_of_lines(t_file_data *data, char *map_as_string)
{
	char	*temp;

	temp = map_as_string;
	data->map_number_of_lines++;
	while (*temp)
	{
		if (*temp == '\n')
			data->map_number_of_lines++;
		temp++;
	}
	if (data->map_number_of_lines < 3)
		data->return_value = MAP_CONTENT_NOT_VALID;
	return (data->map_number_of_lines + 1);
}

static int	get_max_line_length(char *map_as_string)
{
	int		max_line_length;
	int		line_length;
	char	*line_starts;
	char	*line_ends;

	max_line_length = 0;
	line_starts = map_as_string;
	while (*line_starts != '\0')
	{
		line_ends = ft_strchr(line_starts, '\n');
		if (line_ends == NULL)
			line_ends = line_starts + ft_strlen(line_starts);
		line_length = line_ends - line_starts;
		if (line_length > max_line_length)
			max_line_length = line_length;
		line_starts = line_ends;
		line_starts++;
	}
	return (max_line_length);
}

static void	copy_map_data(char *line_starts, t_file_data *data,
		int max_line_length, int current_line)
{
	int	j;

	j = 0;
	while (j < max_line_length && line_starts[j] != '\n' && line_starts[j] != '\0')
	{
		if (line_starts[j] == '0')
			data->map_as_array[current_line][j] = FLOOR;
		else if (line_starts[j] == '1')
			data->map_as_array[current_line][j] = WALL;
		else if (line_starts[j] == ' ')
			data->map_as_array[current_line][j] = EMPTY;
		j++;
	}
	while (j < max_line_length)
		data->map_as_array[current_line][j++] = EMPTY;
	data->map_as_array[current_line][max_line_length ] = NEW_LINE;
}

static t_return_value	transfer_remaining_string_to_map_array(t_file_data *data,
																char *map_as_string)
{
	int		max_line_length;
	char	*line_starts;
	char	*line_ends;
	int		current_line;

	max_line_length = get_max_line_length(map_as_string);
	printf("max_line_length :%d:\n", max_line_length);
	current_line = 0;
	line_starts = map_as_string;
	data->map_as_array = (t_map_tile **)ft_calloc(data->map_number_of_lines + 1,
													sizeof(int *));
	if (!data->map_as_array)
		return (data->return_value = MALLOC_FAILURE);
	while (*line_starts != '\0' && current_line < data->map_number_of_lines)
	{
		line_ends = ft_strchr(line_starts, '\n');
		data->map_as_array[current_line] = (t_map_tile *)ft_calloc(max_line_length + 2,
														sizeof(int));
		if (!data->map_as_array)
			return (data->return_value = MALLOC_FAILURE);
		copy_map_data(line_starts, data, max_line_length, current_line);
		line_starts = line_ends;
		if (!line_starts)
			break;
		line_starts++;
		current_line++;
	}
	data->map_as_array[data->map_number_of_lines] = NULL;
	return (data->return_value);
}

static t_return_value	get_player_spawn_position_and_direction(t_file_data *data,
																char *map_string_contains_player_position,
																const char *spawn_direction_delimiter)
{
	int	spawn_location;
	int	index_relative_to_last_new_line_found;
	int	spawn_direction_index;
	int	new_lines_found;

	spawn_location = 0;
	new_lines_found = 0;
	while (map_string_contains_player_position[spawn_location] != '\0')
	{
		if (map_string_contains_player_position[spawn_location] == '\n')
		{
			new_lines_found++;
			index_relative_to_last_new_line_found = spawn_location;
		}
		spawn_direction_index = 0;
		while (spawn_direction_delimiter[spawn_direction_index] != '\0')
		{
			if (map_string_contains_player_position[spawn_location] == spawn_direction_delimiter[spawn_direction_index])
			{
				data->player_x = spawn_location
					- index_relative_to_last_new_line_found;
				data->player_y = new_lines_found;
				*data->player_spawn_direction = spawn_direction_delimiter[spawn_direction_index];
				return (data->return_value);
			}
			spawn_direction_index++;
		}
		spawn_location++;
	}
	return (data->return_value = PLAYER_DATA_INCORRECT_OR_MISSING);
}

/**
 * @brief Import and prepare map elements from a text file.
 *
 * @param data The structure to store imported data.
 * @param element_starts The start of the element in the file.
 * @return A return code indicating success or failure.
 */
static t_return_value	map_import_and_preparation(t_file_data *data,
													char *map_as_string)
{
	map_as_string = remove_leading_white_spaces(map_as_string);
	printf("map as string after trimming :\n%s\n:\n", map_as_string);
	if (get_map_amount_of_lines(data, map_as_string) == MAP_CONTENT_NOT_VALID)
		return (data->return_value);
	printf("map_amount_of_lines :%d:\n", data->map_number_of_lines);
	get_player_spawn_position_and_direction(data, map_as_string,
			SPAWN_DIRECTION);
	transfer_remaining_string_to_map_array(data, map_as_string);
	return (data->return_value);
}

/**
 * @brief Get the texture element content from the provided string.
 *
 * This function extracts the content of a texture element from a string.
 *
 * @param element_type A pointer to store the extracted element content.
 * @param element_content The string containing the element content.
 * @return A return code indicating success or failure.
 */
static t_return_value	get_element_texture(char **element_type,
											char *element_content)
{
	size_t	element_length;

	element_length = 0;
	element_content = remove_leading_white_spaces(element_content);
	while (element_content[element_length] != '\n'
		&& element_content[element_length] != '\0')
		element_length++;
	*element_type = (char *)calloc(element_length + 1, sizeof(char));
	if (*element_type == NULL)
		return (MALLOC_FAILURE);
	ft_strlcpy(*element_type, element_content, element_length + 1);
	return (ELEMENT_FOUND);
}
/**
 * @brief Find and extract map elements from a string.
 *
 * This function identifies and extracts various map elements from a string,
 * such as textures, floor color, ceiling color.
 *
 * @param element The string to analyze and extract elements from.
 * @param data The structure to store the extracted elements.
 * @return A return code indicating success or failure.
 */
static t_return_value	find_and_get_element(char *element, t_file_data *data)
{
	char			*temp;
	t_return_value	return_value;

	temp = element;
	element = remove_leading_white_spaces(temp);
	return_value = ELEMENT_NOT_FOUND;
	if (ft_strncmp("NO ", element, 3) == 0)
		return_value = get_element_texture(&data->north_texture, element + 3);
	else if (ft_strncmp("SO ", element, 3) == 0)
		return_value = get_element_texture(&data->south_texture, element + 3);
	else if (ft_strncmp("WE ", element, 3) == 0)
		return_value = get_element_texture(&data->west_texture, element + 3);
	else if (ft_strncmp("EA ", element, 3) == 0)
		return_value = get_element_texture(&data->east_texture, element + 3);
	else if (ft_strncmp("F ", element, 2) == 0)
		return_value = get_element_texture(&data->floor_color, element + 2);
	else if (ft_strncmp("C ", element, 2) == 0)
		return_value = get_element_texture(&data->ceiling_color, element + 2);
	if (return_value == MALLOC_FAILURE)
		data->return_value = MALLOC_FAILURE;
	else if (return_value == ELEMENT_FOUND)
		data->elements_found++;
	if (data->elements_found == ELEMENTS_NEEDED)
		return (ALL_ELEMENTS_FOUND);
	return (return_value);
}

/**
 * @brief Get map elements from the input scene description.
 *
 * This function parses the input scene description and extracts map elements.
 *
 * @param data The structure to store the extracted elements.
 * @return A return code indicating success or failure.
 */
static t_return_value	get_scene_elements_and_map(t_file_data *data)
{
	char	*element_starts;
	char	*element_ends;
	int		i;

	i = 0;
	element_starts = data->file_content_as_string;
	while (*element_starts != '\0' && data->elements_found < ELEMENTS_NEEDED)
	{
		element_starts = remove_leading_white_spaces(element_starts);
		element_ends = ft_strchr(element_starts, '\n');
		if (element_ends != element_starts)
		{
			if (*element_starts == '1' || *element_starts == '0')
				break ;
			if (find_and_get_element(element_starts, data) == MALLOC_FAILURE)
				break ;
		}
		element_starts = element_ends;
		if (element_starts != '\0')
			element_starts++;
	}
	print_elements(data);
	printf("element_starts after finding all elements:\n:\n%s\n:\n",
			element_starts);
	if (data->return_value == SUCCESS)
		map_import_and_preparation(data, element_starts);
	return (data->return_value);
}
/**
 * @brief Validate scene requirements and import map elements.
 *
 * This function validates the scene requirements and imports map elements.
 *
 * @param data The structure to store the extracted elements.
 * @return A return code indicating success or failure.
 */
t_return_value	validate_scene_requirement(t_file_data *data)
{
	if (get_scene_elements_and_map(data) != SUCCESS)
		return (data->return_value);
	printf("\n\n_______PRINT_STRUCT:\n");
	print_struct(data);
	return (data->return_value);
}
