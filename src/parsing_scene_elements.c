/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:17:58 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/01 15:21:48 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Get the texture element content from the provided string.
 *
 * This function extracts the content of a texture element from a string.
 *
 * @param element_type A pointer to store the extracted element content.
 * @param element_content The string containing the element content.
 * @return A return code indicating success or failure.
 */
static t_return_value
	get_element_texture(char **element_type, char *element_content)
{
	size_t	element_length;

	element_length = 0;
	element_content = skip_leading_white_spaces(element_content);
	while (element_content[element_length] != '\n'
		&& element_content[element_length] != '\0')
		element_length++;
	if (*element_type != NULL)
		return (DUPLICATE_ELEMENT);
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
 * such as textures, floor color, and ceiling color.
 *
 * @param element The string to analyze and extract elements from.
 * @param data A pointer to the t_file_data structure.
 * @return The exit code indicating success or failure.
 */
static t_return_value
	find_and_get_element(char *element, t_file_data *data)
{
	t_return_value	return_value;

	element = skip_leading_white_spaces(element);
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
	else if (return_value == DUPLICATE_ELEMENT)
		data->return_value = DUPLICATE_ELEMENT;
	else if (return_value == ELEMENT_FOUND)
		data->elements_found++;
	if (data->elements_found == ELEMENTS_NEEDED)
		return (ALL_ELEMENTS_FOUND);
	return (return_value);
}

/**
 * @brief Check if the map contains empty lines.
 *
 * This function checks if the map contains empty lines and sets the appropriate
 * error code in the t_file_data structure if it does.
 *
 * @param data A pointer to the t_file_data structure.
 * @param map_as_string The string representing the map.
 * @return The exit code indicating success or failure.
 */
t_return_value
	check_map_does_not_contain_empty_lines(t_file_data *data,
										char *map_as_string)
{
	t_bool	empty_line;

	empty_line = FALSE;
	while (*map_as_string != '\0')
	{
		if (*map_as_string != ' ' && *map_as_string != '\n')
		{
			empty_line = FALSE;
		}
		else if (*map_as_string == '\n')
		{
			if (empty_line)
			{
				data->return_value = MAP_CONTAINS_EMPTY_LINE;
				return (data->return_value);
			}
			empty_line = TRUE;
		}
		map_as_string++;
	}
	return (data->return_value);
}

/**
 * @brief Get map elements from the input scene description.
 *
 * This function parses the input scene description and extracts map elements
 * such as textures, floor color, ceiling color, and the map itself.
 *
 * @param data A pointer to the t_file_data structure.
 * @return The exit code indicating success or failure.
 */
t_return_value
	get_scene_elements_and_map(t_file_data *data)
{
	char	*element_starts;
	char	*element_ends;

	element_starts = data->file_content_as_string;
	while (element_starts && *element_starts != '\0'
		&& data->elements_found < ELEMENTS_NEEDED)
	{
		element_starts = skip_leading_white_spaces(element_starts);
		element_ends = ft_strchr(element_starts, '\n');
		if (element_starts != element_ends)
		{
			if (*element_starts == '1' || *element_starts == '0')
				break ;
			if (find_and_get_element(element_starts, data) == MALLOC_FAILURE)
				break ;
		}
		element_starts = element_ends;
		if (element_starts && *element_starts != '\0')
			element_starts++;
	}
	while (element_starts && *element_starts != '\0' && *element_starts == '\n')
		element_starts++;
	if (data->return_value == SUCCESS)
		map_import_and_preparation(data, element_starts);
	return (data->return_value);
}
