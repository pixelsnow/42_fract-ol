/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:49:20 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 14:52:39 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	count_iter_mandelbrot(int iterations, t_complex c, t_type type)
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

static int	count_iter_julia(int iterations, t_complex k, t_complex c)
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

static void	set_scale(t_fractol *f)
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
			escape_count = count_iter_julia(f->iter, f->k, c);
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
			escape_count = count_iter_mandelbrot(f->iter, c, f->type);
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
