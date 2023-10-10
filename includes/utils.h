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

//typedef enum e_bool
//{
	//FALSE,
	//TRUE
//}			t_bool;

void			initialize_struct(t_file_data *structure_pointer);
void			print_error_message(t_return_value error);
t_return_value	validate_cub_file(t_file_data *data, const char **path_to_file);
void			clean_up(t_file_data *data);


#endif
