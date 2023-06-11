/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:28:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/11 17:51:32 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1500
# define HEIGHT 1200

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>

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

typedef struct s_fractol {
	t_data	img;
	void	*mlx;
	void	*win;
}				t_fractol;

/* typedef struct s_mandelbrot {
	t_data	img;
	void	*mlx;
	void	*win;
}				t_mandelbrot; */

#endif
