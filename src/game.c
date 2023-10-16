/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:19:30 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/16 17:52:54 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	assert(x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT);
	mlx_put_pixel(image, x, y, color);
}

t_point	new_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	draw_line(mlx_image_t *image, t_point start, t_point end, int color)
{
	t_point	delta;
	t_point	sign;
	t_point	idx;
	int		err[2];

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	sign.x = -1;
	if (start.x < end.x)
		sign.x = 1;
	sign.y = -1;
	if (start.y < end.y)
		sign.y = 1;
	err[0] = delta.x - delta.y;
	idx = start;
	while (idx.x != end.x || idx.y != end.y)
	{
		put_pixel(image, idx.x, idx.y, color);
		err[1] = err[0] * 2;
		if (err[1] > -delta.y)
		{
			err[0] -= delta.y;
			idx.x += sign.x;
		}
		if (err[1] < delta.x)
		{
			err[0] += delta.x;
			idx.y += sign.y;
		}
	}
}

void	clean_exit(t_data *d)
{
	int		i;

	printf("Exit called, cleaning up!\n");
	mlx_terminate(d->mlx);
	if (d->map.content)
	{
		i = 0;
		while (i < d->map.height)
		{
			if (d->map.content[i])
				free(d->map.content[i]);
			i++;
		}
		free(d->map.content);
	}
	// delete d->texture.north .east .south .west
	// void mlx_delete_texture(mlx_texture_t* texture); for png
	// void mlx_delete_xpm42(xpm_t* xpm); for xpm
	exit(0);
}

void	close_hook(void *data_param)
{
	t_data	*d;

	printf("Caught close hook!\n");
	d = (t_data *)data_param;
	clean_exit(d);
}

void	key_hook(mlx_key_data_t keydata, void *data_param)
{
	t_data	*d;

	printf("Caught key hook! (%i)\n", keydata.key);
	d = (t_data *)data_param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(d);
}

void	loop_hook(void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	//game(d);
}

void	render_minimap(t_data *d)
{
	float	i;
	float	j;

	// Render background for the minimap
	i = 0;
	while (i < MINIMAP_HEIGHT)
	{
		j = 0;
		while (j < MINIMAP_WIDTH)
		{
			put_pixel(d->img, j, i, COLOR_WHITE);
			j++;
		}
		i++;
	}
	// Render a map grid
	
}

void	game(t_data *d)
{
	render_minimap(d);
	(void)d;
}
