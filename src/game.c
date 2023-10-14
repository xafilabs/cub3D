/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:19:30 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/14 18:35:38 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	draw_line(mlx_image_t *image, t_line line)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	x = line.x0;
	y = line.y0;
	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	p = 2 * dy - dx;
	while (1)
	{
		mlx_put_pixel(image, x, y, line.color);
		if (x == line.x1 && y == line.y1)
			break ;
		if (p >= 0)
		{
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

void	loop_hook(void *data_param)
{
	t_data	*d;

	d = (t_data *)data_param;
	game(d);
}

void	game(t_data *d)
{
	(void)d;
}
