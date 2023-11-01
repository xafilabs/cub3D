/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:12:42 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/01 10:27:36 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Checks if a position in the map is either a wall or floor.
 *
 * This function checks if the specified position in the map is either a wall or
 * a floor. It returns `TRUE` if the given position is surrounded by walls or
 * floors and `FALSE` otherwise.
 *
 * @param data The map data structure.
 * @param line The line (Y-coordinate) of the position to check.
 * @param column The column (X-coordinate) of the position to check.
 * @param map_width The width of the map.
 * @return `TRUE` if the position is a wall or floor, `FALSE` otherwise.
 */
t_bool	is_wall_or_floor(t_file_data *data, int line, int column, int map_width)
{
	t_bool	is_wall_or_floor;

	is_wall_or_floor = FALSE;
	if (line > 0 && line < (data->map_number_of_lines - 1)
		&& column > 0 && column < map_width)
	{
		if (data->map_as_array[line - 1][column] < 2
			&& data->map_as_array[line + 1][column] < 2
			&& data->map_as_array[line][column - 1] < 2
			&& data->map_as_array[line][column + 1] < 2)
		{
			is_wall_or_floor = TRUE;
		}
	}
	return (is_wall_or_floor);
}

/**
 * @brief Validates the entire map for wall breaches.
 *
 * This function validates the entire map to ensure that all floor positions are
 * surrounded by walls or floors. If a floor position is not surrounded
 * properly, it sets the `data->return_value` to `WALL_IS_BREACHED`.
 *
 * @param data The map data structure.
 * @param map_width The width of the map.
 * @return The validation result (`WALL_IS_BREACHED` or no error).
 */
t_return_value	validate_map(t_file_data *data, int map_width)
{
	int	line;
	int	column;

	line = 0;
	print_struct(data);
	while (line < data->map_number_of_lines - 1)
	{
		column = 0;
		while (column < map_width)
		{
			if (data->map_as_array[line][column] == FLOOR)
			{
				if (line == data->map_number_of_lines - 2)
					data->return_value = WALL_IS_BREACHED;
				if (!is_wall_or_floor(data, line, column, map_width))
					data->return_value = WALL_IS_BREACHED;
			}
			column++;
		}
		line++;
	}
	return (data->return_value);
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
t_return_value
	transfer_remaining_string_to_map_array(t_file_data *data,
		char *map_as_string)
{
	char	*line_starts;
	int		current_line;

	data->max_map_width = get_max_line_length(map_as_string);
	current_line = 0;
	line_starts = map_as_string;
	data->map_as_array = (t_map_tile **)
		ft_calloc(data->map_number_of_lines + 1, sizeof(int *));
	if (!data->map_as_array)
		return (data->return_value = MALLOC_FAILURE);
	while (*line_starts != '\0' && current_line < data->map_number_of_lines)
	{
		if (allocate_map_array_and_copy_data(data, data->max_map_width,
				current_line, line_starts) != SUCCESS)
			return (data->return_value);
		line_starts = ft_strchr(line_starts, '\n');
		if (!line_starts)
			break ;
		line_starts++;
		current_line++;
	}
	data->map_as_array[data->map_number_of_lines] = NULL;
	validate_map(data, data->max_map_width);
	return (data->return_value);
}
