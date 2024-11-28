# REPOSITORIO SISTEMAS OPERATIVOS
### Por: Emiliano Romero García

# Administración de memoria
## Política y filosofía
1. ¿Cuál es la diferencia entre fragmentación interna y externa? Explica
cómo cada una afecta el rendimiento de la memoria.
La fragmentación interna es un tipo de fragmentación que tiene lugar cuando se asigna una memoria más grande a un programa en lugar de la requerida. Aquí el espacio libre se conoce como fragmentación interna. Por otro lado, la fragmentación externa es el tipo de espacio libre que se forma entre bloques de memoria no contagiosos.

Impacto en el rendimiento de la memoria: 
* Fragmentación interna: La memoria asignada pero no utilizada dentro de los bloques queda inactiva, reduciendo la cantidad de memoria disponible para otros procesos.
* Fragmentación externa: Aunque puede haber suficiente memoria total disponible, la dispersión en pequeños fragmentos no contiguos impide que los procesos de gran tamaño se asignen, dejando recursos sin aprovechar.

2. Investiga y explica las políticas de reemplazo de páginas en sistemas
operativos. ¿Cuál consideras más eficiente y por qué?

### Reemplazo FIFO
El algoritmo de reemplazo más sencillo es el primero en entrar, primero en salir. Este algoritmo asocia a cada página el instante en el que se trajo a memoria. Cuando hay que reemplazar una página, se elige la más antigua. Para la cadena de referencias de ejemplo, y suponiendo un total de tres marcos, aplicamos este algoritmo con el resultado de 15 fallos de página.

### Reemplazo Óptimo
 El algoritmo de reemplazo de páginas óptimo sería aquel que eligiera la página de la memoria que vaya a ser referenciada más tarde. Por desgracia, este algoritmo es irrealizable, pues no hay forma de predecir qué páginas referenciará un proceso en el futuro. Como resultado de esto, el algoritmo óptimo se utiliza sobre todo para estudios comparativos. Puede ser útil para saber que un nuevo algoritmo está dentro de 12.3% de lo óptimo en el peor de los casos y dentro del 4.7% en promedio.

### Reemplazo Menos Recientemente Usado o LRU (Least Recently Used)
La principal diferencia entre los algoritmos FIFO y OPT es que el primero utiliza el instante en que entró una página en memoria, y el segundo, utiliza el tiempo en el que se usará la página. Una buena aproximación al algoritmo óptimo se basa en el principio de localidad de referencia de los programas. Las páginas de uso frecuente en las últimas instrucciones se utilizan con cierta probabilidad en las siguientes instrucciones. De manera recíproca, es probable que las páginas que no hayan sido utilizadas durante mucho tiempo permanezcan sin ser utilizadas durante cierto tiempo. Es decir, estamos utilizando el pasado reciente como aproximación de lo que sucederá en el futuro. El algoritmo LRU explota esta idea: al ocurrir un fallo de página se utiliza la página que no haya sido utilizada hace más tiempo. El resultado de aplicar este algoritmo a nuestro ejemplo produce 12 fallos.

### EL algortimo del reloj
Aunque la segunda oportunidad es un algoritmo razonable, es ineficiente e innecesario, puesto que desplaza las páginas en una lista. Un mejor diseño consiste en mantener las páginas en una lista circular, con la forma de un reloj, como se muestra en la figura 7.8. Una manecilla apunta hacia la página más antigua.

![algoritmo del reloj](https://lsi.vc.ehu.eus/pablogn/docencia/manuales/SO/TemasSOuJaen/MEMORIAVIRTUAL/Image19.gif)

### Algoritmo LFU (Last Frequently Used)

Un algoritmo de reemplazo de página menos frecuentemente usada (Least Frequently Used) mantiene un contador del número de referencias que se han hecho para cada página. Se reemplaza la página con el menor recuento. La razón para esta selección es que una página que se usa activamente debe tener un alto número de referencias. Este algoritmo tiene problemas cuando una página se usa mucho en la fase inicial de un proceso, pero después ya no se utiliza. Como se usó bastantes veces, tiene un recuento alto y permanece en memoria aunque ya no se necesite. Una solución consiste en desplazar los recuentos un bit a la derecha a intervalos regulares, formando un recuento promedio de utilización que disminuye exponencialmente.


### El algoritmo MFU (Most Frequently Used)

Otro algoritmo de reemplazo de páginas es el reemplazo más frecuentemente usado, que se basa en el argumento de que la página con el menor recuento probablemente acaba de llegar y aún tiene que usarse. Como se podría esperar, no es común ni el reemplazo MFU ni el LFU porque son costosos y se alejan mucho del reemplazo OPT.

 
### Algoritmo de páginas de uso no reciente o NRU (Not Recently Used)

La mayoría de los ordenadores presentan los bits R (de referencia) y M (de modificación) en las entradas de la tabla de páginas, siendo estos bits actualizados vía hardware. Si el hardware no proporciona dichos bits, éstos pueden ser simulados mediante el software. Para ello, cuando se inicia un proceso se señalan todas sus entradas en la tabla de páginas como si no estuvieran dentro de la memoria. Si se hace referencia a cualquier página, ocurre un fallo de página. El sistema operativo activa entonces el bit R (en sus propias tablas) y cambia la entrada de la tabla de páginas para que apunte hacia la página correcta, poniendo dicha entrada en modo sólo lectura (recordar los bits de permisos). El proceso retoma su ejecución; si se escribe en la página, ocurre otra interrupción por violación de permisos, lo que permite al sistema operativo activar el bit M en sus tablas, cambiando los permisos de la página a lectura y escritura.


### Referencias APA
Admin. (2019, 18 noviembre). Diferencia entre fragmentación interna y fragmentación externa. Diferenciario. https://diferenciario.com/fragmentacion-interna-y-fragmentacion-externa/

(S/f-b). Ehu.eus. Recuperado el 28 de noviembre de 2024, de https://lsi.vc.ehu.eus/pablogn/docencia/manuales/SO/TemasSOuJaen/MEMORIAVIRTUAL/4ReemplazodePaginas.htm

