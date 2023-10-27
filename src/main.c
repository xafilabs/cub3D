/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:29:06 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/27 07:37:57 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"


t_return_value	validate_cub_and_map_file(t_file_data *data, const char **path_to_file)
{
	char *temp;

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
	t_data			d;
	int				i;
	int				j;

	(void)argv;
	if (argc != 2)
	{
		printf("usage: ./cube3d map.cub\n");
		exit(NEED_MAP_CUB_FILE);
	}
	d.map.height = 10;
	d.map.width = 10;
	d.map.content = malloc(sizeof(int*) * d.map.height);
	if (!d.map.content)
		return (EXIT_FAILURE);
	i = 0;
	while (i < d.map.height)
	{
		d.map.content[i] = malloc(sizeof(int) * d.map.width);
		if (!d.map.content[i])
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < d.map.height)
	{
		j = 0;
		while (j < d.map.width)
		{
			if (i == 0 || j == 0 || i == d.map.height - 1 || j == d.map.width - 1)
				d.map.content[i][j] = 1;
			else
				d.map.content[i][j] = 0;
			j++;
		}
		i++;
	}
	d.map.content[5][7] = 1;
	d.map.content[5][3] = 1;
	d.map.content[6][2] = 1;
	d.player.pos.x = 3;
	d.player.pos.y = 3;
	init_player_dir_plane(&d, 0, PLAYER_FOV);
	d.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!d.mlx)
		return (EXIT_FAILURE);
	d.img = mlx_new_image(d.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!d.img)
		exit(EXIT_FAILURE);
	if (mlx_image_to_window(d.mlx, d.img, 0, 0) < 0)
		exit(EXIT_FAILURE);
	d.texture.north = mlx_load_png("textures/brick.png");
	d.texture.east = mlx_load_png("textures/grass.png");
	d.texture.south = mlx_load_png("textures/wood.png");
	d.texture.west = mlx_load_png("textures/checker.png");
	d.color.ceiling = COLOR_BLUE;
	d.color.floor = COLOR_GRAY;
	if (!d.texture.north)
		exit(EXIT_FAILURE);
	mlx_loop_hook(d.mlx, loop_hook, &d);
	mlx_close_hook(d.mlx, close_hook, &d);
	mlx_key_hook(d.mlx, key_hook, &d);
	mlx_loop(d.mlx);
	clean_exit(&d);
	return (EXIT_SUCCESS);
}
