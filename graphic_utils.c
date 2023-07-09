/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:17:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/09 20:18:03 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rgb_to_int(int r, int g, int b)
{
	int	bit;
	int	res;

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	res = 0;
	bit = 7;
	while (bit >= 0)
	{
		res |= (r & (1 << bit)) << 16;
		bit--;
	}
	bit = 7;
	while (bit >= 0)
	{
		res |= (g & (1 << bit)) << 8;
		bit--;
	}
	bit = 7;
	while (bit >= 0)
	{
		res |= (b & (1 << bit));
		bit--;
	}
	return (res);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}