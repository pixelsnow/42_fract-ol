/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:32:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/08 19:37:50 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static long long	ft_simple_atoi(const char *str)
{
	char		sign;
	long long	res;

	sign = 1;
	res = 0;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*(str++) - '0');
	return (res * sign);
}

static char	*find_point(char *str)
{
	while (*str && *str != '.')
		str++;
	return (str);
}

static int	ft_strlen(const char *str)
{
	int	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}

double	ft_atof(char *str)
{
	double	res;
	char	*decimal;
	int		decimal_len;

	res = ft_simple_atoi(str);
	decimal = find_point(str);
	if (*decimal == '.')
		decimal++;
	decimal_len = ft_strlen(decimal);
	res += ft_simple_atoi(decimal) * pow(10, -decimal_len);
	return (res);
}
