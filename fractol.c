/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/08 18:33:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <limits.h>
#include <float.h>

t_complex	init_complex(double re, double im)
{
	t_complex	res;

	res.re = re;
	res.im = im;
	return (res);
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

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	count_iterations_mandelbrot(int iterations, t_complex c)
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
		z_parts_sq = init_complex(pow(z.re, 2), pow(z.im, 2));
		if (z_parts_sq.re + z_parts_sq.im > 4)
			return (iter);
		z.im = 2 * z.re * z.im + k.im;
		z.re = z_parts_sq.re - z_parts_sq.im + k.re;
		iter++;
	}
	return (0);
}

int	get_colour_wb(int iterations, int iteration_count)
{
	return (rgb_to_int(255 / iterations * iteration_count,
			255 / iterations * iteration_count,
			255 / iterations * iteration_count));
}

int	get_colour_bw(int iterations, int iteration_count)
{
	return (rgb_to_int(255 / iterations * (iterations - iteration_count),
			255 / iterations * (iterations - iteration_count),
			255 / iterations * (iterations - iteration_count)));
}

int	get_colour_1(int iterations, int iteration_count)
{
	return (rgb_to_int(250,
			255 / iterations * (iterations - iteration_count),
			255 / iterations * (iterations - iteration_count)));
}

int	get_colour(int iterations, int iteration_count)
{
	return get_colour_bw(iterations, iteration_count);
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

void	set_julia_limits(t_fractol *f)
{
	f->min.im = - (f->max.re - f->min.re) / 2 * HEIGHT / WIDTH;
	f->max.im = f->min.im + (f->max.re - f->min.re) * HEIGHT / WIDTH;
	f->scale.re = (f->max.re - f->min.re) / (WIDTH - 1);
	f->scale.im = (f->max.im - f->min.im) / (HEIGHT - 1);
}

void	draw_julia(t_fractol *f)
{
	int		y;
	int		x;
	int		escape_count;
	t_complex	c;

	//printf("DRAW: %p %i %f %f\n", img, iterations, k.re, k.im);
	set_julia_limits(f);
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
				my_mlx_pixel_put(&f->img, x, y, get_colour(f->iter, escape_count));
			else
				my_mlx_pixel_put(&f->img, x, y, rgb_to_int(0, 0, 0));
			x++;
		}
		y++;
	}
}

// TODO: refactor to only take in fractol object
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
			escape_count = count_iterations_mandelbrot(iterations, c);
			if (escape_count)
				my_mlx_pixel_put(img, x, y, get_colour(iterations,
						escape_count));
			else
				my_mlx_pixel_put(img, x, y, rgb_to_int(0, 0, 0));
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

void	set_julia_k(int x, int y, t_fractol *fractol)
{
	fractol->k.re = fractol->min.re + x * fractol->scale.re;
	fractol->k.im = fractol->max.im - y * fractol->scale.im;
}

void	draw_fractal(t_fractol *fractol)
{
	if (fractol->type == JULIA)
	{
		draw_julia(fractol);
	}
	else if (fractol->type == MANDELBROT)
	{
		draw_mandelbrot(&fractol->img, 50);
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

int	julia_mouse_hook(int x, int y, t_fractol *fractol)
{
	// check limits
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	set_julia_limits(fractol);
	set_julia_k(x, y, fractol);
	draw_fractal(fractol);
	return (0);
}

int	zoom(int code, int x, int y, t_fractol *fractol)
{
	// check limits
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	printf("zoom: %d %d %d\n", code, x, y);
	set_julia_limits(fractol);
	set_julia_k(x, y, fractol);
	printf("%f %f\n", fractol->k.re, fractol->k.im); 
	draw_fractal(fractol);
	return (0);
}

void	move_fractol(int code, t_fractol *fractol)
{
	(void)code;
	(void)fractol;
	if (code == ARROW_RIGHT)
	{
		fractol->min.re += 0.1;
		fractol->max.re += 0.1;
	}
	else if (code == ARROW_LEFT)
	{
		fractol->min.re -= 0.1;
		fractol->max.re -= 0.1;
	}
	draw_fractal(fractol);
}

int	keyboard_hook(int code, t_fractol *fractol)
{
	printf("%i\n", code);

	if (code == ESC)
		exit(0);
	else if (code == ARROW_UP || code == ARROW_DOWN || code == ARROW_LEFT || code == ARROW_RIGHT)
		move_fractol(code, fractol);
	(void)fractol;
	return (0);
}

void	init_fractol_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	// identifier of the connection to the graphics server
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "fractol");
	mlx_hook(fractol->win, 17, 0, close_hook, fractol); // weird magic
	mlx_hook(fractol->win, 4, 0, zoom, fractol);
	mlx_hook(fractol->win, 3, 0, keyboard_hook, fractol);
	if (fractol->type == JULIA)
		mlx_hook(fractol->win, 6, 0, julia_mouse_hook, fractol);
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->img.addr = mlx_get_data_addr(fractol->img.img,
		&fractol->img.bits_per_pixel, &fractol->img.line_length,
		&fractol->img.endian);
}

void	print_instructions(void)
{
	write(1, "To draw Mandelbrot:\n", 20);
	write(1, "m [iterations*] - * optional, default is 50\n", 44);
	write(1, "Mandelbrot example:\nm 100\n", 26);
	write(1, "To draw Julia:\n", 15);
	write(1, "j [constant_Re] [constant_Im] [iterations*] - * optional, default is 50\n", 72);
	write(1, "Julia example:\nj 0.33 0.395 40\n", 31);
}

int	parse_fractal_type(const char *type, t_fractol	*fractol)
{
	if (!type[0] || type[1])
		return (1);
	if (type[0] == 'm')
	{
		fractol->type = MANDELBROT;
		return (0);
	}
	else if (type[0] == 'j')
	{
		fractol->type = JULIA;
		return (0);
	}
	else
		return (1);
}

int	validate_julia_args(int ac, char **av, t_fractol *fractol)
{
	(void)ac;
	(void)av;
	(void)fractol;
	return (0);
}

int	parse_julia_args(int ac, char **av, t_fractol *fractol)
{
	printf("parsing julia args\n");
	if (validate_julia_args(ac, av, fractol))
		return (1);
	fractol->k = init_complex(atof(av[2]), atof(av[3]));
	fractol->min.re = -1.0;
	fractol->max.re = 1.0;
	return (0);
}

int	parse_fractal_args(int ac, char **av, t_fractol *fractol)
{
	if (fractol->type == JULIA)
		return parse_julia_args(ac, av, fractol);
	if (fractol->type == MANDELBROT)
		return (ac != 2);
	else
		return (1);
}

int	parse_args(int ac, char **av, t_fractol	*fractol)
{
	if (ac < 2)
		return (1);
	if (parse_fractal_type(av[1], fractol))
	{
		printf("type not parsed\n");
		return (1);
	}
	if (parse_fractal_args(ac, av, fractol))
	{
		printf("args not parsed\n");
		return (1);
	}
	printf("all parsed\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_fractol	fractol;

	// TODO: handle arguments
	if (parse_args(ac, av, &fractol))
		return (1);
	fractol.iter = 50;
	//print_instructions();
	//fractol.k = init_complex(0.26, 0.0016);
	init_fractol_mlx(&fractol);
	//draw_mandelbrot(&fractol.img, 50);
	draw_fractal(&fractol);
	/* mlx_hook(fractol.win, 17, 0, close_hook, &fractol); // weird magic
	mlx_mouse_hook(fractol.win, simple_mouse_hook, &fractol);
	mlx_hook(fractol.win, 6, 0, mouse_hook, &fractol); */
	mlx_loop(fractol.mlx); // draws, opens the window, manages events
	return (0);
}
