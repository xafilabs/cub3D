/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/02 10:28:20 by malaakso         ###   ########.fr       */
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
char	*skip_leading_white_spaces(char *string)
{
	while (string && *string != '\0' && (*string == '\t' || *string == '\v'
			|| *string == '\f' || *string == '\r' || *string == ' '
			|| *string == '\n'))
		string++;
	return (string);
}

/**
 * @brief Initializes a structure with zeros.
 *
 * This function initializes the memory pointed to by `structure_pointer` with
 * zeros, effectively setting all its members to zero values. It's commonly used
 * to prepare structures for use.
 *
 * @param structure_pointer A pointer to the structure to be initialized.
 */
void	initialize_struct(t_file_data *structure_pointer)
{
	ft_bzero(structure_pointer, sizeof(*structure_pointer));
}

void	print_parsing_error_message_2(t_return_value error)
{
	if (error == NO_ELEMENT_FOUND)
		ft_putstr_fd(
			"Error\nCub file not properly formatted\n", 2);
	else if (error == PLAYER_DATA_INCORRECT_OR_MISSING)
		ft_putstr_fd(
			"Error\nPlayer data incorrect or missing\n", 2);
	else if (error == GARBAGE_DATA)
		ft_putstr_fd("Error\nMap contains garbage data\n",
			2);
	else if (error == MAP_CONTAINS_EMPTY_LINE)
		ft_putstr_fd(
			"Error\nMap contains at least an empty line\n",
			2);
	else if (error == WALL_IS_BREACHED)
		ft_putstr_fd("Error\nWall is breached\n", 2);
	else if (error == INVALID_COLORS)
		ft_putstr_fd("Error\nInvalid RGB values\n", 2);
	else if (error == DUPLICATE_ELEMENT)
		ft_putstr_fd("Error\nDuplicate element\n", 2);
}

/**
 * @brief Prints an error message based on the error code.
 *
 * This function prints an error message to the standard error (stderr) stream
 * based on the provided error code. The error messages are related to specific
 * error conditions such as memory allocation failure, file open failure, or
 * invalid file content.
 *
 * @param error The error code representing the specific error condition.
 */
void	print_parsing_error_message(t_return_value error)
{
	if (error == MALLOC_FAILURE)
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
	else if (error == NEED_MAP_CUB_FILE)
		ft_putstr_fd("Error\nUsage: use cub file\n", 2);
	else if (error == FILE_IS_EMPTY)
		ft_putstr_fd("Error\nFile is empty\n", 2);
	else if (error == FILE_OPEN_FAILURE)
		ft_putstr_fd("Error\nFile open failure\n", 2);
	else if (error == MAP_CONTENT_NOT_VALID)
		ft_putstr_fd("Error\nFile content not valid\n",
			2);
	else if (error == INVALID_ARGUMENT)
		ft_putstr_fd("Error\nUsage: use cub file\n", 2);
	else if (error == MISSING_ELEMENTS)
		ft_putstr_fd("Error\nSome elements are missing\n", 2);
	else
		print_parsing_error_message_2(error);
}

/**
 * @brief Frees memory allocated for parsed data.
 *
 * This function is responsible for cleaning up memory allocated during the
 * parsing process, including textures, colors, file content, and the map array.
 *
 * @param data A pointer to the t_file_data structure.
 */
void	clean_up_parsing(t_file_data *data)
{
	int	i;

	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->floor_color)
		free(data->floor_color);
	if (data->ceiling_color)
		free(data->ceiling_color);
	if (data->file_content_as_string)
		free(data->file_content_as_string);
	if (data->map_as_array)
	{
		i = 0;
		while (data->map_as_array[i])
			free(data->map_as_array[i++]);
		free(data->map_as_array);
	}
}
