/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:28:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/09 17:41:00 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 800
# define HEIGHT 800

# define ARROW_UP		126
# define ARROW_DOWN		125
# define ARROW_LEFT		123
# define ARROW_RIGHT	124
# define ESC			53
# define SPACE			49
# define NUM_PAD_PLUS	69
# define NUM_PAD_MINUS	78
# define PLUS			24
# define MINUS			27

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
  JULIA
} t_type;

typedef enum {
  BW,
  COLOR1
} t_color;

typedef struct s_fractol {
	t_data		img;
	void		*mlx;
	void		*win;
	t_type		type; // fractal type
	t_color		color;
	int			iter;
	int			k_fixed;
	t_complex	k; // for julia
	t_complex	min;
	t_complex	max;
	t_complex	scale;
	double		zoom;
}				t_fractol;

double	ft_atof(char *str);

#endif
