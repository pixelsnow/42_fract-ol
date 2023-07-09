/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:58:35 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/09 22:04:39 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_hook(int button, t_fractol *v)
{
	(void)button;
	(void)v;
	exit(0);
}

static void	set_julia_k(int x, int y, t_fractol *fractol)
{
	fractol->k.re = fractol->min.re + x * fractol->scale.re;
	fractol->k.im = fractol->max.im - y * fractol->scale.im;
}

int	julia_mouse_hook(int x, int y, t_fractol *fractol)
{
	// check limits
	if (fractol->k_fixed)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	set_julia_k(x, y, fractol);
	draw_fractal(fractol);
	return (0);
}

int	zoom(int code, int x, int y, t_fractol *f)
{
	double	zoom;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT || (code != 4 && code != 5))
		return (0);
	if (!f->k_fixed)
		set_julia_k(x, y, f);
	if (code == 4)
		zoom = 1.25;
	else
		zoom = 0.8;
	f->min.re += (1 - zoom) * (f->max.re - f->min.re) * (x / (double)WIDTH);
	f->max.re -= (1 - zoom) * (f->max.re - f->min.re) * (((double)WIDTH - x) / (double)WIDTH);
	f->min.im += (1 - zoom) * (f->max.im - f->min.im) * (((double)HEIGHT - y) / (double)HEIGHT);
	f->max.im -= (1 - zoom) * (f->max.im - f->min.im) * (y / (double)HEIGHT);
	draw_fractal(f);
	return (0);
}

void	move_fractol(int code, t_fractol *fractol)
{
	(void)code;
	(void)fractol;
	if (code == ARROW_RIGHT)
	{
		fractol->min.re += 0.1 * (fractol->max.re - fractol->min.re) / 1;
		fractol->max.re += 0.1 * (fractol->max.re - fractol->min.re) / 1;
	}
	else if (code == ARROW_LEFT)
	{
		fractol->min.re -= 0.1 * (fractol->max.re - fractol->min.re) / 1;
		fractol->max.re -= 0.1 * (fractol->max.re - fractol->min.re) / 1;
	}
	else if (code == ARROW_UP)
	{
		fractol->min.im += 0.1 * (fractol->max.im - fractol->min.im) / 1;
		fractol->max.im += 0.1 * (fractol->max.im - fractol->min.im) / 1;
	}
	else if (code == ARROW_DOWN)
	{
		fractol->min.im -= 0.1 * (fractol->max.im - fractol->min.im) / 1;
		fractol->max.im -= 0.1 * (fractol->max.im - fractol->min.im) / 1;
	}
	draw_fractal(fractol);
}

void	shift_colors(t_fractol *fractol)
{
	fractol->color = (fractol->color + 1) % 3;
	draw_fractal(fractol);
}

int	keyboard_hook(int code, t_fractol *fractol)
{
	//printf("%i\n", code);

	if (code == ESC)
		exit(0);
	else if (code == ARROW_UP || code == ARROW_DOWN || code == ARROW_LEFT || code == ARROW_RIGHT)
		move_fractol(code, fractol);
	else if (fractol->type == JULIA && code == SPACE)
		fractol->k_fixed = !fractol->k_fixed;
	else if (code == C)
		shift_colors(fractol);
	(void)fractol;
	return (0);
}
