/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:19:30 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/24 17:58:26 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
		mlx_put_pixel(image, x, y, color);
	// else
	// 	printf("Warning: Putting pixels outside screen to x:y=%i:%i\n", x, y);
}

t_point	new_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	draw_line(mlx_image_t *image, t_point start, t_point end, unsigned int color)
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
		// if (idx.x < 0 || idx.x >= WINDOW_WIDTH || idx.y < 0 || idx.y >= WINDOW_HEIGHT)
		// {
		// 	//printf("Warning: an attempt was made to draw a line at least partially outside the window.\n");
		// 	return ;
		// }
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

//draw_vertical_strip() would be good to implement

int	is_coordinate_in_wall(int **map, double x, double y)
{
	if (map[(int)floor(y)][(int)floor(x)] == 1)
		return (TRUE);
	return (FALSE);
}

void	update_player_location(t_data *d)
{
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		d->player.angle -= PLAYER_ROTATE_SPEED;
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		d->player.angle += PLAYER_ROTATE_SPEED;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
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
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
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
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
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
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
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

	d = (t_data *)data_param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(d);
}

void	loop_hook(void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	update_player_location(d);
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
// Will return rgba encoded int, or 0 for failure.
unsigned int	get_image_pixel(mlx_image_t *image, unsigned int x, unsigned int y)
{
	unsigned int	color;
	unsigned int	offset;

	if (x >= image->width || y >= image->height)
		return (0);
	offset = ((y * image->width) + x);
	color = ((unsigned int *)image->pixels)[offset];
	return (color);
}

// unsigned int	get_image_pixel(mlx_image_t *image, unsigned int x, unsigned int y)
// {
// 	unsigned int	dst;

// 	if (x >= image->width || y >= image->height)
// 		return (COLOR_RED);
// 	dst = *(unsigned int *)(image->pixels + (y * image->width + x));
// 	return (dst);
// }

unsigned int	get_texture_pixel(mlx_texture_t *texture, unsigned int x, unsigned int y)
{
	unsigned int	dst;

	if (x >= texture->width || y >= texture->height)
		return (COLOR_RED);
	dst = *(unsigned int *)(texture->pixels + (y * texture->width + x)); // * (texture->bytes_per_pixel / 8)
	return (dst);
}

void	render_minimap(t_data *d)
{
	render_minimap_background(d);
	// Render a map grid
	
}

void	draw_texture(t_data *d, int x, int wall_height, t_ray ray)
{
	double			y_inc;
	double			y;
	unsigned int	i;
	unsigned int	color;
	int				texture_x_pos;

	ray.texture = d->texture.north;
	texture_x_pos = ray.texture->width * (ray.x + ray.y);
	texture_x_pos = (int)floor(texture_x_pos) % ray.texture->width;
	y_inc = (wall_height * 2) / ray.texture->height;
	y = WINDOW_HALF_HEIGHT - wall_height;
	i = 0;
	while (i < ray.texture->height)
	{
		color = get_image_pixel(ray.texture, texture_x_pos, i);
		draw_line(d->img, new_point(x, y), new_point(x, y + y_inc), color);
		y = y + y_inc;
		i++;
	}
}

void	render_ceiling_floor(t_data *d)
{
	size_t	i;

	i = 0;
	while (i < (WINDOW_WIDTH * WINDOW_HEIGHT))
	{
		if (i < ((WINDOW_WIDTH * WINDOW_HEIGHT) / 2))
			mlx_put_pixel(d->img, i, 0, COLOR_BLUE);
		else
			mlx_put_pixel(d->img, i, 0, COLOR_GREEN);
		i++;
	}
}

void	cast_rays(t_data *d)
{
	int				ray_count;
	t_ray			ray;
	double			ray_sin;
	double			ray_cos;
	double			wall_distance;
	double			wall_height;

	d->ray_angle = d->player.angle - PLAYER_HALF_FOV;
	ray_count = 0;
	while (ray_count < RAY_LIMIT)
	{
		ray.x = d->player.x;
		ray.y = d->player.y;
		ray_sin = sin(deg_to_rad(d->ray_angle)) / RAY_PRECISION;
		ray_cos = cos(deg_to_rad(d->ray_angle)) / RAY_PRECISION;
		while (d->map.content[(int)floor(ray.y)][(int)floor(ray.x)] == 0)
		{
			ray.x += ray_cos;
			if (d->map.content[(int)floor(ray.y)][(int)floor(ray.x)] == 0)
				ray.y += ray_sin;
		}
		wall_distance = sqrt(pow(d->player.x - ray.x, 2) + pow(d->player.y - ray.y, 2));
		wall_distance = wall_distance * cos(deg_to_rad(d->ray_angle - d->player.angle));
		wall_height = floor(WINDOW_HALF_HEIGHT / wall_distance);
		//if (wall_height > WINDOW_HALF_HEIGHT)
		//	wall_height = WINDOW_HALF_HEIGHT;
		// determine texture: north, south, east, west
		// determine x position of the texture to draw
		//draw_line(d->img, new_point(ray_count, WINDOW_HALF_HEIGHT - wall_height), new_point(ray_count, WINDOW_HALF_HEIGHT + wall_height), COLOR_RED);
		draw_texture(d, ray_count, wall_height, ray);
		d->ray_angle += (double)RAY_INCREMENT;
		ray_count++;
	}
}

void	render(t_data *d)
{
	render_ceiling_floor(d);
	cast_rays(d);
	printTextureFromImage(100, 100, d);
	printTextureFromTexture(100, 300, d);
	mlx_image_to_window(d->mlx, d->texture.north, WINDOW_HALF_WIDTH, WINDOW_HALF_HEIGHT);
	//render_minimap(d);
}
