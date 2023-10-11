/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:29:06 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/11 18:11:04 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"


t_return_value	validate_cub_and_map_file(t_file_data *data, const char **path_to_file)
{
	char *temp;

	if (check_file_type(data, path_to_file) == SUCCESS)
	 {
		get_file_content_to_string(data, path_to_file);
		printf("%s\n", data->file_content_as_string);
		temp = ft_strtrim(data->file_content_as_string, " \t\v\f\r\n");
		free (data->file_content_as_string);
		data->file_content_as_string = temp;
		printf("After trimming:\n%s\n", data->file_content_as_string);
		//if (file_contains_data(data) != FILE_IS_EMPTY
	 }
	//if (data->return_value == SUCCESS)
		//validate_scene_requirement(data);

	return (data->return_value);
}
/**
 * @brief The main function of the cub3D program.
 *
 * This function handles command-line arguments, initializes the necessary data
 * structures,
	and performs file and map validation for the scene description file.
 * If the validation is successful, it can proceed to initialize the game and
 * execute the main game loop.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @return An exit code indicating the program's success or failure.
 */
int	main(int argc, char **argv)
{
	t_file_data		file_data;

	if (argc != 2)
	{
		printf("usage: ./cube3d map.cub\n");
		exit(NEED_MAP_CUB_FILE);
	}
	initialize_struct(&file_data);
	file_data.return_value = SUCCESS;
	validate_cub_and_map_file(&file_data, (const char **)argv);
	//initialize_game();
	if (file_data.return_value != SUCCESS)
	 	print_error_message(file_data.return_value);
	clean_up(&file_data);
	return (file_data.return_value);
}

