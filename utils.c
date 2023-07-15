/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:09:38 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 16:31:52 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	init_complex(double re, double im)
{
	t_complex	res;

	res.re = re;
	res.im = im;
	return (res);
}

void	print_instructions(void)
{
	write(1, "Mandelbrot:\tm\n", 14);
	write(1, "Julia:\t\tj [constant_Re] [constant_Im]\n", 38);
	write(1, "Burning ship:\tb\n", 16);
	write(1, "---------------------------------------------\n", 46);
	write(1, "Zoom:\tmouse wheel (take it slow...)\n", 36);
	write(1, "Move:\t\t↑↓←→\n", 17);
}
