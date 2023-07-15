/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 14:17:48 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	count_iterations_mandelbrot(int iterations, t_complex c, t_type type)
{
	int			iter;
	t_complex	z;
	t_complex	z_parts_sq;

	z = init_complex(c.re, -c.im);
	iter = 0;
	while (iter < iterations)
	{
		if (type == BURNING_SHIP)
			z = init_complex(fabs(z.re), fabs(z.im));
		z_parts_sq = init_complex(pow(z.re, 2), pow(z.im, 2));
		if (z_parts_sq.re + z_parts_sq.im > 4)
			return (iter);
		z.im = 2 * z.re * z.im - c.im;
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
		z_parts_sq = init_complex(pow(z.re, 2), pow(z.im, 2));
		if (z_parts_sq.re + z_parts_sq.im > 4)
			return (iter);
		z.im = 2 * z.re * z.im + k.im;
		z.re = z_parts_sq.re - z_parts_sq.im + k.re;
		iter++;
	}
	return (0);
}

void	set_scale(t_fractol *f)
{
	f->scale.re = (f->max.re - f->min.re) / (WIDTH - 1);
	f->scale.im = (f->max.im - f->min.im) / (HEIGHT - 1);
}

void	draw_julia(t_fractol *f)
{
	int			y;
	int			x;
	int			escape_count;
	t_complex	c;

	set_scale(f);
	y = 0;
	while (y < HEIGHT)
	{
		c.im = f->max.im - y * f->scale.im;
		x = 0;
		while (x < WIDTH)
		{
			c.re = f->min.re + x * f->scale.re;
			escape_count = count_iterations_julia(f->iter, f->k, c);
			if (escape_count)
				my_mlx_pixel_put(&f->img, x, y, get_colour(f->color, f->iter, escape_count));
			else
				my_mlx_pixel_put(&f->img, x, y, rgb_to_int(0, 0, 0));
			x++;
		}
		y++;
	}
}

void	draw_mandelbrot(t_fractol *f)
{
	int			y;
	int			x;
	int			escape_count;
	t_complex	c;

	set_scale(f);
	y = 0;
	while (y < HEIGHT)
	{
		c.im = f->max.im - y * f->scale.im;
		x = 0;
		while (x < WIDTH)
		{
			c.re = f->min.re + x * f->scale.re;
			escape_count = count_iterations_mandelbrot(f->iter, c, f->type);
			if (escape_count)
				my_mlx_pixel_put(&f->img, x, y, get_colour(f->color, f->iter,
						escape_count));
			else
				my_mlx_pixel_put(&f->img, x, y, rgb_to_int(0, 0, 0));
			x++;
		}
		y++;
	}
}


void	draw_fractal(t_fractol *fractol)
{
	if (fractol->type == JULIA)
	{
		draw_julia(fractol);
	}
	else if (fractol->type == MANDELBROT || fractol->type == BURNING_SHIP)
	{
		draw_mandelbrot(fractol);
	}
/* 	else if (fractol->type == BURNING_SHIP)
	{
		draw_burning_ship(fractol);
	} */
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

void	init_fractol_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "fractol");
	mlx_hook(fractol->win, 17, 0, close_hook, fractol);
	mlx_hook(fractol->win, 4, 0, zoom, fractol);
	mlx_hook(fractol->win, 3, 0, keyboard_hook, fractol);
	if (fractol->type == JULIA)
		mlx_hook(fractol->win, 6, 0, julia_mouse_hook, fractol);
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->img.addr = mlx_get_data_addr(fractol->img.img,
		&fractol->img.bits_per_pixel, &fractol->img.line_length,
		&fractol->img.endian);
}

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (parse_args(ac, av, &fractol))
		return (1);
	init_fractol_mlx(&fractol);
	draw_fractal(&fractol);
	mlx_loop(fractol.mlx);
	return (0);
}
