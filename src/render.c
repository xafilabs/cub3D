/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:19:30 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/27 07:35:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
		mlx_put_pixel(image, x, y, color);
}

void	update_player_location(t_data *d)
{
	double	old_dir;
	double	old_plane;
	t_dvec	rot;

	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
	{
		old_dir = d->player.dir.x;
		d->player.dir.x = d->player.dir.x * cos(PLAYER_ROTATE_SPEED)
			- d->player.dir.y * sin(PLAYER_ROTATE_SPEED);
		d->player.dir.y = old_dir * sin(PLAYER_ROTATE_SPEED)
			+ d->player.dir.y * cos(PLAYER_ROTATE_SPEED);
		old_plane = d->player.plane.x;
		d->player.plane.x = d->player.plane.x * cos(PLAYER_ROTATE_SPEED)
			- d->player.plane.y * sin(PLAYER_ROTATE_SPEED);
		d->player.plane.y = old_plane * sin(PLAYER_ROTATE_SPEED)
			+ d->player.plane.y * cos(PLAYER_ROTATE_SPEED);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
	{
		old_dir = d->player.dir.x;
		d->player.dir.x = d->player.dir.x * cos(-PLAYER_ROTATE_SPEED)
			- d->player.dir.y * sin(-PLAYER_ROTATE_SPEED);
		d->player.dir.y = old_dir * sin(-PLAYER_ROTATE_SPEED)
			+ d->player.dir.y * cos(-PLAYER_ROTATE_SPEED);
		old_plane = d->player.plane.x;
		d->player.plane.x = d->player.plane.x * cos(-PLAYER_ROTATE_SPEED)
			- d->player.plane.y * sin(-PLAYER_ROTATE_SPEED);
		d->player.plane.y = old_plane * sin(-PLAYER_ROTATE_SPEED)
			+ d->player.plane.y * cos(-PLAYER_ROTATE_SPEED);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		if (d->map.content[
				(int)d->player.pos.y][
			(int)(d->player.pos.x
			+ d->player.dir.x * PLAYER_MOVE_SPEED)] == 0)
		{
			d->player.pos.x += d->player.dir.x * PLAYER_MOVE_SPEED;
		}
		if (d->map.content[
				(int)(d->player.pos.y + d->player.dir.y * PLAYER_MOVE_SPEED)][
			(int)d->player.pos.x] == 0)
		{
			d->player.pos.y += d->player.dir.y * PLAYER_MOVE_SPEED;
		}
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		if (d->map.content[
				(int)d->player.pos.y][
			(int)(d->player.pos.x
			- d->player.dir.x * PLAYER_MOVE_SPEED)] == 0)
		{
			d->player.pos.x -= d->player.dir.x * PLAYER_MOVE_SPEED;
		}
		if (d->map.content[
				(int)(d->player.pos.y - d->player.dir.y * PLAYER_MOVE_SPEED)][
			(int)d->player.pos.x] == 0)
		{
			d->player.pos.y -= d->player.dir.y * PLAYER_MOVE_SPEED;
		}
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		rot.y = d->player.dir.x * -1;
		rot.x = d->player.dir.y;
		if (d->map.content[
				(int)d->player.pos.y][
			(int)(d->player.pos.x
			+ rot.x * PLAYER_MOVE_SPEED)] == 0)
		{
			d->player.pos.x += rot.x * PLAYER_MOVE_SPEED;
		}
		if (d->map.content[
				(int)(d->player.pos.y + rot.y * PLAYER_MOVE_SPEED)][
			(int)d->player.pos.x] == 0)
		{
			d->player.pos.y += rot.y * PLAYER_MOVE_SPEED;
		}
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		rot.y = d->player.dir.x * -1;
		rot.x = d->player.dir.y;
		if (d->map.content[
				(int)d->player.pos.y][
			(int)(d->player.pos.x
			- rot.x * PLAYER_MOVE_SPEED)] == 0)
		{
			d->player.pos.x -= rot.x * PLAYER_MOVE_SPEED;
		}
		if (d->map.content[
				(int)(d->player.pos.y - rot.y * PLAYER_MOVE_SPEED)][
			(int)d->player.pos.x] == 0)
		{
			d->player.pos.y -= rot.y * PLAYER_MOVE_SPEED;
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

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

unsigned int	get_texture_pixel(mlx_texture_t *texture, unsigned int x, unsigned int y)
{
	unsigned int	color;
	unsigned int	offset;

	if (x >= texture->width || y >= texture->height)
		return (0);
	offset = ((y * texture->width) + x);
	color = ((unsigned int *)texture->pixels)[offset];
	return (convert_abgr_to_rgba(color));
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

void	init_player_dir_plane(t_data *d, int player_angle_deg, int fov_deg)
{
	double	old_dir;
	double	old_plane;

	if (fov_deg < 2 || fov_deg >= 180)
	{
		ft_putstr_fd("Error\nInvalid FOV.", 1);
		exit(1);
	}
	d->player.dir.x = 1;
	d->player.dir.y = 0;
	d->player.plane.x = 0;
	d->player.plane.y = tan(deg_to_rad((double)fov_deg / 2.0));
	player_angle_deg = (player_angle_deg - 90) % 360;
	old_dir = d->player.dir.x;
	d->player.dir.x = d->player.dir.x * cos(deg_to_rad(player_angle_deg))
		- d->player.dir.y * sin(deg_to_rad(player_angle_deg));
	d->player.dir.y = old_dir * sin(deg_to_rad(player_angle_deg))
		+ d->player.dir.y * cos(deg_to_rad(player_angle_deg));
	old_plane = d->player.plane.x;
	d->player.plane.x = d->player.plane.x * cos(deg_to_rad(player_angle_deg))
		- d->player.plane.y * sin(deg_to_rad(player_angle_deg));
	d->player.plane.y = old_plane * sin(deg_to_rad(player_angle_deg))
		+ d->player.plane.y * cos(deg_to_rad(player_angle_deg));
}

void	set_ray_texture(t_data	*d, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			ray->texture = d->texture.east;
		else
			ray->texture = d->texture.west;
	}
	else
	{
		if (ray->dir.y < 0)
			ray->texture = d->texture.south;
		else
			ray->texture = d->texture.north;
	}
}

void	draw_texture(t_data *d, t_ray *ray, int x)
{
	int				y;
	double			step;
	double			tex_start_pos;
	unsigned int	color;

	set_ray_texture(d, ray);
	ray->tex_pos.x = (int)(ray->wall_hit_dec * (double)ray->texture->width);
	if (ray->side == 0 && ray->dir.x < 0)
		ray->tex_pos.x = ray->texture->width - ray->tex_pos.x - 1;
	if (ray->side == 1 && ray->dir.y > 0)
		ray->tex_pos.x = ray->texture->width - ray->tex_pos.x - 1;
	step = 1.0 * ray->texture->height / ray->line_height;
	tex_start_pos = (ray->draw_start
			- WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_pos.y = (int)tex_start_pos & (ray->texture->height - 1);
		tex_start_pos += step;
		color = get_texture_pixel(ray->texture, ray->tex_pos.x, ray->tex_pos.y);
		put_pixel(d->img, x, y, color);
		y++;
	}
}

void	cast_rays(t_data *d)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray.cam_x = 2 * x / (double)WINDOW_WIDTH - 1;
		ray.dir.x = d->player.dir.x + d->player.plane.x * ray.cam_x;
		ray.dir.y = d->player.dir.y + d->player.plane.y * ray.cam_x;
		ray.map.x = (int)d->player.pos.x;
		ray.map.y = (int)d->player.pos.y;
		ray.delta_dist.x = HUGE_NUMBER;
		if (ray.dir.x != 0)
			ray.delta_dist.x = fabs(1 / ray.dir.x);
		ray.delta_dist.y = HUGE_NUMBER;
		if (ray.dir.y != 0)
			ray.delta_dist.y = fabs(1 / ray.dir.y);
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (d->player.pos.x - ray.map.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (ray.map.x + 1.0 - d->player.pos.x)
				* ray.delta_dist.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (d->player.pos.y - ray.map.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (ray.map.y + 1.0 - d->player.pos.y)
				* ray.delta_dist.y;
		}
		ray.hit = 0;
		while (!ray.hit)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.map.x += ray.step.x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.map.y += ray.step.y;
				ray.side = 1;
			}
			if (d->map.content[ray.map.y][ray.map.x] > 0)
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.normal_wall_distance = ray.side_dist.x - ray.delta_dist.x;
		else
			ray.normal_wall_distance = ray.side_dist.y - ray.delta_dist.y;
		ray.line_height = (int)(WINDOW_HEIGHT / ray.normal_wall_distance);
		ray.draw_start = -ray.line_height / 2 + WINDOW_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WINDOW_HEIGHT / 2;
		if (ray.draw_end >= WINDOW_HEIGHT)
			ray.draw_end = WINDOW_HEIGHT - 1;
		if (ray.side == 0)
			ray.wall_hit_dec = d->player.pos.y + ray.normal_wall_distance
				* ray.dir.y;
		else
			ray.wall_hit_dec = d->player.pos.x + ray.normal_wall_distance
				* ray.dir.x;
		ray.wall_hit_dec -= floor(ray.wall_hit_dec);
		draw_texture(d, &ray, x);
		x++;
	}
}

void	render(t_data *d)
{
	render_ceiling_floor(d);
	cast_rays(d);
}
