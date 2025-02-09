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
	t_fractal	fractal; //definimos una vatiable tipo t_fractal que es la estructura que almacena todos los parametros y conf del fractal
//Esta parte valida los argumentos pasados al programa:Si el programa recibe 2 argumentos (ac == 2) y el primer argumento (av[1]) es "mandelbrot",
//o si recibe 4 argumentos (ac == 4) y el primer argumento es "julia"
	if (2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10)
		|| 4 == argc && !ft_strncmp(argv[1], "julia", 5))
//entonces la condición se evalúa como verdadera y entra en el bloque if.
//ft_strncmp es una función que compara los primeros n caracteres de dos cadenas. En este caso, compara av[1] con "mandelbrot" 
//(para el caso del fractal Mandelbrot) o con "julia" (para el caso del fractal Julia

	{
		fractal.name = argv[1];//Se asigna a fractal.name el nombre del fractal (ya sea "mandelbrot" o "julia").
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
			//Si el nombre del fractal es "julia", entonces se leen los parámetros adicionales (av[2] y av[3]) que especifican las coordenadas 
			//julia_x y julia_y, que son constantes utilizadas para calcular el fractal de Julia. Estos parámetros son convertidos de cadenas a 
			//números de tipo double utilizando la función atodbl
		}
		//Inicialización y renderizado del fractal
		//TL;DR
		//Prompt correct, kick off the application
		//1)
		fractal_init(&fractal);//Llama a la función fractal_init, que probablemente inicializa los valores necesarios para renderizar el fractal,
		//como la conexión con la ventana de MiniLibX, la configuración inicial de la imagen y los parámetros del fractal (por ejemplo, número de 
		//iteraciones, valores de escape, etc.).
		//2)
		fractal_render(&fractal);//Llama a la función fractal_render, que se encarga de dibujar el fractal en la ventana. Utiliza la información 
		//almacenada en la estructura fractal (como los parámetros de zoom, desplazamiento y las constantes para el fractal de Julia).
		//3)
		mlx_loop(fractal.mlx_connection);//Inicia el ciclo principal de MiniLibX. Este ciclo mantiene la ventana abierta y actualiza la imagen a 
		//medida que el usuario interactúa con ella (por ejemplo, moviendo el ratón o haciendo zoom). El ciclo sigue ejecutándose hasta que el usuario cierra la ventana.
	}
	else
	{
		putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}	//Si los argumentos no son válidos (por ejemplo, si no se pasa "mandelbrot" o "julia", o si el número de argumentos es incorrecto), el programa entra en el bloque else. Aquí:
		//se imprime un mensaje de error (ERROR_MESSAGE) a través de putstr_fd (que probablemente escribe en el flujo de error estándar stderr).
		//luego, el programa termina con exit(EXIT_FAILURE), lo que indica que hubo un error al ejecutar el programa.
}

/*Resumen del flujo de ejecución:
El programa valida los argumentos de entrada:
Si se pasa el nombre "mandelbrot" o "julia" y el número adecuado de parámetros, procede con la inicialización del fractal.
Si no se cumplen las condiciones, muestra un mensaje de error y termina.
Si la validación es exitosa, se configura el fractal:
Si es "julia", se extraen los parámetros julia_x y julia_y.
Luego, se inicializa el fractal con fractal_init, se renderiza con fractal_render, y finalmente se inicia el bucle de eventos con mlx_loop, que mantiene la ventana activa.
Este programa está diseñado para crear y mostrar fractales de Mandelbrot y Julia según los argumentos proporcionados por el usuario.*/
