/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:29:06 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/27 17:38:17 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static t_return_value
	validate_cub_and_map_file(t_file_data *data, const char **path_to_file)
{
	char	*temp;

	if (check_file_type(data, path_to_file) == SUCCESS)
	{
		get_file_content_to_string(data, path_to_file);
		temp = ft_strtrim(data->file_content_as_string, " \t\v\f\r\n");
		free (data->file_content_as_string);
		data->file_content_as_string = ft_strdup(temp);
		free (temp);
		printf("After trimming:\n%s\n", data->file_content_as_string);
	}
	if (data->return_value == SUCCESS)
		validate_scene_requirement(data);
	return (data->return_value);
}

static void	parsing_main(t_file_data *file_data, char **argv)
{
	initialize_struct(file_data);
	file_data->return_value = SUCCESS;
	validate_cub_and_map_file(file_data, (const char **)argv);
	if (file_data->return_value != SUCCESS)
	{
		print_parsing_error_message(file_data->return_value);
		clean_up_parsing(file_data);
		exit(1);
	}
}

static t_return_value
	migrate_data_file_to_render(t_file_data *file_data, t_data *render_data)
{
	// What is missing:
	// color unsigned int for floor and ceiling
	render_data->texture.north = mlx_load_png(file_data->north_texture);
	if (!render_data->texture.north)
		return (FAILURE);
	render_data->texture.east = mlx_load_png(file_data->east_texture);
	if (!render_data->texture.east)
		return (FAILURE);
	render_data->texture.south = mlx_load_png(file_data->south_texture);
	if (!render_data->texture.south)
		return (FAILURE);
	render_data->texture.west = mlx_load_png(file_data->west_texture);
	if (!render_data->texture.west)
		return (FAILURE);
	render_data->map.height = file_data->map_number_of_lines;
	render_data->map.width = file_data->max_map_width;
	render_data->map.content = (int **)file_data->map_as_array;
	render_data->player.pos.x = file_data->player_x + 0.5;
	render_data->player.pos.y = file_data->player_y + 0.5;
	migrate_player_direction(file_data, render_data);
	//PLACEHOLDERS START (assuming maps/good/malaakso_verysimple.cub)
	render_data->color.floor = COLOR_GREEN;
	render_data->color.ceiling = COLOR_BLUE;
	//PLACEHOLDERS END
	return (SUCCESS);
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
	t_data			render_data;
	t_file_data		file_data;

	(void)argv;
	if (argc != 2)
	{
		printf("usage: ./cube3d map.cub\n");
		exit(NEED_MAP_CUB_FILE);
	}
	parsing_main(&file_data, argv);
	render_data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!render_data.mlx)
		return (EXIT_FAILURE);
	render_data.img = mlx_new_image(
			render_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!render_data.img)
		exit(EXIT_FAILURE);
	if (migrate_data_file_to_render(&file_data, &render_data) == FAILURE)
	{
		clean_up_parsing(&file_data);
		exit(1);
	}
	if (mlx_image_to_window(render_data.mlx, render_data.img, 0, 0) < 0)
		exit(EXIT_FAILURE);
	mlx_loop_hook(render_data.mlx, loop_hook, &render_data);
	mlx_close_hook(render_data.mlx, close_hook, &render_data);
	mlx_key_hook(render_data.mlx, key_hook, &render_data);
	mlx_loop(render_data.mlx);
	clean_exit(&render_data);
	return (EXIT_SUCCESS);
}
