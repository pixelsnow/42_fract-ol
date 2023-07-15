/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:06:45 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 16:50:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_julia_k(int x, int y, t_fractol *fractol)
{
	fractol->k.re = fractol->min.re + x * fractol->scale.re;
	fractol->k.im = fractol->max.im - y * fractol->scale.im;
}

int	julia_mouse_hook(int x, int y, t_fractol *fractol)
{
	if (fractol->k_fixed)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);
	set_julia_k(x, y, fractol);
	draw_fractal(fractol);
	return (0);
}

static void	adjust_boundaries(t_fractol *f, double zoom, int x, int y)
{
	double	del_min_re;
	double	del_max_re;
	double	del_min_im;
	double	del_max_im;

	del_min_re = (1 - zoom) * (f->max.re - f->min.re) * (x / (double)WIDTH);
	del_max_re = (1 - zoom) * (f->max.re - f->min.re)
		* (((double)WIDTH - x) / (double)WIDTH);
	del_min_im = (1 - zoom) * (f->max.im - f->min.im)
		* (((double)HEIGHT - y) / (double)HEIGHT);
	del_max_im = (1 - zoom) * (f->max.im - f->min.im)
		* (y / (double)HEIGHT);
	f->min.re += del_min_re;
	f->max.re -= del_max_re;
	f->min.im += del_min_im;
	f->max.im -= del_max_im;
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
	adjust_boundaries(f, zoom, x, y);
	draw_fractal(f);
	return (0);
}
