/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:58:02 by malaakso          #+#    #+#             */
/*   Updated: 2023/11/02 17:28:27 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static t_return_value	validate_one_texture(mlx_texture_t *texture)
{
	if (texture->height != texture->width)
	{
		ft_putstr_fd("Error\nTexture is not square\n", 2);
		return (FAILURE);
	}
	if (texture->height < TEXTURE_SIZE_MIN
		|| texture->height > TEXTURE_SIZE_MAX)
	{
		ft_putstr_fd("Error\nTexture is not between ", 2);
		ft_putnbr_fd(TEXTURE_SIZE_MIN, 2);
		ft_putstr_fd(" and ", 2);
		ft_putnbr_fd(TEXTURE_SIZE_MAX, 2);
		ft_putstr_fd(" pixels in side length", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	validate_textures(t_data *render_data)
{
	int	failure_total;

	failure_total = 0;
	failure_total += (int)validate_one_texture(render_data->texture.north);
	failure_total += (int)validate_one_texture(render_data->texture.east);
	failure_total += (int)validate_one_texture(render_data->texture.south);
	failure_total += (int)validate_one_texture(render_data->texture.west);
	if (failure_total > 0)
		clean_exit(render_data, EXIT_FAILURE);
}
