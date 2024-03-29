/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:06:50 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 16:59:52 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_hook(int button, t_fractol *v)
{
	(void)button;
	(void)v;
	exit(0);
}

static void	move_fractol(int code, t_fractol *fractol)
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

static void	shift_colors(t_fractol *fractol)
{
	fractol->color = (fractol->color + 1) % 3;
	draw_fractal(fractol);
}

static void	change_iterations(int code, t_fractol *fractol)
{
	if (code == MINUS || code == MINUS_KEYPAD)
		fractol->iter -= 10;
	else
		fractol->iter += 10;
	if (fractol->iter > 255)
		fractol->iter = 255;
	else if (fractol->iter < 2)
		fractol->iter = 2;
	draw_fractal(fractol);
}

int	keyboard_hook(int code, t_fractol *fractol)
{
	if (code == ESC)
		exit(0);
	else if (code == ARROW_UP || code == ARROW_DOWN || code == ARROW_LEFT
		|| code == ARROW_RIGHT)
		move_fractol(code, fractol);
	else if (fractol->type == JULIA && code == SPACE)
		fractol->k_fixed = !fractol->k_fixed;
	else if (code == C)
		shift_colors(fractol);
	else if (code == PLUS || code == MINUS || code == PLUS_KEYPAD
		|| code == MINUS_KEYPAD)
		change_iterations(code, fractol);
	(void)fractol;
	return (0);
}
