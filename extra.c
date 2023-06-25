/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:55:32 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/25 12:56:22 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_binary(int n)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		if (n & (1 << i))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		if (!(i % 8))
			write(1, " ", 1);
		i--;
	}
	write(1, "\n", 1);
}

void	fill(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			my_mlx_pixel_put (img, i, j, rgb_to_int(255, 255, 255));
			j++;
		}
		i++;
	}
}

void	draw_square(t_data *img, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while (j < 30)
		{
			my_mlx_pixel_put (img, i + x, j + y,
				rgb_to_int(100 + i / 4, 100 + j / 4, 100 + j / 8 + i / 8));
			j++;
		}
		i++;
	}
}