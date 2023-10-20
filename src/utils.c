/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/20 15:54:36 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"
void print_elements(t_file_data *data) {
    printf("\t\tNorth Texture: %s\n", data->north_texture);
    printf("\t\tSouth Texture: %s\n", data->south_texture);
    printf("\t\tWest Texture: %s\n", data->west_texture);
    printf("\t\tEast Texture: %s\n", data->east_texture);
    printf("\t\tFloor Color: %s\n", data->floor_color);
    printf("\t\tCeiling Color: %s\n", data->ceiling_color);
}
void print_struct(t_file_data *data) {
    printf("North Texture: %s\n", data->north_texture);
    printf("South Texture: %s\n", data->south_texture);
    printf("West Texture: %s\n", data->west_texture);
    printf("East Texture: %s\n", data->east_texture);
    printf("Floor Color: %s\n", data->floor_color);
    printf("Ceiling Color: %s\n", data->ceiling_color);
    printf("Player Spawn Direction: %s\n", data->player_spawn_direction);
    printf("Player X Coordinate: %lf\n", data->player_x);
    printf("Player Y Coordinate: %lf\n", data->player_y);
    printf("File Descriptor: %d\n", data->file_descriptor);
    printf("Return Value: %d\n", data->return_value);
    printf("Floor RGB: R(%d) G(%d) B(%d)\n", data->floor_rgb.red, data->floor_rgb.green, data->floor_rgb.blue);
    printf("Ceiling RGB: R(%d) G(%d) B(%d)\n", data->ceiling_rgb.red, data->ceiling_rgb.green, data->ceiling_rgb.blue);
    if (data->map_as_array) {
        printf("Map Content:\n");
        int i = 0;
        while (data->map_as_array[i] != NULL) {
            int j = 0;
            while (data->map_as_array[i][j] != NEW_LINE) {
                if (data->map_as_array[i][j] == EMPTY)
                    printf("%d",data->map_as_array[i][j]);
                else if (data->map_as_array[i][j] == FLOOR)
                    printf("%d",data->map_as_array[i][j]);
                else if (data->map_as_array[i][j] == WALL)
                    printf("%d",data->map_as_array[i][j]);
                j++;
            }
            printf(":%c:\n",data->map_as_array[i][j+1]);
            i++;
        }
    } else {
        printf("Map Content: (Empty)\n");
    }
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
void	print_error_message(t_return_value error)
{
	if (error == MALLOC_FAILURE)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (error == NEED_MAP_CUB_FILE)
		ft_putstr_fd("Usage: use cub file\n", 2);
	else if (error == FILE_IS_EMPTY)
		ft_putstr_fd("Error: file is empty\n", 2);
	else if (error == FILE_OPEN_FAILURE)
		ft_putstr_fd("Error: file open failure\n", 2);
	else if (error == MAP_CONTENT_NOT_VALID)
		ft_putstr_fd("Error: file content not valid\n", 2);
	else if (error == INVALID_ARGUMENT)
		ft_putstr_fd("Usage: use cub file\n", 2);
}

void	clean_up(t_file_data *data)
{
	if (data->file_content_as_string)
		free(data->file_content_as_string);

}


