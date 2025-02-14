/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:02:30 by cagomez-          #+#    #+#             */
/*   Updated: 2025/02/12 21:21:41 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * PROJECT
 *
 * ~Julia and Mandelbrot
 * ~Infinite Zoom
 * ~Able to take command line args to disipline
 * 		which fractal render
 * ~Able to take command line args to shape Julia, i.e x y coordinates
 * ~ESC closes the process with no leaks
 * ~Click on the X window, closes the process leaks free
 *
 * * 🚨 Code has to be norminetted 🚨
 * 		~there are comments everywhere for clarity
 * 		~i go always on the next line to better see the function inputs
 * 		tldr->Don't git clone and push.

*/

#include "fractol.h"
#include "minilibx-linux/mlx.h"

/*
 * I HAVE 2 KINDA PROMPTS
 * 		~./fractol mandelbrot
 * 		~./fractol julia <real> <i>
 *
 * 	The main function is a TL,DR
 * 	of your application
 *
*/
int	main(int argc, char **argv)
{
	t_fractal	fractal;
	if ((argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		|| (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0))
	{
		fractal.name = argv[1];
		if (ft_strncmp(fractal.name, "julia", 5) == 0 && ft_str_isdigit(argv[2]) && ft_str_isdigit(argv[3]))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
		}
		else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		{
		}
		else
		{
			putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
	{
		putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
