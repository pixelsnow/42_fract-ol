/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:28:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 14:18:56 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH			500
# define HEIGHT			500

# define ARROW_UP		126
# define ARROW_DOWN		125
# define ARROW_LEFT		123
# define ARROW_RIGHT	124
# define ESC			53
# define SPACE			49
# define C				8

# define ITER			80

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex {
	double	re;
	double	im;
}				t_complex;

typedef enum {
  MANDELBROT,
  JULIA,
  BURNING_SHIP
} t_type;

typedef struct s_fractol {
	t_data		img;
	void		*mlx;
	void		*win;
	t_type		type;
	int			color;
	int			iter;
	int			k_fixed;
	t_complex	k;
	t_complex	min;
	t_complex	max;
	t_complex	scale;
}				t_fractol;

double		ft_atof(char *str);
t_complex	init_complex(double re, double im);
int			rgb_to_int(int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			get_colour(int color, int iterations, int iteration_count);
int			parse_args(int ac, char **av, t_fractol	*fractol);
int			keyboard_hook(int code, t_fractol *fractol);
void		move_fractol(int code, t_fractol *fractol);
int			zoom(int code, int x, int y, t_fractol *f);
int			julia_mouse_hook(int x, int y, t_fractol *fractol);
int			close_hook(int button, t_fractol *v);
void		draw_fractal(t_fractol *fractol);

#endif
