/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:44 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/25 12:29:25 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

unsigned int	get_rgba(unsigned int r,
					unsigned int g,
					unsigned int b,
					unsigned int a);
unsigned int	get_r(unsigned int rgba);
unsigned int	get_g(unsigned int rgba);
unsigned int	get_b(unsigned int rgba);
unsigned int	get_a(unsigned int rgba);
unsigned int	convert_abgr_to_rgba(unsigned int agbr);

#endif
