/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:47:43 by vvagapov          #+#    #+#             */
/*   Updated: 2023/06/02 21:04:11 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init(); // identifier of the connection to the graphics server
	win_ptr = mlx_new_window(mlx_ptr, 300, 300, "test"); // will need this when we need to draw
	mlx_loop(mlx_ptr); // draws, opens the window, manages events
	return (0);
}
