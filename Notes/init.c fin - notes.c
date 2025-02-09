#include "fractol.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * If MALLOC goes bad (improbable)
*/
static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}



static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4; // 2 ^ 2, my hypotenuse
	fractal->iterations_defintion = 42; 
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	// zoom factor
	fractal->zoom = 1.0;
}


static void	events_init(t_fractal *fractal)
//configura los eventos de la ventana donde se dibujan los fractales. 
{
	mlx_hook(fractal->mlx_window,
			KeyPress,//cuando se presiona una tecla del teclado se llama a la función key_handler
			KeyPressMask,
			key_handler,
			fractal);
	mlx_hook(fractal->mlx_window, 
			ButtonPressMask,
			mouse_handler,//se asocia al evento de hacer click con el ratón en la ventana se llama a la función mouse_handler
			ButtonPress,
			fractal);
	mlx_hook(fractal->mlx_window,
			DestroyNotify,//Este evento se activa cuando la ventana se cierra. Llama a la función close_handler,
			//que generalmente se usa para liberar recursos o cerrar la aplicación correctamente.
			StructureNotifyMask,
			close_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			MotionNotify,//Este evento ocurre cuando el ratón se mueve dentro de la ventana. Se asocia a la función julia_track,
			//que probablemente actualiza algo relacionado con el fractal de Julia a medida que el ratón se mueve (por ejemplo,
			//cambiar parámetros del fractal en tiempo real
			PointerMotionMask,
			julia_track,
			fractal);
}

/*
 * INIT 
 * ~mlx
 * ~listening events
 * ~hooks data
*/
void	fractal_init(t_fractal *fractal)
{
	//MLX stuff
	fractal->mlx_connection = mlx_init();//Se inicia la conexión a la librería mlx
	if (NULL == fractal->mlx_connection)//Si no se puede inicializar, se llama a malloc_error() para gestionar el error.
		malloc_error();
	//Se crea una nueva ventana con un tamaño de WIDTH x HEIGHT y se le asigna un título usando el campo fractal->name
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, mlx_ptr:
										WIDTH, size_x:
										HEIGHT, size_y:
										fractal->name); tittle:
	if (NULL == fractal->mlx_window)//Si la ventana no se crea correctamente, se destruye la conexión y se llama a malloc_error(
	{
		mlx_destroy_display(fractal->mlx_connection); mlx_ptr:
		free(fractal->mlx_connection); ptr:
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,//Se crea una nueva imagen en la memoria para dibujar el fractal
										WIDTH, HEIGHT);
	if (NULL == fractal->img.img_ptr)//Si no se puede crear la imagen, se destruyen la ventana y la conexión, y se llama a malloc_error()
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window); mlx_ptr: win_ptr:
		mlx_destroy_display(fractal->mlx_connection); mlx_ptr:
		free(fractal->mlx_connection); ptr:
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,//Esta línea obtiene la dirección de memoria donde se almacenan los píxeles de la imagen creada
												&fractal->img.bpp,//se obtienen los bytes por pixel
												&fractal->img.line_len,//la longitud de línea de la imagen
												&fractal->img.endian);//y el orden de los bytes 
	events_init(fractal);//Después de crear la ventana y la imagen, se llama a events_init(fractal) para configurar los eventos que 
	//responderán a las interacciones del usuario
	data_init(fractal);//Finalmente, se llama a data_init(fractal) para inicializar cualquier otro dato relacionado con el fractal
}
