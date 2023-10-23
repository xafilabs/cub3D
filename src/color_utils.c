/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:55:51 by malaakso          #+#    #+#             */
/*   Updated: 2023/10/23 13:57:22 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int get_a(int rgba)
{
	return (rgba & 0xFF);
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
