/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/10/09 10:07:40 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	initialize_struct(void *structure_pointer)
{
	ft_bzero(structure_pointer, sizeof(*structure_pointer));
}


