/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:55:51 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/24 08:03:25 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int get_r(unsigned int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

unsigned int get_g(unsigned int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

unsigned int get_b(unsigned int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

unsigned int get_a(unsigned int rgba)
{
	return (rgba & 0xFF);
}

unsigned int get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
