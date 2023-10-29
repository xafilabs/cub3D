/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_and_player_import.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:19:06 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/29 13:12:14 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/**
 * @brief Set player data based on the input string and player spawn direction.
 *
 * This function sets the player's spawn position and direction based on the
 * provided input string and player spawn direction.
 *
 * @param data A pointer to the t_file_data structure.
 * @param input_string The string containing player data.
 * @param player_spawn_direction The player's spawn direction.
 */
static void
	set_player_data(t_file_data *data, char *input_string,
		char player_spawn_direction)
{
	data->player_x = data->current_position - data->last_new_line_position;
	data->player_y = data->line_count;
	*data->player_spawn_direction = player_spawn_direction;
	input_string[data->current_position] = '0';
}

/**
 * @brief Get player spawn position and direction.
 *
 * This function extracts the player's spawn position and direction from the
 * scene description and updates the corresponding fields in the data structure.
 *
 * @param data A pointer to the t_file_data structure.
 * @param input_string The string containing player data.
 * @param spawn_direction_delimiter Delimiter for spawn direction 
 * (e.g., "NSEW" for North, South, East, West).
 * @return The exit code indicating success or failure.
 */
static t_return_value
	get_player_spawn_position_and_direction(t_file_data *data,
										char *input_string,
										const char *spawn_direction_delimiter)
{
	while (input_string[data->current_position] != '\0')
	{
		if (input_string[data->current_position] == '\n')
		{
			data->line_count++;
			data->last_new_line_position = data->current_position;
		}
		data->direction_index = 0;
		while (spawn_direction_delimiter[data->direction_index] != '\0')
		{
			if (input_string[data->current_position] 
				== spawn_direction_delimiter[data->direction_index])
			{
				set_player_data(data, input_string,
					spawn_direction_delimiter[data->direction_index]);
				return (data->return_value);
			}
			data->direction_index++;
		}
		data->current_position++;
	}
	data->return_value = PLAYER_DATA_INCORRECT_OR_MISSING;
	return (data->return_value);
}

/**
 * @brief Check for garbage data before the map in the input string.
 *
 * This function checks for invalid characters or data before the map content
 * in the input string and sets the appropriate error code if found.
 *
 * @param data A pointer to the t_file_data structure.
 * @param map_as_string The string containing map data.
 * @return The exit code indicating success or failure.
 */
static t_return_value
	check_for_garbage_data_in_remaining_map(t_file_data *data,
										char *map_as_string)
{
	while (*map_as_string && *map_as_string != '\0')
	{
		if (*map_as_string != ' ' && *map_as_string != '0'
			&& *map_as_string != '1' && *map_as_string != '\n')
		{
			data->return_value = GARBAGE_DATA;
			return (data->return_value);
		}
		map_as_string++;
	}
	return (data->return_value);
}

/**
 * @brief Import and prepare map elements from a text file.
 *
 * This function parses the input scene description and prepares map elements
 * for use, including the map content and player data. SPAWN_DIRECTION is 
 * defined as the following delimiter string "NSEW"
 *
 * @param data A pointer to the t_file_data structure.
 * @param map_as_string The string containing map data.
 * @return The exit code indicating success or failure.
 */
t_return_value	map_import_and_preparation(t_file_data *data,
		char *map_as_string)
{
	if (data->elements_found != 6)
	{
		if (data->elements_found == 0)
			data->return_value = NO_ELEMENT_FOUND;
		else
			data->return_value = MISSING_ELEMENTS;
		return (data->return_value);
	}
	//printf("map as string after trimming :\n->%s\n:\n", map_as_string);
	if (get_map_amount_of_lines(data, map_as_string) == MAP_CONTENT_NOT_VALID)
		return (data->return_value);
	//printf("map_amount_of_lines :%d:\n", data->map_number_of_lines);
	get_player_spawn_position_and_direction(data, map_as_string,
		SPAWN_DIRECTION);
	if (check_for_garbage_data_in_remaining_map(data,
			map_as_string) == GARBAGE_DATA)
		return (data->return_value);
	if (check_map_does_not_contain_empty_lines(data,
			map_as_string) == MAP_CONTAINS_EMPTY_LINE)
		return (data->return_value);
	transfer_remaining_string_to_map_array(data, map_as_string);
	return (data->return_value);
}
