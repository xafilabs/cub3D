/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   migration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:22:21 by malaakso          #+#    #+#             */
/*   Updated: 2023/11/02 15:06:08 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	migrate_player_direction(t_file_data *file_data, t_data *render_data)
{
	int	degrees;

	degrees = 0;
	if (file_data->player_spawn_direction[0] == 'N')
		degrees = 0;
	else if (file_data->player_spawn_direction[0] == 'E')
		degrees = 90;
	else if (file_data->player_spawn_direction[0] == 'S')
		degrees = 180;
	else if (file_data->player_spawn_direction[0] == 'W')
		degrees = 270;
	init_player_dir_plane(render_data, degrees, PLAYER_FOV);
}

static unsigned int
	migrate_colors_to_rgba(
		unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	exit_parsing(t_file_data *file_data, int return_value)
{
	print_parsing_error_message(return_value);
	clean_up_parsing(file_data);
	exit(EXIT_FAILURE);
}

void
	exit_mlx_parsing(t_file_data *file_data, t_data	*render_data,
		int return_value, mlx_t *mlx)
{
	mlx_terminate(mlx);
	free_cub3d_textures(render_data);
	exit_parsing(file_data, return_value);
}

void	migrate_colors(t_file_data *file_data, t_data *render_data)
{
	render_data->color.floor = migrate_colors_to_rgba(
			(unsigned int)file_data->floor_rgb.red,
			(unsigned int)file_data->floor_rgb.green,
			(unsigned int)file_data->floor_rgb.blue, 255);
	render_data->color.ceiling = migrate_colors_to_rgba(
			(unsigned int)file_data->ceiling_rgb.red,
			(unsigned int)file_data->ceiling_rgb.green,
			(unsigned int)file_data->ceiling_rgb.blue, 255);
}
