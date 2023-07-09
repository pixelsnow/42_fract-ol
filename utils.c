/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:09:38 by vvagapov          #+#    #+#             */
/*   Updated: 2023/07/09 20:16:56 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	init_complex(double re, double im)
{
	t_complex	res;

	res.re = re;
	res.im = im;
	return (res);
}