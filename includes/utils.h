/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:44:10 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/04 13:38:37by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "../includes/file_validation.h"

# define NULL ((void *) 0);

typedef enum e_return_value
{
	SUCCESS,
	FAILURE,
	MALLOC_FAIL,
	NEED_MAP_CUB_FILE,
	FILE_NOT_VALID,
	FILE_CONTENT_NOT_VALID,
	INVALID_ARGUMENT,
}						t_return_value;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

void			initialize_struct(void *structure_pointer);
t_return_value	validate_cub_file(t_file_data file_data, const char **path_to_file);

#endif