/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   migration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:22:21 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/28 17:01:27 by malaakso         ###   ########.fr       */
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

unsigned int
	migrate_colors_to_rgba(
		unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
