/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/10 18:50:19 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

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

int	rgb_to_int(int r, int g, int b)
{
	int	bit;
	int res;
	
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

	/* printf("Pixel to: x = %i, y = %i, color = ", x, y);
	print_binary(color);
	printf("\n"); */
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_data *img, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while (j < 30)
		{
			my_mlx_pixel_put (img, i + x, j + y, rgb_to_int(100 + i / 4, 100 + j / 4, 100 + j / 8 + i / 8));
			j++;
		}
		i++;
	}
}

int	iterations_to_exit(double *z_r, double *z_i, int	iterations, double c_r, double c_i)
{
	int		iteration;
	double	z_r2;
	double	z_i2;

	iteration = 0;
	while (iteration < iterations)
	{
		z_r2 = *z_r * *z_r;
		z_i2 = *z_i * *z_i;
		if (z_r2 + z_i2 > 4)
		{
			return (iteration);
		}
		*z_i = 2 * *z_r * *z_i + c_i;
		*z_r = z_r2 - z_i2 + c_r;
		iteration++;
	}
	return (0);
}

int	get_colour_by_iteration(int	iterations, int iteration_count)
{
	return rgb_to_int(255 / iterations * (iterations - iteration_count), 255 / iterations * (iterations - iteration_count), 255 / iterations * (iterations - iteration_count));
}

void	draw_mandelbrot(t_data *img, int	iterations)
{
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	scale_r;
	double	scale_i;
	int		y;
	int		x;
	double	z_r;
	double	z_i;
	double	c_r;
	double	c_i;
	int		iteration_count;

	min_r = -2.0;
	max_r = 2.0;
	min_i = - (max_r - min_r) / 2 * WIN_WIDTH / WIN_HEIGHT;
	max_i = min_i + (max_r - min_r) * WIN_HEIGHT / WIN_WIDTH;
	scale_r = (max_r - min_r) / (WIN_WIDTH - 1);
	scale_i = (max_i - min_i) / (WIN_HEIGHT - 1);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		c_i = max_i - y * scale_i;
		x = 0;
		while (x < WIN_WIDTH)
		{
			c_r = min_r + x * scale_r;
			z_r = c_r;
			z_i = c_i;
			iteration_count = iterations_to_exit(&z_r, &z_i, iterations, c_r, c_i);
			if (iteration_count)
				my_mlx_pixel_put(img, x, y, get_colour_by_iteration(iterations, iteration_count));
			x++;
		}
		y++;
	}
}

int main(void)
{
	t_fractol	fractol;

	fractol.mlx_ptr = mlx_init(); // identifier of the connection to the graphics server
	fractol.win_ptr = mlx_new_window(fractol.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "test"); // will need this when we need to draw
	fractol.img.img = mlx_new_image(fractol.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fractol.img.addr = mlx_get_data_addr(fractol.img.img, &fractol.img.bits_per_pixel, &fractol.img.line_length,
								&fractol.img.endian);
	//draw_square(&fractol.img, 0, 0);
	draw_mandelbrot(&fractol.img, 50);
	mlx_put_image_to_window(fractol.mlx_ptr, fractol.win_ptr, fractol.img.img, 0, 0);
	mlx_loop(fractol.mlx_ptr); // draws, opens the window, manages events
	return (0);
}
