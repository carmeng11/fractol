#include "fractol.h"

//ES COMO LA DEL EX PERO CHEQUEAMOS SOLO HASTA N
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
//FUCION EXRANK02
/*int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}*/

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
//CHEQUEAR CREO QUE DA ERROR EN LA LIBFT EL WHILE CON EL FD LO DABA
/*void	putstr_fd(char *s, int fd)
{
	if (NULL == s || fd < 0)
		return ;
	While(*s)
	{
		write(fd, s, 1);
		S++;
	}
}*/

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
		if ('-' == *s++)//si encuentra signo negativo incrementa s, pasa al siguiente caracter 
		//y como cumple la condicion sign lo pone en negativo
			sign = -sign;
	while (*s != '.' && *s)//mientras no encuentre la parte decimal sacamos cada número multiplicando x 10 y sumando 
	//el siguiente en la cadena, luego lo convertimos a dígito, 48 es el entero equivalente al 0
		integer_part = (integer_part * 10) + (*s++ - 48);
		//result = result * 10 + *str - '0'
		//integer_part = (integer_part * 10) + (*s - '0')
		//s++;
	if ('.' == *s)//Si encuentra un punto decimal, lo salta para empezar a procesar la parte fraccionaria.
		++s;
	while (*s)
	{
		pow /= 10; //lo dividimos entre 10 para procesar la parte fraccionaria empezamos con 0.1
		fractional_part = fractional_part + (*s++ - 48) * pow;
		//fractional_part = fractional_part + (*s - '0') * pow;
		//s++
		//si tengo por ejemplo .56 para sacar el 5 0 = 0 + 5 * 0.1 = 0.5
		// pow ahora vale 0.01 el 6 lo sacamos fractional_part = 0.5 + 6 * 0.01 = 0.5 + 0.06 = 0.56
	}
	return ((integer_part + fractional_part) * sign);
}


/*int	ft_atoi(char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;//si encuentra un signo pasa al siguiente y si es otro signo no hace el while y retorna 0
		//pq sign * result es 0 al tener al inicio declarado result=0
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}*/
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