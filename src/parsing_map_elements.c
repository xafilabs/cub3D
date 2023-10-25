/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:12:42 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/25 13:19:10 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Remove leading white spaces from a string.
 *
 * This function removes leading white spaces (spaces and tabs) from a string.
 *
 * @param string The string to process.
 * @return A pointer to the string with leading white spaces removed.
 */
char	*remove_leading_white_spaces(char *string)
{
	while (string && *string != '\0' && (*string == '\t' || *string == '\v'
			|| *string == '\f' || *string == '\r' || *string == ' '))
		string++;
	return (string);
}

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
int	get_map_amount_of_lines(t_file_data *data, char *map_as_string)
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
/**
 * @brief Get the maximum line length in the map content.
 *
 * This function calculates the maximum line length in the map content by
 * iterating through the lines.
 *
 * @param map_as_string The map content as a string.
 * @return The maximum line length.
 */
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
/**
 * @brief Copy map data to a 2D array.
 *
 * This function copies the map data from the string to a 2D array and converts
 * the characters to their corresponding integer values (e.g., '0' to FLOOR).
 *
 * @param line_starts The start of the line in the map string.
 * @param data A pointer to the t_file_data structure.
 * @param max_line_length The maximum line length.
 * @param current_line The current line number being processed.
 */
static void	copy_map_data(char *line_starts, t_file_data *data,
		int max_line_length, int current_line)
{
	int	j;

	j = 0;
	while (j < max_line_length && line_starts[j] != '\n'
		&& line_starts[j] != '\0')
	{
		if (line_starts[j] == '0')
			data->map_as_array[current_line][j] = FLOOR;
		else if (line_starts[j] == '1')
			data->map_as_array[current_line][j] = WALL;
		else if (line_starts[j] == ' ')
			data->map_as_array[current_line][j] = EMPTY;
		else
			data->map_as_array[current_line][j] = FLOOR;
		j++;
	}
	while (j < max_line_length)
		data->map_as_array[current_line][j++] = EMPTY;
	data->map_as_array[current_line][max_line_length] = NEW_LINE;
}

/**
 * @brief Transfer the remaining string to a 2D array.
 *
 * This function transfers the remaining map data from the string to a 2D array.
 * It also determines the maximum line length and allocates memory accordingly.
 *
 * @param data A pointer to the t_file_data structure.
 * @param map_as_string The map content as a string.
 * @return A return code indicating success or failure.
 */
t_return_value	transfer_remaining_string_to_map_array(t_file_data *data,
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
		data->map_as_array[current_line] = (t_map_tile *)ft_calloc(max_line_length
				+ 2,
																	sizeof(int));
		if (!data->map_as_array)
			return (data->return_value = MALLOC_FAILURE);
		copy_map_data(line_starts, data, max_line_length, current_line);
		line_starts = line_ends;
		if (!line_starts)
			break ;
		line_starts++;
		current_line++;
	}
	data->map_as_array[data->map_number_of_lines] = NULL;
	return (data->return_value);
}
