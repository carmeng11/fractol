Hola!!  
Esta guía pretende ayudar a tod@s los que os sentís un poco perdidos cuando os  enfrentáis por primera vez a un proyecto sobre fractales. Lo que empezaron siendo apuntes para mi propio estudio y entendimiento decidí compartirlo para facilitar el camino, sobre todo si os sentís superados por el proyecto, bien porque nunca habéis trabajo con la librería gráfica, o porque pensáis que las matemáticas del proyecto son demasiado complejas.
Espero que os facilite el camino, en el repositorio dejo este documento sobre la teoría de los fractales, los archivos de los que se compone el proyecto y el proyecto en sí, donde hay dos carpetas, la carpeta src contiene el código limpio de comentarios, y la carpeta notes (pendiente subir), donde están los ficheros con las mismas funciones explicadas paso a paso. 
Mi proyecto tiene la parte bonus integrada, todos los puntos excepto uno, que espero en un futuro completarlo.


**Fractales de Mandelbrot y Julia**

Los conjuntos de mandelbrot y julia son dos tipos de fractales que se generan a partir de funciones complejas, son conjuntos en el plano complejo que se definen a partir de la iteración de una fórmula, y tienen representaciones visuales muy atractivas.
\[ z_{n+1} = z_n^2 + c \]
En el conjunto de mandelbrot z es un número complejo que comienza en 0 y c tb es un número complejo que representa cada punto en el plano. El conjunto incluye aquellos valores de c para los cuales la secuencia generada no tiende al infinito cuando se itera.
En el conjunto de julia (comienza con diferentes valores para z y c es fijo)
Para un número complejo fijo \( c \), el conjunto de Julia correspondiente se define utilizando la misma función:

\[ z_{n+1} = z_n^2 + c \]
Sin embargo, aquí comenzamos con diferentes valores iniciales para \( z_0 \). El resultado es otro fractal, cuyo aspecto depende del valor específico elegido para \( c \)
El conjunto de Julia para un valor fijo de c se define como el conjunto de puntos que no tienden al infinito cuando se aplica la iteración repetidamente.
Si pertenece al conjunto de Mandelbrot, entonces el conjunto de Julia correspondiente es conexo, es decir, está "unido" en una sola pieza.
Si no pertenece al conjunto de Mandelbrot, entonces el conjunto de Julia correspondiente se descompone en varios fragmentos disconexos.


En resumen:
- **Mandelbrot:** Esquema global donde estudiamos cómo cambia las trayectorias según variamos \(c\).
- **Julia:** Estudia las trayectorias específicas resultantes desde diferentes valores iniciales dados ese mismo parámetro fijo (\(c\)).
. **Estructura Fractal**: Tanto el conjunto de Mandelbrot como los conjuntos de Julia son fractales, lo que significa que tienen estructuras que se repiten a diferentes escalas.
.Al hacer zoom en cualquier parte del conjunto, se pueden encontrar estructuras similares a las originales.

**Diseño de la estructura de archivos:**

- **main.c:** Archivo principal donde se manejarán los argumentos de la línea de comandos, se inicializarán los parámetros de la ventana y se llamarán las funciones que gestionarán los fractales.
- **init.c:** Aquí están las funciones para la conexión con la librería gráfica MiniLibX,  y donde definimos algunos de los valores de nuestro fractal como el valor de escape, número de iteraciones, zoom y valores de desplazamiento del eje x e y.
- **events.c:** Funciones donde se representan las interacciones del usuario con la ventana, eventos de teclado, ratón.
- **fractol.c:** Funciones que calculan los conjuntos de Mandelbrot y Julia. Aquí se manejan las ecuaciones matemáticas y la profundidad de los fractales. Este archivo no se utiliza en el proyecto, la fórmula matemática se utiliza en la función handle_pixel.c, pero este fichero es fundamental si queréis entender cómo se genera en fractal con la fórmula en el plano complejo, formado por un eje real, el eje x y un eje imaginario, el eje y.
- **render.c:** Funciones encargadas de renderizar los fractales en la ventana utilizando la miniLibX.
- **string_utils.c:** Funciones auxiliares como el manejo de parámetros de entrada, conversión de valores, y otras funciones comunes (por ejemplo, manejo de errores, y de memoria).
- **math_utils.c:** Funciones matemáticas como hallar la suma y el cuadrado de números complejos o el mapeo del eje de coordenadas del plano de la ventana en pixeles al plano complejo donde se dibuja el fractal.
- **makefile:** Un Makefile para compilar el proyecto con las reglas all, clean, fclean y re
