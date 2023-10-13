/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:42:34 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/13 15:32:23 by lclerc           ###   ########.fr       */
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
		//+ 1, sizeof(char *));
//if (!data->file_content_as_array)
//data->return_value = MALLOC_FAILURE;

//}
static t_return_value	get_element_texture(char *element_type, char *element_content)
{
	size_t element_length;
	
	element_length = 0;
	while (element_content[element_length] != '\n' || element_content[element_length] != '\0')
		element_length++;
	element_type = (char *)calloc(element_length + 1, sizeof(char *));
	if (element_type == NULL)
		return (MALLOC_FAILURE);
	ft_strlcpy(element_type, element_content, element_length + 1);
	return (SUCCESS);
}

static t_return_value	find_and_get_element(char *element, t_file_data *data)
{
	t_return_value return_value;
	
	return_value = ELEMENT_NOT_FOUND;
	if (ft_strncmp("NO ", element, 3) == 0)
		return_value = get_element_texture(data->north_texture, element);
	else if (ft_strncmp("SO ", element, 3) == 0)
		return_value = get_element_texture(data->south_texture, element);
	else if (ft_strncmp("WE ", element, 3) == 0)
		return_value = get_element_texture(data->west_texture, element);
	else if (ft_strncmp("EA ", element, 3) == 0)
		return_value = get_element_texture(data->east_texture, element);
	else if (ft_strncmp("F ", element, 2) == 0)
		return_value = get_element_texture(data->floor_color, element);
	else if (ft_strncmp("C ", element, 2) == 0)
		return_value = get_element_texture(data->ceiling_color, element);
	data->return_value = return_value;
	return (data->return_value);
}

static void	remove_leading_white_spaces(char *string_beginning)
{
	while (*string_beginning != '\n' || *string_beginning != '\0')
	{
		if ((*string_beginning > 8 && *string_beginning < 14 ) ||
			*string_beginning == 32)
			string_beginning++;
		else
			break;
	}
}


static t_return_value	get_scene_elements(t_file_data *data)
{
	char	*element_starts;
	char	*element_ends;

	element_starts = data->file_content_as_string;
	while (*element_starts != '\0' || data->elements_found < 6)
	{
		element_ends = ft_strchr(element_starts, '\n');
		remove_leading_white_spaces(element_starts);
		if (element_ends != element_starts)
		{
			if (find_and_get_element(element_starts, data) == SUCCESS)
				data->elements_found++;
			else
				break;
		}
		element_starts++;
	}
	return (data->return_value);
}

t_return_value	validate_scene_requirement(t_file_data *data)
{
	if (get_scene_elements(data) != SUCCESS)
		return (data->return_value);
	//if (get_file_amount_of_lines(data) < 9)
		//return (data->return_value);
	//if (transfer_string_to_array(data) == MALLOC_FAILURE)
		//return (data->return_value);
	print_struct(data);
	return (data->return_value);
}
