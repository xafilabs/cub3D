/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:17:58 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/06 17:23:16 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static	t_return_value open_and_validate_file(t_file_data *data, char **path)
{
	data->file_descriptor = open(path[1], O_RDONLY);
	if (data->file_descriptor == -1)
	 {
		data->return_value == FILE_OPEN_ERROR;
		return (data->return_value);
	 }
	return (data->return_value);
}

static t_return_value	initialize_strings(char *line, char *file_content_as_string, t_file_data *data)
{
	line = ft_strdup("");
	file_content_as_string = ft_strdup(""); 
	if (!line || !file_content_as_string)
	{
		data->return_value = MALLOC_FAIL;
		if (line)
			free(line);
		if (file_content_as_string)
			free(file_content_as_string);
		close(data->file_descriptor);
	}
	return (data->return_value);
}

static t_return_value	concatenate_line_to_string(t_file_data *data, char *line)
{
	char	*temp;

	temp = ft_strdup(data->file_content_as_string);
	if (temp == NULL)
	 {
		data->return_value = MALLOC_FAIL;
		return (data->return_value);
	 }
	free(data->file_content_as_string);
	data->file_content_as_string = ft_strjoin(temp, line);
	free(temp);
	if (data->file_content_as_string == NULL)
			data->return_value = MALLOC_FAIL;
	return (data->return_value);
}

static t_return_value	get_file_content_to_string(t_file_data *data, const char **path)
{
	char	*line;

	if (open_and_validate_file(data, path) == FILE_NOT_VALID)
		return (data->return_value);
	if (initialize_strings(line, data->file_content_as_string, data) == MALLOC_FAIL)
		return (data->return_value);
	while (line)
	{
		line = get_next_line(data->file_descriptor);
		if (line == NULL)
			break;
		if (concatenate_line_to_string(data, line) == MALLOC_FAIL)
			break;
		free(line);
	}
	if (line)
		free(line);
	close(data->file_descriptor);
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
	}
	return (data->return_value);
}

t_return_value	validate_cub_file(t_file_data *data, const char **path_to_file)
{
	if (check_file_type(data, path_to_file) == SUCCESS)
	{
		if (get_file_content_to_string(data, path_to_file) == SUCCESS)
		{
			
		}
	}
	return (data->return_value);
}
