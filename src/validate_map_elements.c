/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:42:34 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/12 15:56:55 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

//static int	get_file_amount_of_lines(t_file_data *data)
//{
//char	*temp;

//temp = data->file_content_as_string;
//while(*temp)
//{
//if (*temp == '\n')
//data->file_number_of_lines++;
//temp++;
//}
//if (data->file_number_of_lines < 9)
//data->return_value = FILE_CONTENT_NOT_VALID;
//return (data->file_number_of_lines);
//}

//static t_return_value	transfer_string_to_array(t_file_data *data)
//{
//data->file_content_as_array = (char **)ft_calloc(data->file_number_of_lines
		+ 1, sizeof(char *));
//if (!data->file_content_as_array)
//data->return_value = MALLOC_FAILURE;

//}
static t_return_value	find_and_get_element(char *element, t_file_data *data)
{
	if (ft_strncmp("NO ", element, 3) == 0)
		get_element_texture(data->no_texture, element);
	else if (ft_strncmp("SO ", element, 3) == 0)
		get_element_texture(data->so_texture, element);
	else if (ft_strncmp("WE ", element, 3) == 0)
		get_element_texture(data->we_texture, element);
	else if (ft_strncmp("EA ", element, 3) == 0)
		get_element_texture(data->ea_texture, element);
	else if (ft_strncmp("F ", element, 2) == 0)
		get_element_texture(data->floor_color, element);
	else if (ft_strncmp("C ", element, 2) == 0)
		get_element_texture(data->ceiling_color, element);
}

static void	remove_leading_white_spaces(char *string_beginning)
{
	while (*string_beginning != '\n' || *string_beginning != '\0')
	{
		if ((*string_beginning > 8 && *string_beginning < 14 
			|| *string_beginning == 32))
			string_beginning++;
		else
			break;
	}
}


static t_return_value	get_scene_elements(t_file_data *data)
{
	char	*end_of_line;
	char	*string_beginning;

	string_beginning = data->file_content_as_string;
	while (*string_beginning != '\0' || data->elements_found < 6)
	{
		end_of_line = ft_strchr(string_beginning, "\n");
		remove_leading_white_spaces(string_beginning);
		if (end_of_line	!= string_beginning)
		{
			if (find_and_get_element(string_beginning, data) == SUCCESS)
				data->elements_found++;
			else 
			{
				data->return_value = ELEMENTS_NOT_VALID;
				break;
			}
		}
		string_beginning++;
	}
	return (data->return_value);
}

t_return_value	validate_scene_requirement(t_file_data *data)
{
	if (get_scene_elements(data) == ELEMENTS_NOT_VALID)
		return (data->return_value);
	//if (get_file_amount_of_lines(data) < 9)
		//return (data->return_value);
	//if (transfer_string_to_array(data) == MALLOC_FAILURE)
		//return (data->return_value);
}
