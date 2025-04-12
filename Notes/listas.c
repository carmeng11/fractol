
Los miembros de la estructura t_list son:
• content: la información contenida por el nodo.
void *: permite guardar cualquier tipo de información.
• next: la dirección del siguiente nodo, o NULL si el siguiente nodo es el último.

typedef	struct	s_list
{
	void	*content;
	struct s_list	*next;
}			t_list;

t_list	tmp;

tmp = begin_list;

while (tmp->next)
{

}

// en una estructura cuando utiizamos las variables en otras funciones las declaramos siempre 
//t_list   t_complex, con el alias que hemos definido en la estructura
//veamos el ejemplo con t_complex

typedef	struct s_complex
{
	double	x;
	double	y;
}		t_complex;
//Cuando declaramos la funcion sum_complex será de tipo estructura (t_complex) equivalente a cuando ponemos int, void, char

t_complex   sum_complex(t_complex z1, t_complex z2)
{
    //no declaramos la variable result de tipo double, int o char sino que result la declaramos de tipo t_complex, 
    //ya en la estructura está definido que tipo de variable utiliza
    t_complex   result;
    // para indicar que result es del tipo double ponemos result.x si fuera un puntero pondríamos result->x
    result.x = z1.x + z2.x;
    result.y = z1.y + z2.y;
    return result;
}

//duda porqué utilizar una estructura??? como se haría la función sum_complex si no se utiliza una estructura

double  sum_complex(double z1, double z2)
{
    double result;

}

t_complex   square_complex(t_complex z)
{
    t_complex   result;
    
    result.x = (z.x * z.x) - (z.y * z.y);
    result.y = 2 * z.x * z.y;
    return result;
}