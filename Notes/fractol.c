#include <stdio.h>

/*typedef struct s_complex
{
    // x
    double real;
    // y
    double i;
}           t_complex;

int main()
{
    t_complex   z;   //similar al t_list
    //formula z = z^2 + c
    //         c point;
    t_complex   c;   //similar al t_list como cuando se declaraba un t_list tmp, una lista temporal
    //se igualaba a begin_list
    double      tmp_real;

    z.real = 0;   //esto sería como decir tmp->data o tmp->next que es lo que teníamos declarado en las listas. 
    //Cuando las variables declaradas en nuestra estructura no son punteros, en lugar de -> se utiliza .  z.real y z.i
    z.i = 0;

    c.real = 5;
    c.i = 2;
    //SOLUCION DEL VIDEO SUSTITUYO ABAJO EL FOR POR UN WHILE
    // for (int = 0; i < 42; ++i)
    // {
    //     // General formula
    //     // z = z^2 + c;
    //     tmp_real = (z.real * z.real) - (z.i * z.i);
    //     z.i = 2 * z.real * z.i;
    //     z.real = tmp_real;
    //     //Adding c value
    //     z.real += c.real;
    //     z.i += c.i;
    //     printf("iteration n -> %d real %f imaginary%f\n", i);
    // }

    int i = 0;
    while (i < 42)
    {
        // Fórmula general
        // z = z^2 + c;
        tmp_real = (z.real * z.real) - (z.i * z.i);  // tenemos que declarar una variable tmp_real pq z,real abajo tiene que tner el mismo valor que aquí,
                                        //y si ponemos z.real = (z.real * z.real) - (z.i * z.i) abajo ya tiene nuevo valor. El nuevo valor de z.real se lo asignamos justo
                                        //después de aplicar la fórmula al num imaginario
        z.i = 2 * z.real * z.i;
        z.real = tmp_real;
        
        // Sumando el valor de c  siguiendo la fórmula z = z^2 + c
        z.real += c.real; //z.real = z.real + c.real
        z.i += c.i;   //z.i = z.i + c.i
        
        // Imprimir los resultados
        printf("iteration n -> %d real %f imaginary %f\n", i, z.real, z.i);
        
        i++;
    }
}
/*int main(int argc, char **argv)
{           ft_strncmp() -> int
    if ( 2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10))
}*/