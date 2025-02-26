/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:15:49 by cagomez-          #+#    #+#             */
/*   Updated: 2025/02/26 21:20:34 by cagomez-         ###   ########.fr       */
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
	if (button == Button4)
	{
		zoom_in(fractal, x, y);
	}
	fractal_render(fractal);
	return (0);
}

// int	mouse_handler(int button, int x, int y, t_fractal *fractal)
// {
// 	double	zoom_factor;
// 	double	cx;
// 	double	cy;

// 	cx = (x - WIDTH / 2) / (0.5 * fractal->zoom * WIDTH) + fractal->shift_x;
// 	cy = (y - HEIGHT / 2) / (0.5 * fractal->zoom * HEIGHT) + fractal->shift_y;
// 	zoom_factor = 1.1;
// 	mlx_destroy_display(fractal->mlx_connection);
// 	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,
// 			WIDTH, HEIGHT);
// 	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
// 			&fractal->img.bpp, &fractal->img.line_len,
// 			&fractal->img.endian);
// 	if (button == 4)
// 		fractal->zoom *= zoom_factor;
// 	else if (button == 5)
// 		fractal->zoom /= (zoom_factor * 1.1);
// 	fractal->shift_x = cx - ((x - WIDTH / 2.0) / (0.5 * fractal->zoom * WIDTH));
// 	fractal->shift_x = cy - ((y - HEIGHT / 2.0) / (0.5 * fractal->zoom * HEIGHT));
// 	fractal_render(fractal);
// 	return (0);
// }

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
	double range;
	double	mouse_re;
	double	mouse_img;
		
	range = 4.0 / fractal->zoom;
		mouse_re = fractal->x_min + (x / (double)fractal->width) * (fractal->x_max - fractal->x_min);
	mouse_img = fractal->y_min + (y / (double)fractal->height) * (fractal->y_max - fractal->y_min);
	fractal->zoom *= 1.1;
	range = 4.0 / fractal->zoom;
	fractal->x_min = mouse_re - range * (fractal->move_x / (double)fractal->move_y);
	fractal->x_max = mouse_re + range * (fractal->move_x/ (double)fractal->move_y);
    fractal->y_min = mouse_img - range;
    fractal->y_max = mouse_img + range;
}


void	zoom_out(t_fractal *fractal, int x, int y)
{
	double	range;
	double	mouse_re;
	double	mouse_img;

	range = 4.0 / fractal->zoom;	
	mouse_re = fractal->x_min + (x / (double)fractal->width) * (fractal->x_max - fractal->x_min);
	mouse_img = fractal->y_min + (y / (double)fractal->height) * (fractal->y_max - fractal->y_min);
	fractal->zoom *= 0.9;
	range = 4.0 / fractal->zoom;
	fractal->x_min = mouse_re - range * (fractal->move_x / (double)fractal->move_y);
    fractal->x_max = mouse_re + range * (fractal->move_x / (double)fractal->move_y);
	fractal->y_min = mouse_img - range;
	fractal->y_max = mouse_img + range;
}

