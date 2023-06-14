/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/14 22:11:42 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

t_complex	init_complex(double re, double im)
{
	t_complex	res;

	res.re = re;
	res.im = im;
	return (res);
}

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

	/* printf("Pixel to: x = %i, y = %i, color = ", x, y);
	print_binary(color);
	printf("\n"); */
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

int	count_iterations_to_escape(int iterations, t_complex c)
{
	int			iter;
	t_complex	z;
	t_complex	z_parts_sq;

	z = init_complex(c.re, c.im);
	iter = 0;
	while (iter < iterations)
	{
		z_parts_sq = init_complex(z.re * z.re, z.im * z.im);
		if (z_parts_sq.re + z_parts_sq.im > 4)
		{
			// out of the circle with radius of 2
			return (iter);
		}
		z.im = 2 * z.re * z.im + c.im;
		z.re = z_parts_sq.re - z_parts_sq.im + c.re;
		iter++;
	}
	return (0);
}

int	count_iterations_julia(int iterations, t_complex k, t_complex c)
{
	int			iter;
	t_complex	z;
	t_complex	z_parts_sq;

	z = init_complex(c.re, c.im);
	iter = 0;
	while (iter < iterations)
	{
		z_parts_sq = init_complex(z.re * z.re, z.im * z.im);
		//printf("%f\n", z_parts_sq.re + z_parts_sq.im);
		if (z_parts_sq.re + z_parts_sq.im > 4)
		{
			return (iter);
		}
		z.im = 2 * z.re * z.im + k.im;
		z.re = z_parts_sq.re - z_parts_sq.im + k.re;
		iter++;
	}
	return (0);
}

int	get_colour(int iterations, int iteration_count)
{
	return (rgb_to_int(255 / iterations * iteration_count,
			255 / iterations * iteration_count,
			255 / iterations * iteration_count));
}

void	set_limits(t_complex *min, t_complex *max, t_complex *scale)
{
	min->re = -2.0;
	max->re = 1.0;
	min->im = - (max->re - min->re) / 2 * HEIGHT / WIDTH;
	max->im = min->im + (max->re - min->re) * HEIGHT / WIDTH;
	scale->re = (max->re - min->re) / (WIDTH - 1);
	scale->im = (max->im - min->im) / (HEIGHT - 1);
}

void	set_julia_limits(t_complex *min, t_complex *max, t_complex *scale)
{
	min->re = -1.0;
	max->re = 1.0;
	min->im = - (max->re - min->re) / 2 * HEIGHT / WIDTH;
	max->im = min->im + (max->re - min->re) * HEIGHT / WIDTH;
	scale->re = (max->re - min->re) / (WIDTH - 1);
	scale->im = (max->im - min->im) / (HEIGHT - 1);
}

void	draw_julia(t_data *img, int	iterations, t_complex k)
{
	int		y;
	int		x;
	int		escape_count;
	t_complex	c;
	t_complex	min;
	t_complex	max;
	t_complex	scale;

	set_julia_limits(&min, &max, &scale);
	y = 0;
	while (y < HEIGHT)
	{
		c.im = max.im - y * scale.im;
		x = 0;
		while (x < WIDTH)
		{
			c.re = min.re + x * scale.re;
			escape_count = count_iterations_julia(iterations, k, c);
			if (escape_count)
			{
				my_mlx_pixel_put(img, x, y, get_colour(iterations, escape_count));
			}
			x++;
		}
		y++;
	}
}

void	draw_mandelbrot(t_data *img, int iterations)
{
	int			y;
	int			x;
	int			escape_count;
	t_complex	c;
	t_complex	min;
	t_complex	max;
	t_complex	scale;

	set_limits(&min, &max, &scale);
	y = 0;
	while (y < HEIGHT)
	{
		c.im = max.im - y * scale.im; // converting coordinates to c
		x = 0;
		while (x < WIDTH)
		{
			c.re = min.re + x * scale.re;
			escape_count = count_iterations_to_escape(iterations, c);
			if (escape_count)
				my_mlx_pixel_put(img, x, y, get_colour(iterations,
						escape_count));
			x++;
		}
		y++;
	}
}

int	close_hook(int button, t_vars *v)
{
	(void)button;
	(void)v;
	exit(0);
}

int	simple_mouse_hook(int code, t_vars *v)
{
	printf("%i\n", code);
	(void)v;
	return (0);
}

int	mouse_hook(int x, int y, int extra, t_fractol *fractol)
{
	t_complex	min;
	t_complex	max;
	t_complex	scale;

	set_julia_limits(&min, &max, &scale);
	/* fractol->k.re = 1;
	fractol->k.im = 1; */
	/* printf("%f %f\n", fractol->k.re, fractol->k.im);  */
	(void)x;
	(void)y;
	(void)extra;
	(void)fractol;
	return (0);
}

void	init_fractol(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	// identifier of the connection to the graphics server
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "test");
	// will need this when we need to draw
	mlx_hook(fractol->win, 17, 0, close_hook, &fractol); // weird magic
	mlx_mouse_hook(fractol->win, simple_mouse_hook, &fractol);
	mlx_hook(fractol->win, 6, 0, mouse_hook, &fractol);
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->img.addr = mlx_get_data_addr(fractol->img.img,
		&fractol->img.bits_per_pixel, &fractol->img.line_length,
		&fractol->img.endian);
}

int	main(void)
{
	t_fractol	fractol;

	init_fractol(&fractol);
	//draw_mandelbrot(&fractol.img, 50);
	fractol.k = init_complex(0.33, 0.395);
	draw_julia(&fractol.img, 50, fractol.k);
	mlx_put_image_to_window(fractol.mlx, fractol.win, fractol.img.img, 0, 0);
	mlx_loop(fractol.mlx); // draws, opens the window, manages events
	return (0);
}
