#include "fractol.h"


/*
 * [0..799] -> [-2..+2]
 *
*/
double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}
// esta funcion la utiliza para cambiar la escala de las coordenadas -2 0.5 -1 1 a la ventana de 800 pixeles
//manteniendo las proporciones

/*
 * SUM complex
 *
 * fairly easy is vector addition
*/
t_complex   sum_complex(t_complex z1, t_complex z2)
{
    t_complex   result;

    result.x = z1.x + z2.x;
    result.y = z1.y + z2.y;
    return result;
}


/*
 * SQUARE is trickier
 *
 * real = (x^2 - y^2)
 * i =  2*x*y
*/
t_complex   square_complex(t_complex z)
{
    t_complex   result;
    
    result.x = (z.x * z.x) - (z.y * z.y);
    result.y = 2 * z.x * z.y;
    return result;
}
/*z = z^2 + c;
z^2 = (x^2 - y^2) + 2 * x * yi; ***necesitamos la función de calcular el cuadrado de un num complejo
      *****El num real es (x^2 - y^2)
      *****El num imaginario es (2 * x * yi)
z = ((x^2 - y^2) + 2 * x * yi) + c: ****necesitamos la función de calcular la suman del cuadrado de z + c*/










