/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:21:07 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/28 16:56:42 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	ret_grid_len(char **grid)
{
	int	i;

	if (!grid)
		return (-1);
	i = 0;
	while (grid[i])
		i++;
	return (i);
}

static t_bool	is_valid_color_value(int color)
{
	if (color >= 0 && color < 256)
		return (TRUE);
	return (FALSE);
}

static t_color	ret_colors(t_file_data *data, char **rgb)
{
	t_color	colors;
	int		valid_colors;

	colors.red = 0;
	colors.green = 0;
	colors.blue = 0;
	if (ret_grid_len(rgb) != 3)
	{
		data->return_value = INVALID_COLORS;
		return (colors);
	}
	colors.red = ft_atoi(rgb[0]);
	colors.green = ft_atoi(rgb[1]);
	colors.blue = ft_atoi(rgb[2]);
	valid_colors = 0;
	valid_colors += is_valid_color_value(colors.red);
	valid_colors += is_valid_color_value(colors.green);
	valid_colors += is_valid_color_value(colors.blue);
	if (valid_colors < 3)
		data->return_value = INVALID_COLORS;
	return (colors);
}

static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

t_return_value	get_rgb_colors(t_file_data *data)
{
	char	**ceiling_colors;
	char	**floor_colors;

	ceiling_colors = ft_split(data->ceiling_color, ',');
	if (!ceiling_colors)
	{
		data->return_value = MALLOC_FAILURE;
		return (data->return_value);
	}
	data->ceiling_rgb = ret_colors(data, ceiling_colors);
	free_grid(ceiling_colors);
	if (data->return_value != SUCCESS)
		return (data->return_value);
	floor_colors = ft_split(data->floor_color, ',');
	if (!floor_colors)
	{
		data->return_value = MALLOC_FAILURE;
		return (data->return_value);
	}
	data->floor_rgb = ret_colors(data, floor_colors);
	free_grid(floor_colors);
	return (data->return_value);
}
