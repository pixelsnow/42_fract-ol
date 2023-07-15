/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 16:44:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_fractol *fractol)
{
	if (fractol->type == JULIA)
		draw_julia(fractol);
	else if (fractol->type == MANDELBROT || fractol->type == BURNING_SHIP)
		draw_mandelbrot(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

static void	init_fractol_mlx(t_fractol *fractol)
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
