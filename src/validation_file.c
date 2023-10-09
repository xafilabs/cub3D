/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:17:58 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/09 11:49:47 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

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
static	t_return_value open_and_validate_file(t_file_data *data, char **path)
{
	data->file_descriptor = open(path[1], O_RDONLY);
	if (data->file_descriptor == -1)
	 {
		data->return_value == FILE_OPEN_ERROR;
		close(data->file_descriptor);
		return (data->return_value);
	 }
	return (data->return_value);
}

/**
 * @brief Initialize string buffers for file content and line.
 *
 * This function initializes the string buffers for storing the file's content
 * and each line of the file. It allocates memory for these buffers and handles
 * memory allocation failures by setting the appropriate error code.
 *
 * @param line A pointer to the line buffer.
 * @param file_content_as_string A pointer to the file content buffer.
 * @param data A pointer to the t_file_data structure.
 * @return The exit code indicating success or failure.
 */
static t_return_value	initialize_string_buffers(char *line, char *file_content_as_string, t_file_data *data)
{
	line = ft_strdup("");
	file_content_as_string = ft_strdup(""); 
	if (!line || !file_content_as_string)
	{
		data->return_value = MALLOC_FAIL;
		if (line)
			free(line);
		if (file_content_as_string)
			free(file_content_as_string);
		close(data->file_descriptor);
	}
	return (data->return_value);
}

/**
 * @brief Concatenate a line to the file content string.
 *
 * This function concatenates a line of text to the existing file content string.
 * It ensures that memory is properly allocated for the updated content and handles
 * memory allocation failures by setting the appropriate error code.
 *
 * @param data A pointer to the t_file_data structure.
 * @param line A pointer to the line to be concatenated.
 * @return The exit code indicating success or failure.
 */
static t_return_value	concatenate_line_to_string(t_file_data *data, char *line)
{
	char	*temp;

	temp = ft_strdup(data->file_content_as_string);
	if (temp == NULL)
	 {
		data->return_value = MALLOC_FAIL;
		return (data->return_value);
	 }
	free(data->file_content_as_string);
	data->file_content_as_string = ft_strjoin(temp, line);
	free(temp);
	if (data->file_content_as_string == NULL)
		data->return_value = MALLOC_FAIL;
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
static t_return_value	get_file_content_to_string(t_file_data *data, const char **path)
{
	char	*line;

	if (open_and_validate_file(data, path) == FILE_OPEN_ERROR)
		return (data->return_value);
	if (initialize_string_buffers(line, data->file_content_as_string, data) == MALLOC_FAIL)
		return (data->return_value);
	while (line)
	{
		line = get_next_line(data->file_descriptor);
		if (line == NULL)
			break;
		if (concatenate_line_to_string(data, line) == MALLOC_FAIL)
			break;
		free(line);
	}
	if (line)
		free(line);
	close(data->file_descriptor);
	return (data->return_value);
}

/**
 * @brief Check the file type to ensure it has the .cub extension.
 *
 * This function checks if the provided file path has the correct extension (.cub).
 * If the extension is incorrect, it sets the appropriate error code in the t_file_data
 * structure and prints a usage message.
 *
 * @param data A pointer to the t_file_data structure.
 * @param path_to_file An array containing the path to the scene description file.
 * @return The exit code indicating success or failure.
 */
static t_return_value	check_file_type(t_file_data *data, const char **path_to_file)
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
			printf("usage: ./cube3d map.cub\n");
			data->return_value = NEED_MAP_CUB_FILE;
		}
	}
	return (data->return_value);
}

/**
 * @brief Validate the scene description file.
 *
 * This function validates the scene description file by checking its type and
 * reading its content into a string. It also handles any errors that may occur
 * during the validation process and sets the appropriate error codes.
 *
 * @param data A pointer to the t_file_data structure.
 * @param path_to_file An array containing the path to the scene description file.
 * @return The exit code indicating success or failure.
 */
t_return_value	validate_cub_file(t_file_data *data, const char **path_to_file)
{
	if (check_file_type(data, path_to_file) == SUCCESS)
	{
		if (get_file_content_to_string(data, path_to_file) == SUCCESS)
		{
			
		}
	}
	return (data->return_value);
}
