/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:40:47 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 16:51:25 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	parse_fractal_type(const char *type, t_fractol *fractol)
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
	else if (type[0] == 'b')
	{
		fractol->type = BURNING_SHIP;
		return (0);
	}
	else
		return (1);
}

static int	parse_julia_args(int ac, char **av, t_fractol *f)
{
	if (validate_julia_args(ac, av))
		return (1);
	f->k = init_complex(ft_atof(av[2]), ft_atof(av[3]));
	f->min.re = -1.0;
	f->max.re = 1.0;
	f->min.im = - (f->max.re - f->min.re) / 2 * HEIGHT / WIDTH;
	f->max.im = f->min.im + (f->max.re - f->min.re) * HEIGHT / WIDTH;
	f->k_fixed = 0;
	return (0);
}

static int	parse_mandelbrot_args(int ac, t_fractol *f)
{
	if (ac != 2)
		return (1);
	f->min.re = -2.0;
	f->max.re = 1.0;
	f->min.im = - (f->max.re - f->min.re) / 2 * HEIGHT / WIDTH;
	f->max.im = f->min.im + (f->max.re - f->min.re) * HEIGHT / WIDTH;
	return (0);
}

static int	parse_fractal_args(int ac, char **av, t_fractol *fractol)
{
	if (fractol->type == JULIA)
		return (parse_julia_args(ac, av, fractol));
	if (fractol->type == MANDELBROT || fractol->type == BURNING_SHIP)
		return (parse_mandelbrot_args(ac, fractol));
	return (1);
}

int	parse_args(int ac, char **av, t_fractol	*fractol)
{
	if (ac < 2)
	{
		print_instructions();
		return (1);
	}
	if (parse_fractal_type(av[1], fractol))
	{
		print_instructions();
		return (1);
	}
	if (parse_fractal_args(ac, av, fractol))
	{
		print_instructions();
		return (1);
	}
	fractol->iter = ITER;
	fractol->color = 0;
	return (0);
}
