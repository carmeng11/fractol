/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:16:20 by cagomez-          #+#    #+#             */
/*   Updated: 2025/02/17 19:34:43 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	ft_strncmp(char *s1, char *s2, int n)
{
	if (NULL == s1 || NULL == s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1 != '\0')
	{
		++s1;
		++s2;
		--n;
	}
	// chars are basically 1 byte int
	// 🚨 when 0, strings are equal !! 🚨
	return (*s1 - *s2);
}

/*
 * RECURSION
*/
void	putstr_fd(char *s, int fd)
{
	if (NULL == s || fd < 0)
		return ;
	if (*s != '\0')
	{
		write(fd, s, 1);
		putstr_fd(s + 1, fd);
	}
}

/*
 * ALPHA TO DOUBLE
 * similar to atoi, but dealing with floats
 * takes the cmnd line args and
 * converts to long double (typedef ldbl)
*/
double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - '0');
	if ('.' == *s)
		++s;
	while (*s)
	{
		pow /= 10;
		fractional_part = fractional_part + (*s++ - '0') * pow;
	}
	return ((integer_part + fractional_part) * sign);
}

/*int	ft_comprobar(char *s1, char *s2, int i)
{
	if (((s1[i] >= '0' && s1[i] <= '9')
		|| s1[i] == '.' || s1[i] == '-'
			|| s1[i] == '+') && ((s2[i] >= '0' && s2[i] <= '9')
				|| s2[i] == '.' || s2[i] == '-' || s2[i] == '+'))
		return (0);
	return (1);
}*/

void check_julia(t_fractal *fractal, char **argv, int argc)
{
	int	i;

	i = 0;
	fractal->name = argv[1];
	//t_fractal	fractal; poniendolo de esta manera daba error
	if ((argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0))
	{
		while (argv[2][i] != '\0' && argv[3][i] != '\0')
		{
			if (((argv[2][i] >= '0' && argv[2][i] <= '9') || argv[2][i] == '.' || argv[2][i] == '-' 
				|| argv[2][i] == '+') && ((argv[3][i] >= '0' && argv[3][i] <= '9') 
					|| argv[3][i] == '.' || argv[3][i] == '-' || argv[3][i] == '+'))
				{
					fractal->julia_x = atodbl(argv[2]);
					fractal->julia_y = atodbl(argv[3]);
				}
				else 
				{
					putstr_fd(ERROR_MESSAGE2, STDERR_FILENO);
					exit(EXIT_FAILURE);
				}
			i++;
		}
	}
}

// int	ft_str_is_dec(char *nb)
// {
// 	int	point_found;

// 	point_found = 0;//se usa para rastrear si ha encontrado un pto
// 	if (*nb == '+' || *nb == '-')//salta los signos
// 		nb++;
// 	if (*nb == '\0')//si se ha llegado al final devuelve 0 indicando que no es decimal
// 		return (0);
// 	while (*nb)//el bucle continuará hasta el final de la cadena
// 	{
// 		if (*nb == '.')
// 		{
// 			if (point_found)//si ya lo ha encontrado devuelve 0 pq un num no puede tener + de una caracter decimal
// 				return (0);
// 			point_found = 1;//si no se ha encontrado punto se establece point_found = 1
// 		} //verificación de dígitos
// 		else if (!(ft_isdigit(*nb))) //si es dígito devuelve 1, por lo que si no lo es devuelve 0
// 		//indicando que la cadena no es un num decimal válido
// 			return (0);
// 		nb++;
// 	}
// 	return (1);
// }
// int	ft_str_isdigit(char *str)
// {
// 	while (*str)
// 	{
// 		printf("%c\n", *str);
// 		if (!(ft_isdigit(*str)))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }
// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	return (0);
// }