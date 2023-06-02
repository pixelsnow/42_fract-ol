/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/02 21:50:25 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>

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

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		pixel;
	int		colour;

	mlx_ptr = mlx_init(); // identifier of the connection to the graphics server
	win_ptr = mlx_new_window(mlx_ptr, 300, 300, "test"); // will need this when we need to draw
	
	colour = rgb_to_int(200, 0, 100);
	print_binary(200);
	print_binary(100);
	print_binary(colour);
	pixel = mlx_pixel_put (mlx_ptr, win_ptr, 100, 100, colour);
	mlx_loop(mlx_ptr); // draws, opens the window, manages events
	return (0);
}
