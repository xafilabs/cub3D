/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_movement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:47:12 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/28 14:48:01 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

// int left_right, 0 for left, 1 for right
static void	rotate_vectors_dir_plane(t_data *d, int left_right)
{
	double	rot_speed;
	double	old_dir;
	double	old_plane;

	rot_speed = PLAYER_ROTATE_SPEED;
	if (left_right == 0)
		rot_speed *= -1;
	old_dir = d->player.dir.x;
	d->player.dir.x = d->player.dir.x * cos(rot_speed)
		- d->player.dir.y * sin(rot_speed);
	d->player.dir.y = old_dir * sin(rot_speed)
		+ d->player.dir.y * cos(rot_speed);
	old_plane = d->player.plane.x;
	d->player.plane.x = d->player.plane.x * cos(rot_speed)
		- d->player.plane.y * sin(rot_speed);
	d->player.plane.y = old_plane * sin(rot_speed)
		+ d->player.plane.y * cos(rot_speed);
}

// int direction 1 for moving in positive direction
// -1 for moving in negative direction
static void	move_player_in_direction_parallel(t_data *d, int direction)
{
	if (d->map.content[(int)d->player.pos.y]
		[(int)(d->player.pos.x
			+ direction * d->player.dir.x * PLAYER_MOVE_SPEED)] == 0)
	{
		d->player.pos.x += direction * d->player.dir.x * PLAYER_MOVE_SPEED;
	}
	if (d->map.content[(int)(d->player.pos.y
			+ direction * d->player.dir.y * PLAYER_MOVE_SPEED)]
			[(int)d->player.pos.x] == 0)
	{
		d->player.pos.y += direction * d->player.dir.y * PLAYER_MOVE_SPEED;
	}
}

// int direction 1 for moving in positive direction
// -1 for moving in negative direction
static void	move_player_in_direction_perpendicular(t_data *d, int direction)
{
	t_dvec	rot;

	rot.y = d->player.dir.x * -1;
	rot.x = d->player.dir.y;
	if (d->map.content[(int)d->player.pos.y]
		[(int)(d->player.pos.x
			+ direction * rot.x * PLAYER_MOVE_SPEED)] == 0)
	{
		d->player.pos.x += direction * rot.x * PLAYER_MOVE_SPEED;
	}
	if (d->map.content[(int)(d->player.pos.y
			+ direction * rot.y * PLAYER_MOVE_SPEED)]
			[(int)d->player.pos.x] == 0)
	{
		d->player.pos.y += direction * rot.y * PLAYER_MOVE_SPEED;
	}
}

void	update_player_location(t_data *d)
{
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
		rotate_vectors_dir_plane(d, 0);
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
		rotate_vectors_dir_plane(d, 1);
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		move_player_in_direction_parallel(d, POSITIVE);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		move_player_in_direction_parallel(d, NEGATIVE);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		move_player_in_direction_perpendicular(d, POSITIVE);
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		move_player_in_direction_perpendicular(d, NEGATIVE);
	}
}
