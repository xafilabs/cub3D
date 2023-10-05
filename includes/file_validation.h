/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:28:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/05 14:15:42 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_VALIDATION_H
# define FILE_VALIDATION_H
# include "../libft/libft.h"

// Structure to hold RGB color components
typedef struct s_color
{
	int red;   // Red component (0-255)
	int green; // Green component (0-255)
	int blue;  // Blue component (0-255)
}					t_color;

// Structure to hold information extracted from the scene description file
typedef struct s_file_data
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*map_content;
	t_color			floor_color;
	t_color			ceiling_color;
	t_return_value	return_value;
}					t_file_data;

#endif