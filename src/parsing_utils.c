/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:47:42 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/01 11:59:11 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Get the number of lines in the map content.
 *
 * This function calculates the number of lines in the map content by counting
 * the newline characters. It also validates that the map contains a minimum of
 * three lines.
 *
 * @param data A pointer to the t_file_data structure.
 * @param map_as_string The map content as a string.
 * @return The number of lines in the map content.
 */
t_return_value	get_map_amount_of_lines(t_file_data *data, char *map_as_string)
{
	char	*temp;

	if (map_as_string)
	{
          temp = map_as_string;
          data->map_number_of_lines++;
          while (*temp) 
		  {
            if (*temp == '\n')
              data->map_number_of_lines++;
            temp++;
          }
    }
	if (data->map_number_of_lines < 4)
	 {
		data->return_value = MAP_CONTENT_NOT_VALID;

	 }
	return (data->return_value);
}

/**
 * @brief Get the maximum line length in the map content.
 *
 * This function calculates the maximum line length in the map content by
 * iterating through the lines.
 *
 * @param map_as_string The map content as a string.
 * @return The maximum line length.
 */
int	get_max_line_length(char *map_as_string)
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
		if (line_starts && *line_starts != '\0')
			line_starts++;
	}
	return (max_line_length);
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
t_return_value	initialize_string_buffers(char **line_buffer,
		t_file_data *data)
{
	*line_buffer = ft_strdup("");
	if (data->file_content_as_string)
		free(data->file_content_as_string);
	data->file_content_as_string = ft_strdup("");
	if (!*line_buffer || !data->file_content_as_string)
	{
		data->return_value = MALLOC_FAILURE;
		if (*line_buffer)
			free(*line_buffer);
		if (data->file_content_as_string)
			free(data->file_content_as_string);
		close(data->file_descriptor);
	}
	return (data->return_value);
}

/**
 * @brief Checks if all characters in the input string are digits and the 
 * string is not empty.
 *
 * This function returns true if all characters in the input string are 
 * digits (0-9) and if the string is not empty. Otherwise, it returns false.
 *
 * @param str The input string to be checked.
 * @return TRUE if the string consists of only digits and is not empty, FALSE 
 * otherwise.
 */
t_bool	ft_is_numerical(char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
