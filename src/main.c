/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:29:06 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/04 15:45:18 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/utils.h"



/**
 * @brief The main function of the cub3D program.
 *
 * This function handles command-line arguments, initializes the necessary data
 * structures, and performs file and map validation for the scene description file.
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
	t_return_value	return_value;

	return_value = SUCCESS;
	if (argc != 2)
	{
		printf("usage: ./cube3d map.cub\n");
		exit (NEED_MAP_CUB_FILE);
	}
	initialize_struct(&file_data);
	return_value = validate_cub_file(&file_data, argv);
	return_value = validate_map_scene(&file_data);
//	initialize_game();
//	clean_up();
	return(return_value);
}

