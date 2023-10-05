/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:17:58 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/05 14:11:48by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static	t_bool is_file_valid(t_file_data *data, int file_descriptor, char **path)
{

	file_descriptor = open(path[1], _RDONLY);
	if (file_descriptor == -1)
	 {
		data->return_value == FILE_NOT_VALID;
		return (FALSE);
	 }
	return (TRUE);
}

static t_return_value	read_cub_file_to_string(t_file_data *data, const char **path)
{
	int		file_descriptor;
	char	*line;
	char	*temp;

	if (is_file_valid(data, &file_descriptor, path) == FALSE)
		return (data->return_value);
	while



	
	close(file_descriptor);
	return (data->return_value);
}

static t_return_value	check_file_type(t_file_data *data, const char **path_to_file)
{
	const char	*path;
	char		*last_4_chars;
	size_t		length;

	path = path_to_file[1];
	last_4_chars = NULL;
	if (*path != '\0')
	{
		length = ft_strlen(path);
		last_4_chars = ft_substr(path, length - 4, 4);
		if (ft_strncmp(".cub", last_4_chars, 4) == SUCCESS)
			free(last_4_chars);
		else
		{
			free(last_4_chars);
			printf("usage: ./cube3d map.cub\n");
			data->return_value = NEED_MAP_CUB_FILE;
		}
		return (data->return_value);
	}
}

t_return_value	validate_cub_file(t_file_data *data, const char **path_to_file)
{
	if (check_file_type(data, path_to_file) == SUCCESS)
	{
		if (read_cub_file_to_string(data, path_to_file) == SUCCESS)
		{
			
		}
	}
	return (SUCCESS);
}
