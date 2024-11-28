# REPOSITORIO SISTEMAS OPERATIVOS
Por: Emiliano Romero García

# Política y filosofía
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


### Algoritmo LFU (Last Frequently Used)
Un algoritmo de reemplazo de página menos frecuentemente usada (Least Frequently Used) mantiene un contador del número de referencias que se han hecho para cada página. Se reemplaza la página con el menor recuento. La razón para esta selección es que una página que se usa activamente debe tener un alto número de referencias. Este algoritmo tiene problemas cuando una página se usa mucho en la fase inicial de un proceso, pero después ya no se utiliza. Como se usó bastantes veces, tiene un recuento alto y permanece en memoria aunque ya no se necesite. Una solución consiste en desplazar los recuentos un bit a la derecha a intervalos regulares, formando un recuento promedio de utilización que disminuye exponencialmente.


### El algoritmo MFU (Most Frequently Used)
Otro algoritmo de reemplazo de páginas es el reemplazo más frecuentemente usado, que se basa en el argumento de que la página con el menor recuento probablemente acaba de llegar y aún tiene que usarse. Como se podría esperar, no es común ni el reemplazo MFU ni el LFU porque son costosos y se alejan mucho del reemplazo OPT.

 
### Algoritmo de páginas de uso no reciente o NRU (Not Recently Used)
La mayoría de los ordenadores presentan los bits R (de referencia) y M (de modificación) en las entradas de la tabla de páginas, siendo estos bits actualizados vía hardware. Si el hardware no proporciona dichos bits, éstos pueden ser simulados mediante el software. Para ello, cuando se inicia un proceso se señalan todas sus entradas en la tabla de páginas como si no estuvieran dentro de la memoria. Si se hace referencia a cualquier página, ocurre un fallo de página. El sistema operativo activa entonces el bit R (en sus propias tablas) y cambia la entrada de la tabla de páginas para que apunte hacia la página correcta, poniendo dicha entrada en modo sólo lectura (recordar los bits de permisos). El proceso retoma su ejecución; si se escribe en la página, ocurre otra interrupción por violación de permisos, lo que permite al sistema operativo activar el bit M en sus tablas, cambiando los permisos de la página a lectura y escritura.

### Referencias APA
Admin. (2019, 18 noviembre). Diferencia entre fragmentación interna y fragmentación externa. Diferenciario. https://diferenciario.com/fragmentacion-interna-y-fragmentacion-externa/

(S/f-b). Ehu.eus. Recuperado el 28 de noviembre de 2024, de https://lsi.vc.ehu.eus/pablogn/docencia/manuales/SO/TemasSOuJaen/MEMORIAVIRTUAL/4ReemplazodePaginas.htm


# Memoria real
Escribe un programa en C o Python que simule la administración de
memoria mediante particiones fijas.

Diseña un algoritmo para calcular qué procesos pueden ser asignados
a un sistema con memoria real limitada utilizando el algoritmo de
"primera cabida".

```C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PARTICIONES 10
#define MAX_PROCESOS 10

typedef struct {
    int tamano;     
    bool ocupado;
    int proceso_id;
} Particion;

typedef struct {
    int id;
    int tamano;   
    int particion_asignada;
} Proceso;

Particion particiones[MAX_PARTICIONES];
Proceso procesos[MAX_PROCESOS];
int num_particiones = 0;
int num_procesos = 0;

void mostrar_memoria() {
    printf("Estado de la memoria:\n");
    for (int i = 0; i < num_particiones; i++) {
        printf("Particion %d: Tamano = %d KB, ", i + 1, particiones[i].tamano);
        if (particiones[i].ocupado)
            printf("Ocupado por Proceso %d\n", particiones[i].proceso_id);
        else
            printf("Libre\n");
    }
}

void definir_particiones() {
    int tamano_total, tamano;
    printf("Define el tamano total de la memoria (en KB): ");
    scanf("%d", &tamano_total);

    printf("Cuantas particiones quieres crear (max %d): ", MAX_PARTICIONES);
    scanf("%d", &num_particiones);

    int suma_tamanos = 0;
    for (int i = 0; i < num_particiones; i++) {
        printf("Tamano de la particion %d (en KB): ", i + 1);
        scanf("%d", &tamano);
        if (suma_tamanos + tamano > tamano_total) {
            printf("No hay suficiente memoria restante. Intenta un tamano menor.\n");
            i--;
            continue;
        }
        particiones[i].tamano = tamano;
        particiones[i].ocupado = false;
        particiones[i].proceso_id = -1;
        suma_tamanos += tamano;
    }
}

void asignar_por_primera_cabida() {
    int tamano;
    printf("Tamano del nuevo proceso (en KB): ");
    scanf("%d", &tamano);

    for (int i = 0; i < num_particiones; i++) {
        if (!particiones[i].ocupado && particiones[i].tamano >= tamano) {
            procesos[num_procesos].id = num_procesos + 1;
            procesos[num_procesos].tamano = tamano;
            procesos[num_procesos].particion_asignada = i;

            particiones[i].ocupado = true;
            particiones[i].proceso_id = procesos[num_procesos].id;

            printf("Proceso %d asignado a la particion %d\n", procesos[num_procesos].id, i + 1);
            num_procesos++;
            return;
        }
    }
    printf("No hay particiones disponibles para este proceso.\n");
}

void liberar_proceso() {
    int proceso_id;
    printf("ID del proceso a liberar: ");
    scanf("%d", &proceso_id);

    for (int i = 0; i < num_particiones; i++) {
        if (particiones[i].ocupado && particiones[i].proceso_id == proceso_id) {
            particiones[i].ocupado = false;
            particiones[i].proceso_id = -1;
            printf("Proceso %d liberado de la particion %d\n", proceso_id, i + 1);
            return;
        }
    }
    printf("Proceso no encontrado.\n");
}

int main() {
    int opcion;
    definir_particiones();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Asignar proceso\n");
        printf("2. Liberar proceso\n");
        printf("3. Mostrar memoria\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: asignar_por_primera_cabida(); break;
            case 2: liberar_proceso(); break;
            case 3: mostrar_memoria(); break;
            case 4: return 0;
            default: printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }
    return 0;
}

```

# Organización de memoria virtual
1. Investiga y explica el concepto de "paginación" y "segmentación".
¿Cuáles son las ventajas y desventajas de cada técnica?

### Paginación
Se trata de un modelo de organización de memoria física en el que se divide toda la memoria en porciones del mismo tamaño. Esas porciones reciben el nombre de marcos o páginas físicas. Si dividimos la memoria en páginas, podremos gestionarla mejor.

Los marcos se identifican con un número que se denomina «número de página física«. A su vez, cada página física se asigna a un proceso de forma exclusiva. Por otro lado, cada proceso tiene un espacio de páginas lógicas, y cada una se mapea o se asocia a un marco.

La tabla de páginas es el mapeo resultante entre páginas lógicas y físicas. Por tanto, cada proceso tiene su tabla de páginas.

### Ventajas de la paginación
* Es posible comenzar a ejecutar un programa, cargando solo una parte del mismo en memoria, y el resto se cargara bajo la solicitud.

* No es necesario que las paginas estén contiguas en memoria, por lo que no se necesitan procesos de compactación cuando existen marcos de páginas libres dispersos en la memoria.

* Es fácil controlar todas las páginas, ya que tienen el mismo tamaño.

* El mecanismo de traducción de direcciones (DAT) permite separar los conceptos de espacio de direcciones y espacios de memoria. Todo el mecanismo es transparente al usuario.

### Desventajas de la paginación
* El costo de hardware y software se incrementa, por la nueva información que debe manejarse y el mecanismo de traducción de direcciones necesario. Se consumen muchos más recursos de memoria, tiempo en el CPU para su implantación.

* Se deben reservar áreas de memoria para las PMT de los procesos. Al no ser fijo el tamaño de estas, se crea un problema semejante al de los programas (cómo asignar un tamaño óptimo sin desperdicio de memoria, u ovearhead del procesador).

### Segmentación 
La segmentación es una técnica de gestión de memoria que divide la memoria física de una computadora en segmentos de tamaño variable, cada uno de los cuales se puede asignar a un proceso o programa diferente. La segmentación permite un uso más eficiente de la memoria, la protección de los datos y el intercambio de código entre procesos. En este artículo, exploraremos los tipos de segmentación en los sistemas operativos y cómo se comparan con otras técnicas de administración de memoria, como la paginación o la memoria virtual.

### Ventajas de la segmentación
La segmentación tiene varias ventajas sobre otras técnicas de administración de memoria. En primer lugar, la segmentación permite la organización lógica de la memoria, ya que cada segmento puede corresponder a una unidad lógica de un programa, como una función, un módulo o una estructura de datos. Esto hace que sea más fácil para los programadores escribir y depurar código, y para el sistema operativo proteger y compartir segmentos entre procesos. En segundo lugar, la segmentación permite un uso eficiente de la memoria, ya que cada segmento se puede asignar y desasignar de acuerdo con las necesidades del proceso, y los segmentos se pueden reubicar en diferentes ubicaciones de la memoria sin afectar las direcciones lógicas del proceso. En tercer lugar, la segmentación permite el crecimiento dinámico de los segmentos, ya que los segmentos se pueden expandir o contraer en tiempo de ejecución, dependiendo de la disponibilidad de memoria y los requisitos del proceso.

### DESVENTAJAS DE LA SEGMENTACIÓN
* Se complica el manejo de memoria virtual.

*El costo del Hardware y el Software se incrementa.

*Mayor consumo de recursos: memoria, tiempo de CPU, etc.

*Aparece el problema de Fragmentación Externa.

2. Escribe un programa que simule una tabla de páginas para procesos
con acceso aleatorio a memoria virtual.

### Referencias APA
Aller, Á. (2020, junio 10). ¿Cómo funciona la paginación de memoria? Profesional Review; Miguel Ángel Navas. https://www.profesionalreview.com/2020/06/10/como-funciona-la-paginacion-de-memoria/

¿Cómo se compara la segmentación con otras técnicas de administración de memoria, como la paginación o la memoria virtual? (2023, marzo 4). Linkedin.com; www.linkedin.com. https://es.linkedin.com/advice/3/how-do-you-compare-segmentation-other-memory?lang=es

Dominguez, A. (2016, abril 15). Paginación y segmentación. Operating Systems. https://sofilethings.wordpress.com/2016/04/15/paginacion-y-segmentacion/








