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

### Referencias APA
Aller, Á. (2020, junio 10). ¿Cómo funciona la paginación de memoria? Profesional Review; Miguel Ángel Navas. https://www.profesionalreview.com/2020/06/10/como-funciona-la-paginacion-de-memoria/

¿Cómo se compara la segmentación con otras técnicas de administración de memoria, como la paginación o la memoria virtual? (2023, marzo 4). Linkedin.com; www.linkedin.com. https://es.linkedin.com/advice/3/how-do-you-compare-segmentation-other-memory?lang=es

Dominguez, A. (2016, abril 15). Paginación y segmentación. Operating Systems. https://sofilethings.wordpress.com/2016/04/15/paginacion-y-segmentacion/


2. Escribe un programa que simule una tabla de páginas para procesos
con acceso aleatorio a memoria virtual.


```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PAGINAS 16    
#define TAMANO_PAGINA 4096 
#define NUM_MARCOS 8    


typedef struct {
    int marco;    
    int presente; 
} EntradaTablaPaginas;


EntradaTablaPaginas tabla_paginas[NUM_PAGINAS];


void inicializar_tabla_paginas() {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        tabla_paginas[i].marco = -1;  
        tabla_paginas[i].presente = 0; 
    }
}

void cargar_pagina(int pagina, int *marcos_disponibles, int *num_marcos_libres) {
    if (*num_marcos_libres == 0) {
        printf("No hay marcos disponibles para cargar la pagina %d.\n", pagina);
        return;
    }

    int marco = marcos_disponibles[--(*num_marcos_libres)];
    tabla_paginas[pagina].marco = marco;
    tabla_paginas[pagina].presente = 1;

    printf("Pagina %d cargada en el marco %d.\n", pagina, marco);
}

void traducir_direccion(int direccion_logica, int *marcos_disponibles, int *num_marcos_libres) {
    int pagina = direccion_logica / TAMANO_PAGINA; 
    int desplazamiento = direccion_logica % TAMANO_PAGINA; 

    printf("Accediendo a direccion logica: %d (Pagina: %d, Desplazamiento: %d)\n", 
           direccion_logica, pagina, desplazamiento);

    if (tabla_paginas[pagina].presente) {
        int direccion_fisica = tabla_paginas[pagina].marco * TAMANO_PAGINA + desplazamiento;
        printf("Direccion fisica: %d (Marco: %d, Desplazamiento: %d)\n", 
               direccion_fisica, tabla_paginas[pagina].marco, desplazamiento);
    } else {
        printf("Fallo de pagina: La pagina %d no esta en memoria.\n", pagina);
        cargar_pagina(pagina, marcos_disponibles, num_marcos_libres);
    }
}

int main() {
    int marcos_disponibles[NUM_MARCOS]; 
    int num_marcos_libres = NUM_MARCOS;


    for (int i = 0; i < NUM_MARCOS; i++) {
        marcos_disponibles[i] = i;
    }

    inicializar_tabla_paginas();

    srand(time(NULL)); 

    int num_accesos;
    printf("Numero de accesos aleatorios a generar: ");
    scanf("%d", &num_accesos);

    for (int i = 0; i < num_accesos; i++) {
        int direccion_logica = rand() % (NUM_PAGINAS * TAMANO_PAGINA);
        traducir_direccion(direccion_logica, marcos_disponibles, &num_marcos_libres);
        printf("\n");
    }

    return 0;
}

```

# Administración de memoria virtual
Escribe un código que implemente el algoritmo de reemplazo de página
"Least Recently Used" (LRU).
```C
#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGINAS 100  
#define NUM_MARCOS 4    

int buscar_pagina(int marcos[], int num_marcos, int pagina) {
    for (int i = 0; i < num_marcos; i++) {
        if (marcos[i] == pagina) {
            return i;  
        }
    }
    return -1; 
}

int encontrar_marco_lru(int tiempo[], int num_marcos) {
    int lru = 0;  
    for (int i = 1; i < num_marcos; i++) {
        if (tiempo[i] < tiempo[lru]) {
            lru = i;
        }
    }
    return lru;
}

void simular_lru(int paginas[], int num_paginas, int num_marcos) {
    int marcos[num_marcos];   
    int tiempo[num_marcos];      
    int fallos_pagina = 0;      
    int reloj = 0;              

    for (int i = 0; i < num_marcos; i++) {
        marcos[i] = -1;
        tiempo[i] = 0;
    }

    printf("\nReferencias de pagina y estado de memoria:\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("| Pagina Referenciada | Fallo de Pagina | Estado de Memoria Fisica            |\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_paginas; i++) {
        int pagina_actual = paginas[i];
        reloj++;

        int indice = buscar_pagina(marcos, num_marcos, pagina_actual);

        if (indice != -1) {
            tiempo[indice] = reloj;
            printf("| %-20d | %-16s | ", pagina_actual, "No");
        } else {
            fallos_pagina++;
            int marco_a_reemplazar;

            bool marco_libre = false;
            for (int j = 0; j < num_marcos; j++) {
                if (marcos[j] == -1) {
                    marco_libre = true;
                    marco_a_reemplazar = j;
                    break;
                }
            }

            if (!marco_libre) {
                marco_a_reemplazar = encontrar_marco_lru(tiempo, num_marcos);
            }

            marcos[marco_a_reemplazar] = pagina_actual;
            tiempo[marco_a_reemplazar] = reloj;
            printf("| %-20d | %-16s | ", pagina_actual, "Si");
        }

        for (int j = 0; j < num_marcos; j++) {
            if (marcos[j] != -1) {
                printf("%d ", marcos[j]);
            } else {
                printf("- ");
            }
        }
        printf("|\n");
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("Total de fallos de pagina: %d\n", fallos_pagina);
}

int main() {
    int num_paginas;
    printf("Ingrese el numero de referencias de pagina: ");
    scanf("%d", &num_paginas);

    int paginas[num_paginas];
    for (int i = 0; i < num_paginas; i++) {
        printf("Ingrese la referencia de pagina °%d: ", i + 1);
        scanf("%d", &paginas[i]);
    }

    printf("Numero de marcos en memoria fisica: %d\n", NUM_MARCOS);
    simular_lru(paginas, num_paginas, NUM_MARCOS);

    return 0;
}

```
Diseña un diagrama que represente el proceso de traducción de direcciones
virtuales a físicas en un sistema con memoria virtual.

![Diagrama de traducción de e direcciones
virtuales a físicas](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/direccionesvirtualesafisicas.png)

# Integración

Analiza un sistema operativo moderno (por ejemplo, Linux o Windows)
e identifica cómo administra la memoria virtual.

## Linux

1. Paginación y Segmentación
Linux utiliza una combinación de paginación y segmentación para gestionar la memoria. La memoria se divide en bloques de tamaño fijo llamados páginas. Cada proceso en Linux tiene su propio espacio de direcciones virtuales, que se divide en segmentos y páginas. Esto proporciona una forma eficiente de gestionar la memoria y permite características como la memoria virtual y la protección de memoria.

2. Memoria Virtual
Linux utiliza la memoria virtual para dar a cada proceso la impresión de que tiene acceso a una gran cantidad de memoria, incluso si la memoria física real del sistema es limitada. Esto se logra a través de un sistema de paginación que mapea las direcciones de memoria virtuales a direcciones de memoria físicas.

3. Swap (Intercambio)
Cuando la memoria física se llena, Linux puede mover algunas páginas de memoria a un espacio en disco llamado espacio de intercambio o swap. Esto libera memoria física para otros procesos, pero puede ralentizar el sistema si se utiliza en exceso, ya que acceder al disco es mucho más lento que acceder a la memoria física. Para entender mejor cómo funciona el swap en Linux, puedes leer este artículo.

4. Caché y Buffer
Linux intenta utilizar toda la memoria física disponible de manera eficiente. Cualquier memoria que no esté siendo utilizada para procesos se utiliza para caché de disco y buffers. Esto ayuda a acelerar el acceso a los datos a los que se accede con frecuencia. Si un proceso necesita más memoria, Linux reducirá automáticamente el tamaño de la caché para liberar memoria. Para aprender más sobre cómo Linux usa la caché y los buffers, puedes consultar esta explicación.

5. Asignación y Liberación de Memoria
Linux proporciona una serie de llamadas al sistema para asignar y liberar memoria, como malloc(), calloc(), realloc() y free(). Estas funciones permiten a los procesos solicitar memoria dinámicamente en tiempo de ejecución. Para obtener más información sobre cómo se asigna y se libera memoria en Linux, puedes leer este artículo.

6. OOM Killer
Cuando el sistema se queda sin toda la memoria disponible (física y swap), el kernel de Linux activa un proceso especial llamado OOM Killer (Out of Memory Killer). Este proceso selecciona y mata otros procesos para liberar memoria, utilizando un algoritmo para determinar qué procesos son los mejores candidatos para ser matados.


## Windows
Espacio de direcciones: Cada proceso tiene un espacio virtual aislado. En sistemas de 32 bits, se divide típicamente en 2 GB para el núcleo y 2 GB para el usuario, aunque puede configurarse (por ejemplo, 3 GB/1 GB). En sistemas de 64 bits, el espacio es mucho mayor.

Paginación por demanda: Windows carga en memoria física solo las páginas necesarias, acelerando la traducción con Translation Lookaside Buffers (TLBs).

Archivo de paginación: Usa uno o más archivos de paginación (pagefile.sys) para mover páginas inactivas desde la memoria física, liberando espacio para procesos activos.

Protección y seguridad: Cada página tiene permisos de acceso y Windows incluye mecanismos como DEP (Data Execution Prevention) para prevenir la ejecución de código en áreas de datos y ASLR (Address Space Layout Randomization) para mitigar ataques de memoria.

Optimización: Ajusta dinámicamente el uso de memoria priorizando aplicaciones interactivas y críticas.


## Referencias APA

Ferrer, A. (s/f). Gestión automática de memoria en Linux - alberto@barrahome:~$. Barrahome.org. Recuperado el 30 de noviembre de 2024, de https://www.barrahome.org/gesti%C3%B3n-autom%C3%A1tica-de-memoria-en-linux/


Realiza una simulación en cualquier lenguaje de programación que
emule el swapping de procesos en memoria virtual.

```C

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESOS 5
#define TAMANO_MEMORIA 100  

typedef struct {
    int id;
    int tamano;     
    bool en_memoria;  
} Proceso;

Proceso procesos[MAX_PROCESOS];
int memoria_disponible = TAMANO_MEMORIA;

void inicializar_procesos() {
    for (int i = 0; i < MAX_PROCESOS; i++) {
        procesos[i].id = i + 1;
        printf("Introduce el tamanio del proceso %d (en KB): ", i + 1);
        scanf("%d", &procesos[i].tamano);
        procesos[i].en_memoria = false;
    }
}

void mostrar_estado_memoria() {
    printf("\n=== Estado de la memoria ===\n");
    printf("Memoria disponible: %d KB\n", memoria_disponible);
    printf("Procesos en memoria:\n");
    for (int i = 0; i < MAX_PROCESOS; i++) {
        if (procesos[i].en_memoria) {
            printf("  - Proceso %d (%d KB)\n", procesos[i].id, procesos[i].tamano);
        }
    }
    printf("\n");
}

void cargar_proceso(int id) {
    if (procesos[id].tamano <= memoria_disponible) {
        memoria_disponible -= procesos[id].tamano;
        procesos[id].en_memoria = true;
        printf("Proceso %d cargado en memoria.\n", procesos[id].id);
    } else {
        printf("No hay suficiente memoria para el proceso %d. Realizando swapping...\n", procesos[id].id);

        for (int i = 0; i < MAX_PROCESOS; i++) {
            if (procesos[i].en_memoria) {
                printf("Sacando el proceso %d (%d KB) de la memoria.\n", procesos[i].id, procesos[i].tamano);
                memoria_disponible += procesos[i].tamano;
                procesos[i].en_memoria = false;
                break;
            }
        }

        cargar_proceso(id);
    }
}

int main() {
    int opcion, proceso_id;

    inicializar_procesos();

    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Mostrar estado de la memoria\n");
        printf("2. Cargar un proceso en memoria\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrar_estado_memoria();
                break;
            case 2:
                printf("Introduce el ID del proceso a cargar (1-%d): ", MAX_PROCESOS);
                scanf("%d", &proceso_id);
                if (proceso_id < 1 || proceso_id > MAX_PROCESOS) {
                    printf("ID de proceso invalido.\n");
                } else {
                    cargar_proceso(proceso_id - 1);
                }
                break;
            case 3:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }

    return 0;
}

```




