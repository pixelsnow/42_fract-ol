/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/02 22:27:02 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	print_binary(int n)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		if (n & (1 << i))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		if (!(i % 8))
			write(1, " ", 1);
		i--;
	}
	write(1, "\n", 1);
}

int	rgb_to_int(int r, int g, int b)
{
	int	bit;
	int res;
	
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_data *img, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 300)
	{
		j = 0;
		while (j < 300)
		{
			my_mlx_pixel_put (img, i + x, j + y, rgb_to_int(100 + i / 2, 100 + j / 2, 100 + j / 4 + i / 4));
			j++;
		}
		i++;
	}
	
}

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;

	mlx_ptr = mlx_init(); // identifier of the connection to the graphics server
	win_ptr = mlx_new_window(mlx_ptr, 300, 300, "test"); // will need this when we need to draw
	img.img = mlx_new_image(mlx_ptr, 300, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	draw_square(&img, 0, 0);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr); // draws, opens the window, manages events
	return (0);
}
