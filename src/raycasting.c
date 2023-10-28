/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:18:42 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/28 12:51:19 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static void	perform_dda(t_data *d, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (d->map.content[ray->map.y][ray->map.x] > 0)
			ray->hit = 1;
	}
}

static void	calculate_wall_line_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->normal_wall_distance = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->normal_wall_distance = ray->side_dist.y - ray->delta_dist.y;
	ray->line_height = (int)(WINDOW_HEIGHT / ray->normal_wall_distance);
}

static void	calculate_wall_start_end_pixels(t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

static void	calculate_wall_hit_decimal(t_data *d, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_hit_dec = d->player.pos.y + ray->normal_wall_distance
			* ray->dir.y;
	else
		ray->wall_hit_dec = d->player.pos.x + ray->normal_wall_distance
			* ray->dir.x;
	ray->wall_hit_dec -= floor(ray->wall_hit_dec);
}

void	cast_rays(t_data *d)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_base_values(d, &ray, x);
		init_ray_delta(&ray);
		init_ray_side_distance(d, &ray);
		perform_dda(d, &ray);
		calculate_wall_line_height(&ray);
		calculate_wall_start_end_pixels(&ray);
		calculate_wall_hit_decimal(d, &ray);
		draw_texture(d, &ray, x);
		x++;
	}
}
