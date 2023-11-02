/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:29:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/11/02 15:03:28 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	free_cub3d_textures(t_data *d)
{
	if (!d)
		return ;
	if (d->texture.north)
		free(d->texture.north);
	if (d->texture.east)
		free(d->texture.east);
	if (d->texture.south)
		free(d->texture.south);
	if (d->texture.west)
		free(d->texture.west);
}

void	free_file_data_not_map(t_file_data *data)
{
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
}
