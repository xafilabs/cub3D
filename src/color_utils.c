/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:55:51 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/25 12:31:19 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	get_r(unsigned int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

unsigned int	get_g(unsigned int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

unsigned int	get_b(unsigned int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

unsigned int	get_a(unsigned int rgba)
{
	return (rgba & 0xFF);
}

unsigned int
	get_rgba(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// takes in uint32 with color encoded as AAGGBBRR (AGBR)
// and outputs it as uint32 with color encoded as RRGGBBAA (RGBA)
unsigned int convert_abgr_to_rgba(unsigned int agbr)
{
	unsigned int	rgba;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	r = (agbr & 0x000000FF) << 24;
	g = (agbr & 0x0000FF00) << 8;
	b = (agbr & 0x00FF0000) >> 8;
	a = (agbr & 0xFF000000) >> 24;
	rgba = a | r | g | b;
	return (rgba);
}
