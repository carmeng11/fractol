/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:15:49 by cagomez-          #+#    #+#             */
/*   Updated: 2025/02/25 19:55:34 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection,
		fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_connection,
		fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_plus)
		fractal->iterations_defintion += 10;
	else if (keysym == XK_minus)
		fractal->iterations_defintion -= 10;
	else if (keysym == XK_c)
		fractal->colorchange = (fractal->colorchange + 1) % 2;
	fractal_render(fractal);
	return (0);
}

// int	mouse_handler(int button, int x, int y, t_fractal *fractal)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == Button5)
// 	{
// 		fractal->zoom *= 0.95;
// 		//fractal->shift_y -= (0.5 * fractal->zoom);
// 		//fractal->shift_x -= (0.5 * fractal->zoom);
// 	}
// 	else if (button == Button4)
// 	{
// 		fractal->zoom *= 1.05;
// 		//fractal->shift_y += (0.5 * fractal->zoom);
// 		//fractal->shift_x += (0.5 * fractal->zoom);
// 		//zoom_in(fractal, x, y);
// 	}
// 	fractal_render(fractal);
// 	return (0);
// }
int	mouse_handler(int button, int x, int y, void *param)
{
	t_fractal	*fractal;

	(void)x;
	(void)y;
	fractal = (t_fractal *)param;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	if (button == Button5)
	{
		zoom_out(fractal, x, y);
	}
	else if (button == Button4)
	{
		zoom_in(fractal, x, y);
	}
	fractal_render(fractal);
	return (0);
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (map(x, -2, +2, WIDTH) * fractal->zoom)
			+ fractal->shift_x;
		fractal->julia_y = (map(y, +2, -2, HEIGHT) * fractal->zoom)
			+ fractal->shift_y;
		fractal_render(fractal);
	}
	return (0);
}

void	zoom_in(t_fractal *fractal, int x, int y)
{
	double	mouse_re;
	double	mouse_img;
	double	x_min;
	double	y_min;
	double	x_max;
	double	y_max;
	
	x_max = 2.0;
	x_min = -2.0;
	y_min = -2.0;
	y_max = 2.0;
	mouse_re = x_min + (x / WIDTH) * (x_max - x_min);
	mouse_img = y_min + (y / HEIGHT) * (y_max - y_min);
	fractal->zoom *= 1.1;
	x_min = mouse_re - (mouse_re - x_min) / 1.1;
	x_max = mouse_re + (x_max - mouse_re) / 1.1;
	y_min = mouse_img - (mouse_img - y_min) / 1.1;
	y_max = mouse_img + (y_max - mouse_img) / 1.1;
}
void	zoom_out(t_fractal *fractal, int x, int y)
{
	double	mouse_re;
	double	mouse_img;
	double	x_min;
	double	y_min;
	double	x_max;
	double	y_max;
	
	x_max = 2.0;
	x_min = -2.0;
	y_min = -2.0;
	y_max = 2.0;
	mouse_re = x_min + (x / WIDTH) * (x_max - x_min);
	mouse_img = y_min + (y / HEIGHT) * (y_max - y_min);
	fractal->zoom /= 1.1;
	x_min = mouse_re - (mouse_re - x_min) * 1.1;
	x_max = mouse_re + (x_max - mouse_re) * 1.1;
	y_min = mouse_img - (mouse_img - y_min) * 1.1;
	y_max = mouse_img + (y_max - mouse_img) * 1.1;
}
