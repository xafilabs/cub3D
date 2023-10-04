/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:17:58 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/04 16:23:04 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static t_return_value	check_file_type(t_file_data data, const char **path_to_file)
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
		{
			free(last_4_chars);
			return (SUCCESS);
		}
		free(last_4_chars);
		printf("usage: ./cube3d map.cub\n");
		//Should we free stuff here... or leave it to exit()?
		exit(NEED_MAP_CUB_FILE);
	}
}

t_return_value	validate_cub_file(t_file_data data, const char **path_to_file)
{
	check_file_type(data, path_to_file);
	return (SUCCESS);


}
