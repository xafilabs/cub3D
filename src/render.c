/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:19:30 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/22 15:47:53 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		mlx_put_pixel(image, x, y, color);
	else
		printf("Warning: Putting pixels outside screen to x:y=%i:%i\n", x, y);
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

int	is_coordinate_in_wall(int **map, double x, double y)
{
	if (map[(int)floor(y)][(int)floor(x)] == 1)
		return (TRUE);
	return (FALSE);
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
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		d->player.angle -= PLAYER_ROTATE_SPEED;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		d->player.angle += PLAYER_ROTATE_SPEED;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		d->player.move_cos = cos(deg_to_rad(d->player.angle))
			* PLAYER_MOVE_SPEED;
		d->player.move_sin = sin(deg_to_rad(d->player.angle))
			* PLAYER_MOVE_SPEED;
		if (!is_coordinate_in_wall(d->map.content,
				d->player.x + (d->player.move_cos + WALL_MIN_DISTANCE),
				d->player.y + (d->player.move_sin + WALL_MIN_DISTANCE)))
		{
			d->player.x += d->player.move_cos;
			d->player.y += d->player.move_sin;
		}
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		d->player.move_cos = cos(deg_to_rad(d->player.angle))
			* PLAYER_MOVE_SPEED;
		d->player.move_sin = sin(deg_to_rad(d->player.angle))
			* PLAYER_MOVE_SPEED;
		if (!is_coordinate_in_wall(d->map.content,
				d->player.x - (d->player.move_cos + WALL_MIN_DISTANCE),
				d->player.y - (d->player.move_sin + WALL_MIN_DISTANCE)))
		{
			d->player.x -= d->player.move_cos;
			d->player.y -= d->player.move_sin;
		}
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		d->player.move_cos = cos(deg_to_rad(d->player.angle + 90))
			* PLAYER_MOVE_SPEED;
		d->player.move_sin = sin(deg_to_rad(d->player.angle + 90))
			* PLAYER_MOVE_SPEED;
		if (!is_coordinate_in_wall(d->map.content,
				d->player.x + (d->player.move_cos + WALL_MIN_DISTANCE),
				d->player.y + (d->player.move_sin + WALL_MIN_DISTANCE)))
		{
			d->player.x += d->player.move_cos;
			d->player.y += d->player.move_sin;
		}
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		d->player.move_cos = cos(deg_to_rad(d->player.angle + 90))
			* PLAYER_MOVE_SPEED;
		d->player.move_sin = sin(deg_to_rad(d->player.angle + 90))
			* PLAYER_MOVE_SPEED;
		if (!is_coordinate_in_wall(d->map.content,
				d->player.x - (d->player.move_cos + WALL_MIN_DISTANCE),
				d->player.y - (d->player.move_sin + WALL_MIN_DISTANCE)))
		{
			d->player.x -= d->player.move_cos;
			d->player.y -= d->player.move_sin;
		}
	}
}

void	loop_hook(void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	render(d);
}

static void	render_minimap_background(t_data *d)
{
	int	i;
	int	j;

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
}

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	rad_to_deg(double radians)
{
	return (radians * 180.0 / M_PI);
}

void	render_minimap(t_data *d)
{
	render_minimap_background(d);
	// Render a map grid
	
}

void	cast_rays(t_data *d)
{
	int		ray_count;
	t_ray	ray;
	double	ray_sin;
	double	ray_cos;
	int		wall;
	double	wall_distance;
	double	wall_height;

	d->ray_angle = d->player.angle - PLAYER_HALF_FOV;
	ray_count = 0;
	while (ray_count < RAY_LIMIT)
	{
		ray.x = d->player.x;
		ray.y = d->player.y;
		ray_sin = sin(deg_to_rad(d->ray_angle)) / RAY_PRECISION;
		ray_cos = cos(deg_to_rad(d->ray_angle)) / RAY_PRECISION;
		wall = 0;
		while (!wall)
		{
			ray.x += ray_cos;
			ray.y += ray_sin;
			wall = d->map.content[(int)floor(ray.y)][(int)floor(ray.x)];
		}
		wall_distance = sqrt(pow(d->player.x - ray.x, 2) + pow(d->player.y - ray.y, 2));
		wall_distance = wall_distance * cos(deg_to_rad(d->ray_angle - d->player.angle));
		wall_height = floor(WINDOW_HALF_HEIGHT / wall_distance);
		if (wall_height > WINDOW_HALF_HEIGHT)
			wall_height = WINDOW_HALF_HEIGHT;
		draw_line(d->img, new_point(ray_count, 0), new_point(ray_count, WINDOW_HALF_HEIGHT - wall_height), COLOR_BLUE);
		draw_line(d->img, new_point(ray_count, WINDOW_HALF_HEIGHT - wall_height), new_point(ray_count, WINDOW_HALF_HEIGHT + wall_height), COLOR_RED);
		draw_line(d->img, new_point(ray_count, WINDOW_HALF_HEIGHT + wall_height), new_point(ray_count, WINDOW_HEIGHT), COLOR_GREEN);
		d->ray_angle += (double)RAY_INCREMENT;
		ray_count++;
	}
}

void	render(t_data *d)
{
	cast_rays(d);
	//render_minimap(d);
	(void)d;
}
