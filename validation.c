/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:47:03 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/15 16:51:32 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_invalid_double(char *str)
{
	int	i;
	int	point_found;
	int	empty;

	i = 0;
	empty = 1;
	point_found = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (!point_found)
				point_found = 1;
			else
				return (1);
		}
		else if (str[i] < '0' || str[i] > '9')
			return (1);
		empty = 0;
		i++;
	}
	return (empty);
}

int	validate_julia_args(int ac, char **av)
{
	if (ac != 4)
		return (1);
	if (is_invalid_double(av[2]) || is_invalid_double(av[3]))
		return (1);
	return (0);
}
