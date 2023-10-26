/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:12:42 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/26 11:26:47 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

// int	isWallOrFloor(char c)
// {
// 	return (c == '0' || c == '1');
// }

// t_return_value validateMap(t_file_data *data, int mapWidth)
// {
//     int
//  mapHeight;
//     bool foundEmptyLine;
//     char currentChar;

//     mapHeight = data->map_number_of_lines;
//     foundEmptyLine = false;
//     for (int y = 0; y < mapHeight; y++)
//     {
//         bool isEmptyLine = true; // Initialize isEmptyLine for each row
//         for (int x = 0; x < mapWidth; x++)
//         {
//             currentChar = data->map_as_array[y][x];
//             if (x == 0) // Check if the line starts with a wall
//             {
//                 if (currentChar != WALL)
//                 {
//                     isEmptyLine = false; // Reset isEmptyLine if the first character is not a wall
//                 }
//             }
//             if (currentChar == FLOOR)
//             {
//                 // Check surrounding cells (up, down, left, right)
//                 if (y > 0 && data->map_as_array[y - 1][x] != WALL && data->map_as_array[y - 1][x] != FLOOR)
//                     return false;
//                 if (y < mapHeight - 1 && data->map_as_array[y + 1][x] != WALL && data->map_as_array[y + 1][x] != FLOOR)
//                     return false;
//                 if (x > 0 && data->map_as_array[y][x - 1] != WALL && data->map_as_array[y][x - 1] != FLOOR)
//                     return false;
//                 if (x < mapWidth - 1 && data->map_as_array[y][x + 1] != WALL && data->map_as_array[y][x + 1] != FLOOR)
//                     return false;
//             }
//         }
//         if (isEmptyLine)
//         {
//             printf("line is empty\n\n");
//             data->return_value = MAP_CONTAINS_EMPTY_LINE;
//             return data->return_value;
//         }
//     }
//     return data->return_value;
// }







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
	int	i;

	i = 0;
	while (i < max_line_length && line_starts[i] != '\n'
		&& line_starts[i] != '\0')
	{
		if (line_starts[i] == '0')
			data->map_as_array[current_line][i] = FLOOR;
		else if (line_starts[i] == '1')
			data->map_as_array[current_line][i] = WALL;
		else if (line_starts[i] == ' ')
			data->map_as_array[current_line][i] = EMPTY;
		else
			data->map_as_array[current_line][i] = FLOOR;
		i++;
	}
	while (i < max_line_length)
		data->map_as_array[current_line][i++] = EMPTY;
	data->map_as_array[current_line][max_line_length] = NEW_LINE;
}

/**
 * @brief Allocate memory for the map array and copy map data.
 *
 * This function allocates memory for the map array and copies the map data from
 * the string.
 *
 * @param data The structure to store imported data.
 * @param map_as_string The string with map data.
 * @param max_line_length The maximum length of a map line.
 * @param current_line The current line being processed.
 * @param line_starts The starting point of the current map line.
 * @return A return code indicating success or failure.
 */
static t_return_value	allocate_map_array_and_copy_data(t_file_data *data,
														int max_line_length,
														int current_line,
														char *line_starts)
{
	char	*line_ends;

	line_ends = ft_strchr(line_starts, '\n');
	data->map_as_array[current_line] = (t_map_tile *)ft_calloc(max_line_length
			+ 1, sizeof(int));
	if (!data->map_as_array[current_line])
	{
		data->return_value = MALLOC_FAILURE;
		return (data->return_value);
	}
	copy_map_data(line_starts, data, max_line_length, current_line);
	return (data->return_value);
}

/**
 * @brief Transfer the map data from a string to a map array.
 *
 * This function transfers the map data from a string to a map array.
 *
 * @param data The structure to store imported data.
 * @param map_as_string The string with map data.
 * @param max_line_length The maximum length of a map line.
 * @return A return code indicating success or failure.
 */
t_return_value	transfer_remaining_string_to_map_array(t_file_data *data,
														char *map_as_string)
{
	int		max_line_length;
	char	*line_starts;
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
		if (allocate_map_array_and_copy_data(data, max_line_length,
				current_line, line_starts) != SUCCESS)
			return (data->return_value);
		line_starts = ft_strchr(line_starts, '\n');
		if (!line_starts)
			break ;
		line_starts++;
		current_line++;
	}
	data->map_as_array[data->map_number_of_lines] = NULL;
	// validateMap(data, max_line_length);
	return (data->return_value);
}
