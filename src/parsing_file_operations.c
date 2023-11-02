/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:42:34 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/01 15:21:54 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Open and validate the scene description file.
 *
 * This function opens the specified file, validates its existence, and sets up
 * the file descriptor for reading. If any errors occur during the process, it
 * sets the appropriate error code in the t_file_data structure.
 *
 * @param data A pointer to the t_file_data structure.
 * @param path An array containing the path to the scene description file.
 * @return The exit code indicating success or failure.
 */
static t_return_value	open_and_validate_file(t_file_data *data,
												const char **path)
{
	data->file_descriptor = open(path[1], O_RDONLY);
	if (data->file_descriptor == -1)
	{
		data->return_value = FILE_OPEN_FAILURE;
		close(data->file_descriptor);
		return (data->return_value);
	}
	return (data->return_value);
}

/**
 * @brief Concatenate a line to the file content string.
 *
 * This function concatenates a line of text to the existing
 * file content string. It ensures that memory is properly allocated
 * for the updated content and handles memory allocation failures
 * by setting the appropriate error code.
 *
 * @param data A pointer to the t_file_data structure.
 * @param line A pointer to the line to be concatenated.
 * @return The exit code indicating success or failure.
 */
static t_return_value	concatenate_line_buffer_to_string(t_file_data *data,
														char *line)
{
	char	*temp;

	temp = ft_strdup(data->file_content_as_string);
	if (temp == NULL)
	{
		data->return_value = MALLOC_FAILURE;
		return (data->return_value);
	}
	free(data->file_content_as_string);
	data->file_content_as_string = ft_strjoin(temp, line);
	free(temp);
	if (data->file_content_as_string == NULL)
		data->return_value = MALLOC_FAILURE;
	return (data->return_value);
}

/**
 * @brief Get the contents of the scene description file into a string.
 *
 * This function reads the contents of the scene description file line by line
 * and stores them in a string buffer. It handles file opening errors, memory
 * allocation failures, and closes the file when finished.
 *
 * @param data A pointer to the t_file_data structure.
 * @param path An array containing the path to the scene description file.
 * @return The exit code indicating success or failure.
 */
t_return_value	get_file_content_to_string(t_file_data *data, const char **path)
{
	char	*line_buffer;

	if (open_and_validate_file(data, path) == FILE_OPEN_FAILURE)
		return (data->return_value);
	if (initialize_string_buffers(&line_buffer, data) == MALLOC_FAILURE)
		return (data->return_value);
	while (line_buffer)
	{
		free(line_buffer);
		line_buffer = get_next_line(data->file_descriptor);
		if (line_buffer == NULL)
			break ;
		if (concatenate_line_buffer_to_string(data,
				line_buffer) == MALLOC_FAILURE)
		{
			free(line_buffer);
			break ;
		}
	}
	if (line_buffer)
		free(line_buffer);
	close(data->file_descriptor);
	return (data->return_value);
}

/**
 * @brief Check the file type to ensure it has the .cub extension.
 *
 * This function checks if the provided file path has the correct
 * extension (.cub). If the extension is incorrect, it sets
 * the appropriate error code in the t_file_data structure and
 * prints a usage message.
 *
 * @param data A pointer to the t_file_data structure.
 * @param path_to_file An array containing the path
 * to the scene description file.
 * @return The exit code indicating success or failure.
 */
t_return_value	check_file_type(t_file_data *data,
								const char **path_to_file)
{
	const char	*path;
	char		*last_4_chars;
	size_t		length;

	path = path_to_file[1];
	last_4_chars = NULL;
	if (*path != '\0')
	{
		length = ft_strlen(path);
		last_4_chars = ft_substr(path, length - 4, 4);
		if (ft_strncmp(".cub", last_4_chars, 4) == SUCCESS)
			free(last_4_chars);
		else
		{
			free(last_4_chars);
			data->return_value = NEED_MAP_CUB_FILE;
		}
	}
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
	if (get_rgb_colors(data) != SUCCESS)
		return (data->return_value);
	printf("\n\n_______PRINT_STRUCT:\n");
	if (data->return_value == SUCCESS)
	 	print_struct(data);
	return (data->return_value);
}
