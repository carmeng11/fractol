#include "fractol.h"
#include "minilibx-linux/mlx.h"

/*
 * Put a pixel in my image buffer
*/
static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}
	
/*
 * EASY TOGGLE mandel & julia
*/
static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{	
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x; // c en Julia son las coordenadas que se introducen como argumento al inicio
		c->y = fractal->julia_y;
		//viene en el main     fractal.julia_x = atodbl(argv[2]); fractal.julia_y = atodbl(argv[3]);
	}
	else
	{
		c->x = z->x;// c en mandelbrot son las coordenadas x e y
		c->y = z->y;
	}
}

/*typedef struct	s_complex
{
	//		real
	double	x;
	//		i
	double	y;
}				t_complex;*/
/*typedef struct	s_fractal
{
	char	*name;
	//MLX
	void	*mlx_connection; // mlx_init()
	void	*mlx_window; 	 // mlx_new_window()
	//Image
	t_img	img;

	//Hooks member variables //TODO
	double	escape_value; // hypotenuse lo utiiza en init en ******static void	data_init(t_fractal *fractal)
	int		iterations_defintion; // value tight with the image quality and rendering speed
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;*/

/*
 * 						 ✅ map()
		   	0__________800     -2___________+2    
 *			|			 |     |            |
 *			|			 |	   |            |
 *		800	|			 |     |            |
 *			|			 |     |            |
 *			|			 |     |            |
 *			|____________|     |____________|

 *	
 *		MANDELBROT
 *		z = z^2 + c
 *		z initially is (0, 0)
 *		c is the actual point
 *
 *		z = z^2 + c -> z1 = c + c
 *
 *		JULIA
 *		./fractol julia <real> <i> 
 *		z = pixel_point + constant
*/
static void	handle_pixel(int x, int y, t_fractal *fractal)
//La función handle_pixel() se encarga de calcular el valor de un punto en una imagen fractal, 
//ya sea parte del conjunto de Mandelbrot o del conjunto de Julia. El programa calcula cómo evoluciona 
//la secuencia de valores y determina si un punto pertenece al fractal o si "escapa" (es decir, se aleja al infinito)
//	x, y: Son las coordenadas del píxel en la pantalla donde se va a calcular el valor del fractal.
//fractal: Es un puntero a una estructura que contiene los parámetros del fractal, como el número de iteraciones, 
//los valores de desplazamiento (shift_x, shift_y), y la cantidad de zoom (zoom), entre otros.
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	// pixel coordinate x && y scaled to fit mandel needs 
	//                                 --> 📏 <--			🕹🕹🕹 🕹
	z.x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;
//map(x, -2, +2, 0, WIDTH): La función map() convierte las coordenadas del píxel (en el rango de la pantalla) a un rango en el conjunto 
//complejo. En este caso, mapea las coordenadas x del rango de 0 a WIDTH (ancho de la ventana) a un rango en el eje real del conjunto de 
//Mandelbrot, que va de -2 a +2. El mismo mapeo ocurre para las coordenadas y en el eje imaginario (de +2 a -2).
//fractal->zoom: Escala las coordenadas del fractal para ajustarse al nivel de zoom.
//fractal->shift_x y fractal->shift_y: Desplazamientos en el eje real e imaginario, permitiendo mover la vista del fractal.
//double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
	mandel_vs_julia(&z, &c, fractal);
//Esta función, probablemente, define si estamos trabajando con el conjunto de Mandelbrot o Julia y asigna el valor de c. Para Mandelbrot, 
//c será el punto del plano complejo que corresponde a las coordenadas actuales de x e y. Para Julia, c es un valor constante predefinido 
//que se proporciona como argumento de entrada al programa.

	// How many times you want to iterate z^2 + c
	//	to check if the point escaped?
	while (i < fractal->iterations_defintion)
	{
		// actual z^2 + c	
		// z = z^2 + c
		z = sum_complex(square_complex(z), c);
//z = sum_complex(square_complex(z), c): Calcula la siguiente iteración de , donde square_complex(z) eleva z al cuadrado y sum_complex 
//suma c al resultado.
		
		// Is the value escaped???
		// if hypotenuse > 2 i assume the point has escaped
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
//Condición de escape:
//Si la magnitud de z (es decir, ) es mayor que un valor de escape (por ejemplo, 2), se considera que el punto ha escapado y no forma 
//parte del fractal.
		{
//En ese caso, se asigna un color al píxel basado en cuántas iteraciones se necesitaron antes de que el valor escapara. Este valor se mapea 
//a un color entre BLACK y WHITE, y luego se coloca en la imagen.
			color = map(i, BLACK, WHITE, 0, fractal->iterations_defintion);
			my_pixel_put(x, y, &fractal->img, color);
//Esta función coloca el color calculado en el píxel correspondiente de la imagen en el buffer de píxeles.

			return ;
		}
		++i;	
	}
	// We are in MANDELBROT given the iterations made
	my_pixel_put(x, y, &fractal->img, WHITE);
//Caso en que el punto no escapa:
//Si el punto no ha escapado después del número máximo de iteraciones, se considera que está dentro del fractal 
//y se le asigna un color blanco:
}



/*
 * Actual 🍖
 *
 * 				
 *		   	____800_______
 *			|			 |
 *			|			 |
 *		800	|			 |
 *			|			 |
 *			|			 |
 *			|____________|
*/
// renderizarlos en una ventana utilizando la biblioteca gráfica MiniLibX 
void	fractal_render(t_fractal *fractal)
//la variable t_fractal contiene toda la información necesaria para generar y mostrar el fractal, como la conexión con la ventana 
//(mlx_connection), la ventana en sí (mlx_window), y la imagen que se va a renderizar (img).
{
	int	x;
	int	y;
//con las variables x e y recorreremos todos los pixeles de la ventana donde se mostrará el fractal
	y = -1;
	while (++y < HEIGHT)
	//este bucle recorre todas las filas de pixeles mientras sea menor que height
	{
		x = -1;
		while (++x < WIDTH)
		//similar al anterior, recorre todas las columnas de pixels
		{
			handle_pixel(x, y, fractal);//Esta línea es crucial, ya que llama a la función handle_pixel, pasándole las coordenadas 
			//del píxel (x, y) y el puntero al objeto fractal. La función handle_pixel probablemente se encarga de calcular el color 
			//o el valor del fractal para ese píxel específico
		}
	}
	//Finalmente, después de haber recorrido todos los píxeles de la ventana, la función mlx_put_image_to_window 
	//se llama para renderizar la imagen en la ventana.
	mlx_put_image_to_window(fractal->mlx_connection, //Es la conexión a la librería gráfica (MiniLibX).
							fractal->mlx_window, //Es la ventana en la que se mostrará la imagen.
							fractal->img.img_ptr, //Es el puntero a la imagen que contiene los píxeles ya calculados del fractal.
							0, 0); //Son las coordenadas en la ventana donde se coloca la imagen. En este caso, la imagen 
							//se coloca en la esquina superior izquierda (coordenada 0, 0).

}
