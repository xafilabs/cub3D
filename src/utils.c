/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/09 14:00:39 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"


/**
 * @brief Initializes a structure with zeros.
 *
 * This function initializes the memory pointed to by `structure_pointer` with
 * zeros, effectively setting all its members to zero values. It's commonly used
 * to prepare structures for use.
 *
 * @param structure_pointer A pointer to the structure to be initialized.
 */
void	initialize_struct(void *structure_pointer)
{
	ft_bzero(structure_pointer, sizeof(*structure_pointer));
}

/**
 * @brief Prints an error message based on the error code.
 *
 * This function prints an error message to the standard error (stderr) stream
 * based on the provided error code. The error messages are related to specific
 * error conditions such as memory allocation failure, file open failure, or
 * invalid file content.
 *
 * @param error The error code representing the specific error condition.
 */
void	print_error_message(t_return_value error)
{
	if (error == MALLOC_FAILURE)
		ft_putstr_fd("Memory allocation failed\n", 2);
	else if (error == NEED_MAP_CUB_FILE)
		ft_putstr_fd("Usage: use cub file\n", 2);
	else if (error == FILE_OPEN_FAILURE)
		ft_putstr_fd("Error: file open failure\n", 2);
	else if (error == FILE_CONTENT_NOT_VALID)
		ft_putstr_fd("Error: file content not valid\n", 2);
	else if (error == INVALID_ARGUMENT)
		ft_putstr_fd("Usage: use cub file\n", 2);
}


