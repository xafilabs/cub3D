/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:19:30 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/28 12:19:02 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

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
	exit(EXIT_SUCCESS);
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
	while (y <= ray->draw_end)
	{
		ray->tex_pos.y = (int)tex_start_pos & (ray->texture->height - 1);
		tex_start_pos += step;
		color = get_texture_pixel(ray->texture, ray->tex_pos.x, ray->tex_pos.y);
		put_pixel(d->img, x, y, color);
		y++;
	}
}

void	render(t_data *d)
{
	render_ceiling_floor(d);
	cast_rays(d);
}
