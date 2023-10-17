/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:42:34 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/16 15:37:10by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	get_map_amount_of_lines(t_file_data *data, char *map_as_string)
{
	char	*temp;

	temp = map_as_string;
	while (*temp)
	{
		if (*temp == '\0' || (*temp == '\n' && *temp + 1 != '\n') || (*temp == '\n' && *temp != '\0'))
			data->map_number_of_lines++;
		temp++;
	}
	if (data->map_number_of_lines < 3)
		data->return_value = MAP_CONTENT_NOT_VALID;
	return (data->map_number_of_lines);
}

static t_return_value	transfer_remaining_string_to_map_array(t_file_data *data,
		char *map_as_string)
{
	char	*line_starts;
	char	*line_ends;
	int		i;
	
	i = 0;
	line_starts = map_as_string;
	data->map_as_array = (char **)ft_calloc(data->map_number_of_lines + 1,
			sizeof(char *));
	if (!data->map_as_array)
		data->return_value = MALLOC_FAILURE;
	while (*line_starts != '\0' && i <= data->map_number_of_lines)
	{
		line_ends = ft_strchr(line_starts, '\n');
		if (line_ends == NULL)
			line_ends = line_starts + ft_strlen(line_starts);
		data->map_as_array[i] = ft_substr(line_starts, 0, line_ends - line_starts);
		printf("Line just copied :%d: is :%s:\t\t\nline_starts\t\t :%s:\nnumber_of_lines :%d:\n", i, data->map_as_array[i], line_starts, data->map_number_of_lines);
		if (data->map_as_array[i] == NULL)
			return (data->return_value);
		line_starts = line_ends;
		line_starts++;
		i++;
	}
	data->map_as_array[i] = NULL;
	return (data->return_value);
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
	while (*map_as_string == '\n' && (*map_as_string + 1 == '\0' || *map_as_string == '\n'))
		map_as_string++;
	if (get_map_amount_of_lines(data, map_as_string) == MAP_CONTENT_NOT_VALID)
		return (data->return_value);
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
	while (element_content[element_length] != '\n'
		&& element_content[element_length] != '\0')
		element_length++;
	*element_type = (char *)calloc(element_length + 1, sizeof(char));
	if (*element_type == NULL)
		return (MALLOC_FAILURE);
	ft_strlcpy(*element_type, element_content, element_length + 1);
	return (SUCCESS);
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
	t_return_value	return_value;

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
	data->return_value = return_value;
	return (data->return_value);
}

/**
 * @brief Remove leading white spaces from a string.
 *
 * This function removes leading white spaces (spaces and tabs) from a string.
 *
 * @param string_beginning The beginning of the string to process.
 */
static void	remove_leading_white_spaces(char *string_beginning)
{
	while (*string_beginning != '\n' || *string_beginning != '\0')
	{
		if ((*string_beginning > 8 && *string_beginning < 14) ||
			*string_beginning == 32)
			string_beginning++;
		else
			break ;
	}
}

/**
 * @brief Get map elements from the input scene description.
 *
 * This function parses the input scene description and extracts map elements.
 *
 * @param data The structure to store the extracted elements.
 * @return A return code indicating success or failure.
 */
static t_return_value	get_scene_elements(t_file_data *data)
{
	char	*element_starts;
	char	*element_ends;

	element_starts = data->file_content_as_string;
	while (*element_starts != '\0' && data->elements_found < ELEMENTS_NEEDED)
	{
		element_ends = ft_strchr(element_starts, '\n');
		remove_leading_white_spaces(element_starts);
		if (element_ends != element_starts)
		{
			if (find_and_get_element(element_starts, data) == SUCCESS)
				data->elements_found++;
			else
				break ;
		}
		element_starts = element_ends;
		element_starts++;
	}
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
	if (get_scene_elements(data) != SUCCESS)
		return (data->return_value);
	//if (get_file_amount_of_lines(data) < 9)
	//return (data->return_value);
	//if (transfer_string_to_array(data) == MALLOC_FAILURE)
	//return (data->return_value);
	printf("\n\n_______PRINT_STRUCT:\n");
	print_struct(data);
	return (data->return_value);
}

