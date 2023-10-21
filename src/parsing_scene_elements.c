/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:17:58 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/21 17:08:28 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Get player spawn position and direction.
 *
 * This function extracts the player's spawn position and direction from the
 * scene description.
 *
 * @param data The structure to store player data.
 * @param map_string_contains_player_position The string with player data.
 * @param spawn_direction_delimiter Delimiter for spawn direction.
 * @return A return code indicating success or failure.
 */
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
 * This function parses the input scene description and prepares map elements for use.
 *
 * @param data The structure to store imported data.
 * @param map_as_string The string with map data.
 * @return A return code indicating success or failure.
 */
static t_return_value	map_import_and_preparation(t_file_data *data,
													char *map_as_string)
{
	if (data->elements_found != 6)
	 {
		data->return_value = MISSING_ELEMENTS;
		return (data->return_value);
	 }
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
 * This function identifies and extracts various map elements from a string, such as textures, floor color, and ceiling color.
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
t_return_value	get_scene_elements_and_map(t_file_data *data)
{
	char	*element_starts;
	char	*element_ends;
	int		i;

	i = 0;
	element_starts = data->file_content_as_string;
	while (element_starts && *element_starts != '\0' && data->elements_found < ELEMENTS_NEEDED)
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
	printf("element_starts after finding all elements:\n:\n%s\n:\n", element_starts);
	if (data->return_value == SUCCESS)
		map_import_and_preparation(data, element_starts);
	return (data->return_value);
}
