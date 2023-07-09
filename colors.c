/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:39:31 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/09 20:41:28 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_colour_wb(int iterations, int iteration_count)
{
	return (rgb_to_int(255 / iterations * iteration_count,
			255 / iterations * iteration_count,
			255 / iterations * iteration_count));
}

static int	get_colour_bw(int iterations, int iteration_count)
{
	return (rgb_to_int(255 / iterations * (iterations - iteration_count),
			255 / iterations * (iterations - iteration_count),
			255 / iterations * (iterations - iteration_count)));
}

static int	get_colour_1(int iterations, int iteration_count)
{
	int	mod;

	(void) iterations;
	mod = iteration_count % 3;
	if (mod == 0)
		return (rgb_to_int(197, 222, 193));
	if (mod == 1)
		return (rgb_to_int(161, 154, 255));
	return (rgb_to_int(255, 214, 235));
}

int	get_colour(int color, int iterations, int iteration_count)
{
	if (color == 0)
		return get_colour_bw(iterations, iteration_count);
	if (color == 1)
		return get_colour_wb(iterations, iteration_count);
	return get_colour_1(iterations, iteration_count);
}
