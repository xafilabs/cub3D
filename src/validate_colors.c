/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:46:38 by malaakso          #+#    #+#             */
/*   Updated: 2023/11/03 16:20:03 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	contains_two_commas(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count == 2)
		return (1);
	return (0);
}

t_return_value	validate_color_strings(t_file_data *data)
{
	if (!contains_two_commas(data->ceiling_color)
		|| !contains_two_commas(data->floor_color))
	{
		data->return_value = INVALID_COLORS;
		return (INVALID_COLORS);
	}
	return (SUCCESS);
}
