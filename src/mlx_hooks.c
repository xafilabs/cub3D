/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:37:57 by malaakso          #+#    #+#             */
/*   Updated: 2023/11/02 13:27:02 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	loop_hook(void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	update_player_location(d);
	render(d);
}

void	key_hook(mlx_key_data_t keydata, void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(d, EXIT_SUCCESS);
}

void	close_hook(void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	clean_exit(d, EXIT_SUCCESS);
}
