/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:16:13 by cagomez-          #+#    #+#             */
/*   Updated: 2025/02/26 20:56:36 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (unscaled_num) / (old_max) + new_min);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

t_complex	square_complex_abs(t_complex z)
{
	t_complex	result;

	result.x = ft_fabs(z.x) * ft_fabs(z.x) - ft_fabs(z.y) * ft_fabs(z.y);
	result.y = 2 * ft_fabs(z.x) * ft_fabs(z.y);
	return (result);
}
double	ft_fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}
