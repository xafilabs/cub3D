/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:43 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/27 15:40:43 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"


void	handle_error(t_return_value error, t_program_phase phase)
{
	if (phase == PHASE_PARSING)
	{
		print_parsing_error_message(error);
	}
	
	exit(1);
}
