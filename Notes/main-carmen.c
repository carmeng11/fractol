/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:16:03 by cagomez-          #+#    #+#             */
/*   Updated: 2025/02/12 17:32:57 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;
	int	i;
	i = 0;
	int j;
	j = 0;
	if ((argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		|| (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0))
	{
		fractal.name = argv[1];
		if ((argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0))
		{
			while (argv[2][i] != '\0')
			{
				while (argv[3][j] != '\0')
				{
					if (((argv[2][i] >= '0' && argv[2][i] <= '9') || argv[2][i] == '.' || argv[2][i] == '-' || argv[2][i] == '+') && ((argv[3][i] >= '0' && argv[3][i] <= '9') || argv[3][i] == '.' || argv[3][i] == '-' || argv[3][i] == '+'))
					{
						fractal.julia_x = atodbl(argv[2]);
						fractal.julia_y = atodbl(argv[3]);
					}
					else 
					{
						putstr_fd(ERROR_MESSAGE2, STDERR_FILENO);
						exit(EXIT_FAILURE);
					}
					j++;
				}
				i++;
			}
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
