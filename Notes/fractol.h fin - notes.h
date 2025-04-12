#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> //TODO debugging
# include <stdlib.h> //malloc free
# include <unistd.h> // write
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"


#define ERROR_MESSAGE "Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <value_1> <value_2>\"\n"

/*
 * We use a square to 
 * keep the rendering math simple
*/
#define WIDTH	800
#define	HEIGHT	800

/*
 * COLORS
*/
#define BLACK       0x000000  // RGB(0, 0, 0)
#define WHITE       0xFFFFFF  // RGB(255, 255, 255)
#define RED         0xFF0000  // RGB(255, 0, 0)
#define GREEN       0x00FF00  // RGB(0, 255, 0)
#define BLUE        0x0000FF  // RGB(0, 0, 255)

// Psychedelic colors
#define MAGENTA_BURST   0xFF00FF  // A vibrant magenta
#define LIME_SHOCK      0xCCFF00  // A blinding lime
#define NEON_ORANGE     0xFF6600  // A blazing neon orange
#define PSYCHEDELIC_PURPLE 0x660066  // A deep purple
#define AQUA_DREAM      0x33CCCC  // A bright turquoise
#define HOT_PINK        0xFF66B2  // As the name suggests!
#define ELECTRIC_BLUE   0x0066FF  // A radiant blue
#define LAVA_RED        0xFF3300  // A bright, molten red

/*
 * COMPLEX value
*/estructura para las coordenadas x real e y iamginario
typedef struct	s_complex
{
	//		real
	double	x;
	//		i
	double	y;
}				t_complex;

/*
 * IMAGE
 * This is basically a pixels buffer
 * values from mlx_get_data_addr()
*/
typedef struct	s_img
{
	void	*img_ptr; //pointer to image struct
	//Es un puntero que hace referencia a la estructura 
	//de imagen creada por la biblioteca (probablemente mlx en este caso,
	//que es la MiniLibX, una biblioteca gráfica utilizada comúnmente en programación de gráficos en C).
	//Este puntero permite interactuar con la imagen creada (puede ser la imagen de la ventana o el lienzo 
	//donde se dibuja el fractal
	char	*pixels_ptr; //points to the actual pixels
	//Este campo es un puntero que apunta directamente a los píxeles de la imagen. En otras palabras, esta variable 
	//es un buffer (o espacio de memoria) donde se almacenan los valores de cada píxel de la imagen. Este buffer es 
	//utilizado para modificar directamente los colores o valores de los píxeles de la imagen.
    //Es importante porque en la generación de fractales, necesitas actualizar la información de los píxeles para dibujar 
	//el fractal en la pantalla
	int		bpp;
	//bpp significa "bits per pixel" (bits por píxel), y este valor indica cuántos bits se usan para representar 
	//un solo píxel en la imagen. En sistemas comunes, esto puede ser 32, 24 o 16 bits, dependiendo de la profundidad de color 
	//de la imagen.
    //Este valor es importante porque ayuda a determinar cómo acceder y manipular los datos de los píxeles en memoria.
	int		endian; // indica el orden de los bytes 
	int		line_len;//line_len es la longitud en bytes de una fila de píxeles en la imagen (el ancho de la imagen en 
	//términos de memoria, no de píxeles).
}				t_img;


/*
 * FRACTAL ID
 * ~ MLX stuff
 * ~ Image 
 * ~ Hooks values
*/
typedef struct	s_fractal
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
}				t_fractal;




/*
 * PROTOTYPES
 * They are basically IOUs to the compiler
*/
//*** strings utils ***
int		ft_strncmp(char *s1, char *s2, int n);
void    putstr_fd(char *s, int fd);
double  atodbl(char *s);

//*** init ***
void    fractal_init(t_fractal *fractal);

//*** render ***
void    fractal_render(t_fractal *fractal);

//*** math ***
double		map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);

//*** hooks_events ***
int			key_handler(int keysym, t_fractal *fractal);

//*** clean_up ***
int    	close_handler(t_fractal *fractal);
int		mouse_handler(int button, int x, int y, t_fractal *fractal);
int		julia_track(int x, int y, t_fractal *fractal);

#endif
