/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:29:06 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/14 18:38:22 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"


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
	t_data			d;
	int				i;
	int				j;
	mlx_image_t		*img;
	t_line			line;

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
	d.map.content[5][5] = 1;
	d.map.content[5][7] = 1;
	d.player.x = 3;
	d.player.y = 3;
	d.player.angle = 180;
	d.player.fov = 60;
	d.screen.height = WINDOW_HEIGHT;
	d.screen.width = WINDOW_WIDTH;
	d.screen.refresh_rate = 60;
	d.raycast.increment_angle = 0;
	d.raycast.precision = 1;
	d.mlx = mlx_init(d.screen.width, d.screen.height, "cub3D", false);
	if (!d.mlx)
		return (EXIT_FAILURE);
	img = mlx_new_image(d.mlx, d.screen.width, d.screen.height);
	if (!img || (mlx_image_to_window(d.mlx, img, 0, 0) < 0))
		exit(EXIT_FAILURE);
	mlx_put_pixel(img, 100, 100, 0x98FB98FF);
	line.color = 0x90FD90FF;
	line.x0 = 151;
	line.y0 = 144;
	line.x1 = 355;
	line.y1 = 349;
	draw_line(img, line);
	game(&d); //this is the draw/redraw function
	mlx_loop_hook(d.mlx, loop_hook, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	i = 0;
	while (i < d.map.height)
	{
		free(d.map.content[i]);
		i++;
	}
	free(d.map.content);
	return (0);
}

