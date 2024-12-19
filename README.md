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

* El costo del Hardware y el Software se incrementa.

* Mayor consumo de recursos: memoria, tiempo de CPU, etc.

* Aparece el problema de Fragmentación Externa.

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

# Administración de Entrada/Salida

## Dispositivos y manejadores de dispositivos

Explica la diferencia entre dispositivos de bloque y dispositivos de
carácter. Da un ejemplo de cada uno.

Dispositivos de bloque: se caracterizan por transferir la información en grupos de tamaño fijo, denominados bloques. Como ejemplo tenemos el disco magnético.
Dispositivos de tipo carácter: pueden transmitir la información carácter a carácter. Ejemplo: un modem.

## Referencias APA
Sistemas Operativos II - Cuarta sesión. (s/f). Usal.es. Recuperado el 30 de noviembre de 2024, de http://avellano.fis.usal.es/~ssooii/sesion4.htm


Diseña un programa que implemente un manejador de dispositivos sencillo
para un dispositivo virtual de entrada.

```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 256
#define MAX_REQUESTS 5

typedef struct {
    int id;             
    char data[MAX_BUFFER]; 
    bool atendida;   
} Request;

Request requests[MAX_REQUESTS];
int num_requests = 0;
int next_request_id = 1;

void dispositivo_virtual() {
    if (num_requests >= MAX_REQUESTS) {
        printf("La cola de solicitudes esta llena. No se pueden agregar mas solicitudes.\n");
        return;
    }

    char input[MAX_BUFFER];
    printf("Dispositivo virtual: Ingresa los datos: ");
    fgets(input, MAX_BUFFER, stdin);
    input[strcspn(input, "\n")] = '\0';

    requests[num_requests].id = next_request_id++;
    strncpy(requests[num_requests].data, input, MAX_BUFFER);
    requests[num_requests].atendida = false;

    num_requests++;
    printf("Solicitud creada con ID %d.\n", requests[num_requests - 1].id);
}


void manejador_dispositivo() {
    if (num_requests == 0) {
        printf("No hay solicitudes en la cola para manejar.\n");
        return;
    }

    for (int i = 0; i < num_requests; i++) {
        if (!requests[i].atendida) {
            printf("Manejando solicitud ID %d: Datos: %s\n", requests[i].id, requests[i].data);
            requests[i].atendida = true;
            break;
        }
    }
}


void mostrar_solicitudes() {
    printf("\nEstado de las solicitudes:\n");
    if (num_requests == 0) {
        printf("No hay solicitudes.\n");
        return;
    }

    for (int i = 0; i < num_requests; i++) {
        printf("Solicitud ID %d: Datos: %s, Estado: %s\n",
               requests[i].id,
               requests[i].data,
               requests[i].atendida ? "Atendida" : "Pendiente");
    }
}

int main() {
    int opcion;

    while (1) {
        printf("\nMenu del manejador de dispositivos:\n");
        printf("1. Simular entrada del dispositivo\n");
        printf("2. Manejar una solicitud\n");
        printf("3. Mostrar estado de solicitudes\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1:
                dispositivo_virtual();
                break;
            case 2:
                manejador_dispositivo();
                break;
            case 3:
                mostrar_solicitudes();
                break;
            case 4:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }
    return 0;
}

```

## Mecanismos y funciones de los manejadores de dispositivos

Investiga qué es la interrupción por E/S y cómo la administra el sistema
operativo. Escribe un ejemplo en pseudocódigo para simular este
proceso.

Básicamente una interrupción viene determinada por la ocurrencia de una señal externa que provoca la bifurcación a una dirección especifica de memoria, interrumpiendo momentáneamente la ejecución del programa. A partir de esa dirección se encuentra la rutina de tratamiento que se encarga de realizar la operación de E/S propiamente dicha, devolviendo después el control al punto interrumpido del programa. 

## Referencias APA

(S/f-c). Ucm.es. Recuperado el 1 de diciembre de 2024, de https://www.fdi.ucm.es/profesor/jjruz/web2/temas/Curso05_06/EC9.pdf


## Pseudocódigo:
```
# Cola para gestionar solicitudes de E/S
cola_interrupciones = []

Función que simula la solicitud de E/S
function solicitar_e/s(dispositivo, operacion):
    print("Se solicita operación", operacion, "en el dispositivo", dispositivo)
    # Agregar solicitud a la cola
    cola_interrupciones.append((dispositivo, operacion))

# Manejador de interrupciones
function manejador_interrupcion():
    if cola_interrupciones is not empty:
        solicitud = cola_interrupciones.pop(0)  # Obtener la primera solicitud
        dispositivo, operacion = solicitud
        print("Atendiendo interrupción de E/S para el dispositivo", dispositivo)
        # Simular tiempo de atención
        esperar(2)
        print("Operación", operacion, "completada en el dispositivo", dispositivo)
    else:
        print("No hay interrupciones pendientes.")

# Simulación del sistema principal
function sistema_principal():
    while True:
        print("\n1. Solicitar operación de E/S")
        print("2. Atender interrupción")
        print("3. Salir")
        opcion = leer_entrada_usuario()

        if opcion == 1:
            dispositivo = leer("Introduce el dispositivo (teclado, disco, etc.): ")
            operacion = leer("Introduce la operación (lectura, escritura, etc.): ")
            solicitar_e/s(dispositivo, operacion)
        elif opcion == 2:
            manejador_interrupcion()
        elif opcion == 3:
            print("Saliendo del sistema...")
            break
        else:
            print("Opción inválida.")

```

Escribe un programa que utilice el manejo de interrupciones en un
sistema básico de simulación.

```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INTERRUPCIONES 10

typedef struct {
    int id;               
    char dispositivo[50];   
    char operacion[50];  
    bool atendida;        
} Interrupcion;

Interrupcion cola[MAX_INTERRUPCIONES];
int num_interrupciones = 0;
int siguiente_id = 1;

void generar_interrupcion() {
    if (num_interrupciones >= MAX_INTERRUPCIONES) {
        printf("Cola de interrupciones llena. No se pueden agregar mas interrupciones.\n");
        return;
    }

    Interrupcion nueva;
    nueva.id = siguiente_id++;
    printf("Introduce el nombre del dispositivo: ");
    scanf("%s", nueva.dispositivo);
    printf("Introduce la operacion realizada: ");
    scanf("%s", nueva.operacion);
    nueva.atendida = false;

    cola[num_interrupciones++] = nueva;
    printf("Interrupcion generada: ID %d, Dispositivo: %s, Operacion: %s\n",
           nueva.id, nueva.dispositivo, nueva.operacion);
}

void manejar_interrupcion() {
    if (num_interrupciones == 0) {
        printf("No hay interrupciones pendientes.\n");
        return;
    }

    Interrupcion *interrupcion = &cola[0]; 
    if (!interrupcion->atendida) {
        printf("Atendiendo interrupcion ID %d, Dispositivo: %s, Operacion: %s\n",
               interrupcion->id, interrupcion->dispositivo, interrupcion->operacion);
        interrupcion->atendida = true;
        printf("Interrupcion atendida.\n");
    }

    for (int i = 1; i < num_interrupciones; i++) {
        cola[i - 1] = cola[i];
    }
    num_interrupciones--;
}

void mostrar_interrupciones() {
    printf("\nEstado de las interrupciones:\n");
    if (num_interrupciones == 0) {
        printf("No hay interrupciones en la cola.\n");
        return;
    }

    for (int i = 0; i < num_interrupciones; i++) {
        printf("ID %d: Dispositivo: %s, Operacion: %s, Estado: %s\n",
               cola[i].id, cola[i].dispositivo, cola[i].operacion,
               cola[i].atendida ? "Atendida" : "Pendiente");
    }
}

int main() {
    int opcion;

    while (1) {
        printf("\nMenu del sistema de manejo de interrupciones:\n");
        printf("1. Generar interrupcion\n");
        printf("2. Manejar interrupcion\n");
        printf("3. Mostrar estado de interrupciones\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                generar_interrupcion();
                break;
            case 2:
                manejar_interrupcion();
                break;
            case 3:
                mostrar_interrupciones();
                break;
            case 4:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }
    return 0;
}

```

## Estructura de datos para manejos de dispositivos
Investiga y explica qué es una cola de E/S. Diseña una simulación de
una cola con prioridad.

Una cola de E/S (entrada/salida) es una estructura de datos utilizada por los sistemas operativos para organizar y gestionar las solicitudes de acceso a dispositivos de entrada y salida, como discos, impresoras, teclados, etc.

```C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COLA 10

typedef struct {
    int id;        
    int prioridad;  
} Elemento;

typedef struct {
    Elemento elementos[MAX_COLA];
    int tamanio;
} ColaPrioridad;

void inicializar_cola(ColaPrioridad *cola) {
    cola->tamanio = 0;
}

bool esta_vacia(ColaPrioridad *cola) {
    return cola->tamanio == 0;
}

bool esta_llena(ColaPrioridad *cola) {
    return cola->tamanio == MAX_COLA;
}

void agregar_elemento(ColaPrioridad *cola, int id, int prioridad) {
    if (esta_llena(cola)) {
        printf("La cola esta llena. No se puede agregar mas elementos.\n");
        return;
    }

    int i = cola->tamanio - 1;
    while (i >= 0 && cola->elementos[i].prioridad < prioridad) {
        cola->elementos[i + 1] = cola->elementos[i]; 
        i--;
    }

    cola->elementos[i + 1].id = id;
    cola->elementos[i + 1].prioridad = prioridad;
    cola->tamanio++;

    printf("Elemento ID %d con prioridad %d agregado.\n", id, prioridad);
}

void atender_elemento(ColaPrioridad *cola) {
    if (esta_vacia(cola)) {
        printf("La cola esta vacia. No hay elementos para atender.\n");
        return;
    }

    Elemento atendido = cola->elementos[0];
    printf("Atendiendo elemento ID %d con prioridad %d.\n", atendido.id, atendido.prioridad);

    for (int i = 1; i < cola->tamanio; i++) {
        cola->elementos[i - 1] = cola->elementos[i];
    }
    cola->tamanio--;
}

void mostrar_cola(ColaPrioridad *cola) {
    if (esta_vacia(cola)) {
        printf("La cola esta vacia.\n");
        return;
    }

    printf("Estado de la cola:\n");
    for (int i = 0; i < cola->tamanio; i++) {
        printf("ID: %d, Prioridad: %d\n", cola->elementos[i].id, cola->elementos[i].prioridad);
    }
}

int main() {
    ColaPrioridad cola;
    inicializar_cola(&cola);

    int opcion, id, prioridad;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Agregar elemento\n");
        printf("2. Atender elemento\n");
        printf("3. Mostrar cola\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el ID del elemento: ");
                scanf("%d", &id);
                printf("Introduce la prioridad del elemento: ");
                scanf("%d", &prioridad);
                agregar_elemento(&cola, id, prioridad);
                break;
            case 2:
                atender_elemento(&cola);
                break;
            case 3:
                mostrar_cola(&cola);
                break;
            case 4:
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }

    return 0;
}

```


Escribe un programa que simule las operaciones de un manejador de
dispositivos utilizando una tabla de estructuras.

```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DISPOSITIVOS 10
#define MAX_NOMBRE 20

typedef struct {
    int id;                    
    char nombre[MAX_NOMBRE];   
    bool en_uso;              
} Dispositivo;

Dispositivo tabla_dispositivos[MAX_DISPOSITIVOS];
int total_dispositivos = 0;

void agregar_dispositivo(int id, const char *nombre) {
    if (total_dispositivos >= MAX_DISPOSITIVOS) {
        printf("La tabla de dispositivos esta llena. No se pueden agregar mas dispositivos.\n");
        return;
    }
    tabla_dispositivos[total_dispositivos].id = id;
    strncpy(tabla_dispositivos[total_dispositivos].nombre, nombre, MAX_NOMBRE - 1);
    tabla_dispositivos[total_dispositivos].en_uso = false;
    total_dispositivos++;
    printf("Dispositivo '%s' agregado con ID %d.\n", nombre, id);
}

void mostrar_dispositivos() {
    printf("\nEstado actual de los dispositivos:\n");
    printf("ID\tNombre\t\tEstado\n");
    printf("----------------------------------\n");
    for (int i = 0; i < total_dispositivos; i++) {
        printf("%d\t%s\t\t%s\n", tabla_dispositivos[i].id, 
                                 tabla_dispositivos[i].nombre, 
                                 tabla_dispositivos[i].en_uso ? "En uso" : "Disponible");
    }
}

void asignar_dispositivo(int id) {
    for (int i = 0; i < total_dispositivos; i++) {
        if (tabla_dispositivos[i].id == id) {
            if (tabla_dispositivos[i].en_uso) {
                printf("El dispositivo '%s' ya esta en uso.\n", tabla_dispositivos[i].nombre);
            } else {
                tabla_dispositivos[i].en_uso = true;
                printf("El dispositivo '%s' ha sido asignado.\n", tabla_dispositivos[i].nombre);
            }
            return;
        }
    }
    printf("No se encontro un dispositivo con ID %d.\n", id);
}

void liberar_dispositivo(int id) {
    for (int i = 0; i < total_dispositivos; i++) {
        if (tabla_dispositivos[i].id == id) {
            if (tabla_dispositivos[i].en_uso) {
                tabla_dispositivos[i].en_uso = false;
                printf("El dispositivo '%s' ha sido liberado.\n", tabla_dispositivos[i].nombre);
            } else {
                printf("El dispositivo '%s' ya estaba disponible.\n", tabla_dispositivos[i].nombre);
            }
            return;
        }
    }
    printf("No se encontro un dispositivo con ID %d.\n", id);
}

int main() {
    int opcion, id;
    char nombre[MAX_NOMBRE];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Agregar dispositivo\n");
        printf("2. Mostrar dispositivos\n");
        printf("3. Asignar dispositivo\n");
        printf("4. Liberar dispositivo\n");
        printf("5. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el ID del dispositivo: ");
                scanf("%d", &id);
                printf("Introduce el nombre del dispositivo: ");
                scanf("%s", nombre);
                agregar_dispositivo(id, nombre);
                break;
            case 2:
                mostrar_dispositivos();
                break;
            case 3:
                printf("Introduce el ID del dispositivo a asignar: ");
                scanf("%d", &id);
                asignar_dispositivo(id);
                break;
            case 4:
                printf("Introduce el ID del dispositivo a liberar: ");
                scanf("%d", &id);
                liberar_dispositivo(id);
                break;
            case 5:
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }

    return 0;
}

```

## Operaciones de Entrada/Salida

Diseña un flujo que describa el proceso de lectura de un archivo desde
un disco magnético. Acompáñalo con un programa básico que simule
el proceso.

# Diagrama de flujo del proceso de lectura de un archivo desde un disco magnético

![Diagrama de flujo](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/DiagramaProcesoDeLectura.png)

```C

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ARCHIVOS 5
#define TAMANO_BLOQUE 512  

typedef struct {
    char nombre[50];
    int bloques_inicio;  
    int tamano;        
} Archivo;

Archivo disco_virtual[MAX_ARCHIVOS];
int num_archivos = 0;

void leer_disco(int bloque_inicio, int tamano) {
    printf("Leyendo %d bytes desde el bloque %d del disco...\n", tamano, bloque_inicio);
    printf("Simulacion: Los datos se han cargado en memoria.\n");
}

void registrar_archivo(const char *nombre, int bloques_inicio, int tamano) {
    if (num_archivos >= MAX_ARCHIVOS) {
        printf("El disco virtual esta lleno. No se pueden registrar mas archivos.\n");
        return;
    }
    strncpy(disco_virtual[num_archivos].nombre, nombre, sizeof(disco_virtual[num_archivos].nombre) - 1);
    disco_virtual[num_archivos].bloques_inicio = bloques_inicio;
    disco_virtual[num_archivos].tamano = tamano;
    num_archivos++;
    printf("Archivo '%s' registrado. Inicio en bloque %d, Tamano %d bytes.\n", nombre, bloques_inicio, tamano);
}


void leer_archivo(const char *nombre) {
    for (int i = 0; i < num_archivos; i++) {
        if (strcmp(disco_virtual[i].nombre, nombre) == 0) {
            printf("Archivo encontrado: '%s'. Localizando en disco...\n", nombre);
            leer_disco(disco_virtual[i].bloques_inicio, disco_virtual[i].tamano);
            return;
        }
    }
    printf("Archivo '%s' no encontrado en el disco.\n", nombre);
}

int main() {
    registrar_archivo("archivo1.txt", 10, 2048);
    registrar_archivo("archivo2.dat", 20, 1024);
    registrar_archivo("imagen.png", 30, 5120);

    printf("\nIntentando leer 'archivo1.txt':\n");
    leer_archivo("archivo1.txt");

    printf("\nIntentando leer 'imagen.png':\n");
    leer_archivo("imagen.png");

    printf("\nIntentando leer 'archivo_no_existente.txt':\n");
    leer_archivo("archivo_no_existente.txt");

    return 0;
}

```

Implementa un programa en Python, C o java que realice operaciones
de entrada/salida asíncronas usando archivos.

```C
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "archivo.txt"
#define BUF_SIZE 1024

void async_read(int fd) {
    char buffer[BUF_SIZE];
    ssize_t bytes_read = read(fd, buffer, BUF_SIZE - 1);
    
    if (bytes_read < 0) {
        perror("Error al leer archivo");
        return;
    }

    buffer[bytes_read] = '\0';
    printf("Datos leidos: %s\n", buffer);
}

void async_write(int fd) {
    char buffer[] = "Esto es una operacion de escritura asincrona en el archivo.\n";

    ssize_t bytes_written = write(fd, buffer, sizeof(buffer) - 1);
    
    if (bytes_written < 0) {
        perror("Error al escribir archivo");
        return;
    }

    printf("Datos escritos en el archivo.\n");
}

int main() {
    int fd = open(FILENAME, O_RDWR | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("Error al abrir archivo");
        return 1;
    }

    printf("Iniciando lectura asincrona...\n");
    async_read(fd);

    printf("Esperando que la lectura termine...\n");
    sleep(1);

    printf("Iniciando escritura asincrona...\n");
    async_write(fd);

    printf("Esperando que la escritura termine...\n");
    sleep(1);

    close(fd);

    return 0;
}

```
# Integración

Escribe un programa que implemente el algoritmo de planificación de
discos "Elevator (SCAN)".

``` C

#include <stdio.h>
#include <stdlib.h>

#define MAX_CILINDROS 100

void elevator_scan(int solicitudes[], int num_solicitudes, int cabeza, int direccion) {
    int i, j;
    int mov = 0;
    int izquierda[MAX_CILINDROS], derecha[MAX_CILINDROS];
    int num_izquierda = 0, num_derecha = 0;

    for (i = 0; i < num_solicitudes; i++) {
        if (solicitudes[i] < cabeza) {
            izquierda[num_izquierda++] = solicitudes[i];
        } else {
            derecha[num_derecha++] = solicitudes[i];
        }
    }

    for (i = 0; i < num_izquierda - 1; i++) {
        for (j = i + 1; j < num_izquierda; j++) {
            if (izquierda[i] < izquierda[j]) {
                int temp = izquierda[i];
                izquierda[i] = izquierda[j];
                izquierda[j] = temp;
            }
        }
    }

    for (i = 0; i < num_derecha - 1; i++) {
        for (j = i + 1; j < num_derecha; j++) {
            if (derecha[i] > derecha[j]) {
                int temp = derecha[i];
                derecha[i] = derecha[j];
                derecha[j] = temp;
            }
        }
    }

    if (direccion == 1) {
        for (i = 0; i < num_derecha; i++) {
            mov += abs(cabeza - derecha[i]);
            cabeza = derecha[i];
        }

        cabeza = derecha[num_derecha - 1];
        for (i = num_izquierda - 1; i >= 0; i--) {
            mov += abs(cabeza - izquierda[i]);
            cabeza = izquierda[i];
        }
    } else {
        for (i = num_izquierda - 1; i >= 0; i--) {
            mov += abs(cabeza - izquierda[i]);
            cabeza = izquierda[i];
        }

        cabeza = izquierda[0];
        for (i = 0; i < num_derecha; i++) {
            mov += abs(cabeza - derecha[i]);
            cabeza = derecha[i];
        }
    }

    printf("Movimientos totales: %d\n", mov);
}

int main() {
    int solicitudes[MAX_CILINDROS];
    int num_solicitudes;
    int cabeza, direccion;

    printf("Ingrese el numero de solicitudes: ");
    scanf("%d", &num_solicitudes);

    printf("Ingrese las solicitudes de acceso al disco:\n");
    for (int i = 0; i < num_solicitudes; i++) {
        printf("Solicitud %d: ", i + 1);
        scanf("%d", &solicitudes[i]);
    }

    printf("Ingrese la posicion inicial de la cabeza del disco: ");
    scanf("%d", &cabeza);

    printf("Ingrese la direccion (1 para derecha, 0 para izquierda): ");
    scanf("%d", &direccion);

    elevator_scan(solicitudes, num_solicitudes, cabeza, direccion);

    return 0;
}

```
Diseña un sistema que maneje múltiples dispositivos simulados (disco
duro, impresora, teclado) y muestra cómo se realiza la comunicación
entre ellos.

```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOLICITUDES 5

typedef struct {
    int id;
    char solicitud[100];
    int estado; 
} Dispositivo;


typedef struct {
    Dispositivo disco;
    Dispositivo impresora;
    Dispositivo teclado;
} ManejadorDispositivos;


void inicializarDispositivos(ManejadorDispositivos *manejador) {
    manejador->disco.id = 1;
    strcpy(manejador->disco.solicitud, "");
    manejador->disco.estado = 0;

    manejador->impresora.id = 2;
    strcpy(manejador->impresora.solicitud, "");
    manejador->impresora.estado = 0;

    manejador->teclado.id = 3;
    strcpy(manejador->teclado.solicitud, "");
    manejador->teclado.estado = 0;
}


void mostrarEstado(ManejadorDispositivos *manejador) {
    printf("Estado de los dispositivos:\n");
    printf("Disco: %s\n", manejador->disco.estado == 0 ? "No solicitado" : (manejador->disco.estado == 1 ? "En proceso" : "Completado"));
    printf("Impresora: %s\n", manejador->impresora.estado == 0 ? "No solicitado" : (manejador->impresora.estado == 1 ? "En proceso" : "Completado"));
    printf("Teclado: %s\n", manejador->teclado.estado == 0 ? "No solicitado" : (manejador->teclado.estado == 1 ? "En proceso" : "Completado"));
}


void solicitarOperacion(ManejadorDispositivos *manejador, int dispositivo, const char *solicitud) {
    switch (dispositivo) {
        case 1:
            strcpy(manejador->disco.solicitud, solicitud);
            manejador->disco.estado = 1;
            printf("Solicitud en el Disco: %s\n", solicitud);
            break;
        case 2:
            strcpy(manejador->impresora.solicitud, solicitud);
            manejador->impresora.estado = 1;
            printf("Solicitud en la Impresora: %s\n", solicitud);
            break;
        case 3:
            strcpy(manejador->teclado.solicitud, solicitud);
            manejador->teclado.estado = 1;
            printf("Solicitud en el Teclado: %s\n", solicitud);
            break;
        default:
            printf("Dispositivo no valido.\n");
            break;
    }
}


void procesarSolicitudes(ManejadorDispositivos *manejador) {
    if (manejador->disco.estado == 1) {
        printf("Procesando solicitud en el Disco: %s\n", manejador->disco.solicitud);
        manejador->disco.estado = 2;
    }
    if (manejador->impresora.estado == 1) {
        printf("Procesando solicitud en la Impresora: %s\n", manejador->impresora.solicitud);
        manejador->impresora.estado = 2;
    }
    if (manejador->teclado.estado == 1) {
        printf("Procesando solicitud en el Teclado: %s\n", manejador->teclado.solicitud);
        manejador->teclado.estado = 2;
    }
}


void comunicacionEntreDispositivos(ManejadorDispositivos *manejador) {
    printf("Comunicacion entre dispositivos:\n");
    if (manejador->disco.estado == 2 && manejador->impresora.estado == 2) {
        printf("El Disco ha completado su tarea. Comunicando con la Impresora...\n");
        printf("La Impresora esta lista para imprimir.\n");
    }
    if (manejador->impresora.estado == 2 && manejador->teclado.estado == 2) {
        printf("La Impresora ha completado la impresion. Comunicando con el Teclado...\n");
        printf("El Teclado esta listo para recibir entrada.\n");
    }
}

int main() {
    ManejadorDispositivos manejador;
    int dispositivo;
    char solicitud[100];

    inicializarDispositivos(&manejador);

    while (1) {
        printf("\nSeleccione una operacion:\n");
        printf("1. Solicitar operacion en el Disco\n");
        printf("2. Solicitar operacion en la Impresora\n");
        printf("3. Solicitar operacion en el Teclado\n");
        printf("4. Mostrar estado de los dispositivos\n");
        printf("5. Procesar solicitudes\n");
        printf("6. Simular comunicacion entre dispositivos\n");
        printf("7. Salir\n");
        printf("Opcion: ");
        scanf("%d", &dispositivo);
        getchar(); 

        if (dispositivo == 7) {
            break;
        }

        if (dispositivo >= 1 && dispositivo <= 3) {
            printf("Ingrese la solicitud: ");
            fgets(solicitud, sizeof(solicitud), stdin);
            solicitud[strcspn(solicitud, "\n")] = 0;  
            solicitarOperacion(&manejador, dispositivo, solicitud);
        } else if (dispositivo == 4) {
            mostrarEstado(&manejador);
        } else if (dispositivo == 5) {
            procesarSolicitudes(&manejador);
        } else if (dispositivo == 6) {
            comunicacionEntreDispositivos(&manejador);
        } else {
            printf("Opcion no valida.\n");
        }
    }

    return 0;
}

```

# Avanzados

Explica cómo los sistemas operativos modernos optimizan las operaciones
de entrada/salida con el uso de memoria caché.

Los sistemas operativos modernos optimizan las operaciones de entrada/salida (E/S) mediante el uso de memoria caché para reducir el tiempo de acceso a los datos y mejorar el rendimiento general del sistema

La memoria caché es un área de memoria rápida (normalmente en RAM) utilizada para almacenar temporalmente los datos que se han leído o que se escribirán en dispositivos más lentos, como discos duros o SSDs. 

Beneficios del uso de caché en E/S:
* Reducción de la latencia: La caché, al ser más rápida que los dispositivos de almacenamiento, permite acceder a los datos con mayor velocidad.

* Disminución de accesos físicos: Al reducir la frecuencia de lecturas y escrituras en el disco, se extiende su vida útil y se mejora el rendimiento.

* Optimización de recursos del sistema: Al agrupar operaciones, el sistema reduce la sobrecarga en la gestión de dispositivos.

* Mejora en el rendimiento de aplicaciones: Procesos como la ejecución de aplicaciones o lectura/escritura de archivos se ven significativamente acelerados.


## Referencias APA:

a:, E. E. U. (s/f). Gestión de los recursos de un sistema operativo. Mheducation.es. Recuperado el 1 de diciembre de 2024, de https://www.mheducation.es/bcv/guide/capitulo/8448180321.pdf

# Actividades: Dispositivos de entrada y salida en Linux

# Reporte de Actividades: Manejo de Dispositivos en Linux

## Actividad 1: Listar dispositivos conectados

### Objetivo
Conocer los dispositivos de entrada y salida conectados al sistema.

### Observaciones

#### 1. Comando `lsblk`
- **Salida:** Enumera los dispositivos de bloque como discos duros, particiones y unidades extraíbles.
- **Tipos de dispositivos mostrados:** Discos duros, particiones, unidades USB montadas.

#### 2. Comando `lsusb`
- **Salida:** Lista los dispositivos conectados a los puertos USB como ratones, teclados, cámaras y discos externos.

#### 3. Comando `lspci`
- **Salida:** Muestra dispositivos conectados al bus PCI, como tarjetas de red, tarjetas gráficas y controladores.

#### 4. Comando `dmesg | grep usb`
- **Salida:** Muestra mensajes del kernel relacionados con dispositivos USB, como la detección de dispositivos o errores.

### Respuestas

1. **¿Qué tipos de dispositivos se muestran en la salida de `lsblk`?**
   - Discos duros, particiones, dispositivos de almacenamiento extraíble.

2. **¿Cuál es la diferencia entre `lsusb` y `lspci`?**
   - `lsusb` muestra dispositivos conectados al bus USB, mientras que `lspci` lista dispositivos conectados al bus PCI.

3. **¿Qué información adicional proporciona `dmesg | grep usb`?**
   - Detalles del kernel sobre el estado, errores y eventos relacionados con dispositivos USB.

---

## Actividad 2: Verificar dispositivos de almacenamiento

### Observaciones

#### 1. Comando `fdisk -l`
- **Salida:** Lista todos los discos, particiones y sus tamaños.

#### 2. Comando `blkid`
- **Salida:** Muestra UUID, etiquetas y tipos de sistemas de archivos de cada partición.

#### 3. Comando `df -h`
- **Salida:** Lista dispositivos montados, su espacio usado, disponible y punto de montaje.

### Respuestas

1. **¿Qué dispositivos de almacenamiento están conectados a su sistema?**
   - Discos principales (sda) y dispositivos USB si están conectados.

2. **¿Qué particiones están montadas actualmente?**
   - Las particiones del sistema raíz `/` y `/boot/efi` están montadas.

3. **¿Qué tipo de sistemas de archivos se usan en las particiones?**
   - `ext4` para particiones Linux y `vfat` para particiones de arranque UEFI.

---

## Actividad 3: Explorar dispositivos de entrada

### Observaciones

#### 1. Comando `cat /proc/bus/input/devices`
- **Salida:** Lista dispositivos de entrada como teclados, ratones y controladores adicionales.

#### 2. Comando `evtest`
- **Salida:** Muestra eventos generados por los dispositivos cuando se interactúa con ellos.

### Respuestas

1. **¿Qué eventos genera cada dispositivo al interactuar con ellos?**
   - Teclado: Eventos de pulsación y liberación de teclas.
   - Mouse: Movimientos, clics y desplazamientos.
   - Controladores USB: Conexión y desconexión.

2. **¿Cómo se identifican los dispositivos en `/proc/bus/input/devices`?**
   - Por nombre, tipo y controlador asociado.

---

## Actividad 4: Examinar dispositivos de salida

### Observaciones

#### 1. Comando `xrandr`
- **Salida:** Lista las pantallas conectadas, resoluciones disponibles y configuraciones actuales.

#### 2. Comando `aplay -l`
- **Salida:** Lista tarjetas de sonido disponibles y dispositivos asociados.

#### 3. Comando `lsof /dev/snd/*`
- **Salida:** Muestra procesos que están utilizando la tarjeta de sonido.

### Respuestas

1. **¿Qué salidas de video están disponibles en su sistema?**
   - Pantalla primaria y cualquier monitor secundario conectado.

2. **¿Qué dispositivos de sonido se detectaron?**
   - Tarjetas de sonido integradas y dispositivos de audio USB si están conectados.

3. **¿Qué procesos están usando la tarjeta de sonido?**
   - Reproductores multimedia y sistemas de notificación.

---

## Actividad 5: Crear un script de resumen

### Observaciones
#### Script `dispositivos.sh`

```bash
echo "Dispositivos de bloque:"
lsblk
echo "Dispositivos USB:"
lsusb
echo "Dispositivos PCI:"
lspci
echo "Dispositivos de entrada:"
cat /proc/bus/input/devices
echo "Salidas de video:"
xrandr
echo "Tarjetas de sonido:"
aplay -l
```
### Respuestas
¿Qué ventajas tiene usar un script para recopilar esta información?

Automatización, facilidad de uso y consistencia en la recopilación de datos.
¿Qué cambios realizaría para personalizar el script?

Incluir marcas de tiempo, separar la salida por tipo de dispositivo en archivos individuales.

---

## Actividad 6: Reflexión y discusión
### Respuestas
¿Qué comando encontró más útil y por qué?

lsblk, porque proporciona una vista clara de los dispositivos de almacenamiento y sus particiones.
¿Qué tan importante es conocer los dispositivos conectados al sistema?

Es crucial para diagnosticar problemas, configurar nuevos dispositivos y optimizar el sistema.
¿Cómo podrían estos conocimientos aplicarse en la administración de sistemas?

Permite una gestión eficiente de hardware, diagnóstico de errores y planificación de actualizaciones.


# Comandos de Entrada y Salida, Discos y Archivos

## Ejercicio 1: Montar y Desmontar Discos

Este ejercicio tuvo como objetivo aprender a montar y desmontar dispositivos USB en una máquina virtual que ejecuta Linux Mint como sistema operativo invitado, utilizando VirtualBox como entorno de virtualización. Además, se incluyó el procedimiento para crear un filtro de USB en VirtualBox para que el dispositivo externo fuera reconocido dentro de la máquina virtual. A continuación, se detalla lo realizado:

1. Preparar el dispositivo USB y el entorno virtual
Conectar la USB al equipo anfitrión: Se insertó la memoria USB en el puerto correspondiente del equipo anfitrión.

Configurar un filtro de USB en VirtualBox:
* En el menú de VirtualBox, se seleccionó la máquina virtual de Linux Mint y se accedió a Configuración > USB.

* Se activó el controlador de USB 2.0 o 3.0 (dependiendo del soporte del equipo).

* Se añadió un filtro de dispositivo USB utilizando el botón con el ícono de "Agregar un nuevo filtro".

* Se seleccionó el dispositivo correspondiente (la memoria USB) para asegurarse de que VirtualBox redirigiera automáticamente el dispositivo a la máquina virtual al conectarlo.

2. Montar la memoria USB en Linux Mint
Identificar el dispositivo USB:

* Se utilizó el comando sudo fdisk -l para listar los discos disponibles y localizar la memoria USB. El dispositivo apareció identificado como /dev/sdb1 con un sistema de archivos FAT16.

* Alternativamente, el comando lsblk ayudó a visualizar los puntos de montaje y particiones disponibles.

Los comandos utilizados tanto para montar como desmontar el USB fueron los siguientes:

![Comandos para montar y desmontar una USB](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/MontarYDesmontarUSBLinux.jpeg)

### Conclusión

Este ejercicio permitió comprender el flujo completo para trabajar con dispositivos USB en una máquina virtual, incluyendo:

Configurar un filtro de USB en VirtualBox para que el dispositivo sea reconocido.
Identificar y montar dispositivos de almacenamiento en Linux.
Transferir archivos a un dispositivo montado.
Desmontar dispositivos para su retiro seguro.
Con estos pasos, se logró una integración eficiente del hardware externo con la máquina virtual.

## Ejercicio 2: Redirección de Entrada y Salida

El objetivo de este ejercicio fue aprender a utilizar la redirección de entrada y salida en Linux para gestionar información en archivos.

Listar archivos y guardar en un archivo:
Se usó el comando ls -l > listado.txt para listar los archivos del directorio actual y guardar el resultado en el archivo listado.txt.

Mostrar el contenido del archivo:
Con cat listado.txt se mostró el contenido del archivo en la terminal.

Añadir la fecha actual:
Se agregó la fecha y hora actuales al final del archivo usando date >> listado.txt.

Verificar el contenido actualizado:
Nuevamente, se usó cat listado.txt para mostrar todo el contenido del archivo, ahora incluyendo la fecha.

Este ejercicio permitió practicar la redirección de salida (> y >>) para gestionar datos de comandos en archivos como se muestra a continuación:

![Redirección de entrada y salida](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/Redirecci%C3%B3nDeEntradaYSalida.jpeg)

## Ejercicio 3: Copiar y Mover Archivos

El objetivo de este ejercicio fue practicar la copia, el renombrado y el movimiento de archivos en Linux.

Crear un archivo de texto:
Se creó un archivo llamado archivo1.txt con el contenido "Este es un archivo de prueba" usando el comando echo.

Copiar el archivo:
El archivo archivo1.txt se copió al directorio /tmp con cp.

Renombrar el archivo:
El archivo copiado en /tmp fue renombrado a archivo2.txt usando mv.

Mover el archivo de vuelta:
Finalmente, se movió archivo2.txt de /tmp al directorio actual con mv.

Este ejercicio permitió familiarizarse con los comandos básicos de manipulación de archivos en Linux como se muestra en la siguiente imagen:

![Copiar y mover archivos](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/CopiarYMoverArchivos.jpeg)


## Ejercicio 4: Comprimir y Descomprimir Archivos con tar
Objetivo: Aprender a empaquetar y descomprimir archivos utilizando la herramienta tar.

Crear un directorio y copiar archivos:
Se creó un directorio llamado backup. Luego, se copiaron los archivos archivo1.txt y archivo2.txt al directorio backup.

Empaquetar y comprimir el directorio:
Se creó un archivo comprimido llamado backup.tar.gz, el cual contiene todo el contenido del directorio backup.

Descomprimir el archivo:
Al intentar extraer el archivo comprimido, hubo un error debido a un nombre incorrecto al escribir backup.tar.gz. con un punto extra al final. Corrigiendo el comando, se descomprime correctamente para restaurar los archivos originales en su estructura original.

Resultado esperado: Los archivos del directorio backup se descomprimen en la ubicación actual, manteniendo la estructura y contenido original como se muestra a continuación:

![Comprimir y descomprimir archivos](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/ComprimirYDescomprimir.jpeg)

## Ejercicio 5: Permisos y Propiedades de Archivos

Objetivo: Aprender a modificar los permisos y propietarios de archivos en un sistema Linux.

Crear un archivo:
Se creó un archivo vacío llamado privado.txt utilizando el comando touch.

Modificar permisos del archivo:
Los permisos del archivo se configuraron para que solo el propietario pueda leer y escribir en él, utilizando el comando chmod 600. Esto establece los permisos como rw-------, restringiendo el acceso para otros usuarios.

Cambiar el propietario del archivo:
Se intentó cambiar el propietario del archivo a otro usuario utilizando el comando sudo chown. Este paso requiere privilegios de superusuario y que el usuario de destino exista en el sistema.

Resultado esperado:
El archivo privado.txt queda protegido con permisos limitados al propietario, y el propietario puede ser modificado si es necesario y si el usuario tiene los permisos adecuados.

## Ejercicio 6: Exploración de Dispositivos
Objetivo: Identificar discos y particiones en el sistema, así como explorar el uso del espacio en disco y directorios específicos.

Listar discos y particiones:
Se utilizó el comando lsblk para obtener una visión general de los dispositivos de almacenamiento y sus puntos de montaje. Esto permitió identificar la estructura del disco principal, que incluye particiones como /boot/efi y la raíz /.

Verificar el uso de disco:
Se empleó el comando df -h para mostrar el espacio total, utilizado y disponible en cada partición, presentado en un formato legible para humanos.

Analizar el tamaño de directorios específicos:
Usando el comando du -sh, se calculó el espacio utilizado por el directorio /home, mostrando el tamaño total en un formato comprensible. Este comando permite identificar directorios que consumen grandes cantidades de espacio.

Resultado esperado:
Al finalizar este ejercicio, se obtiene una visión clara del estado de los discos y particiones en el sistema, así como del uso del espacio en directorios importantes. Esto es útil para la administración y mantenimiento del sistema. Los comandos utilizados se muestran en la imagen:

![Exploración de dispositivos imagen](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/Exploraci%C3%B3nDeDispositivos.png)


## Ejercicio 7: Crear y Formatear Particiones
Objetivo: Aprender a crear, formatear y montar particiones en un sistema Linux utilizando herramientas como fdisk y mkfs.

Identificar discos disponibles:
Se utilizó el comando sudo fdisk -l para listar todos los discos y particiones presentes en el sistema, identificando un disco no particionado que se puede usar para la práctica.

Crear una nueva partición:
Con el comando sudo fdisk /dev/sdX, se accedió al menú de configuración del disco seleccionado. Se siguieron las instrucciones para crear una nueva partición, como elegir el tipo de partición y asignar el espacio.

Formatear la partición:
Una vez creada la partición, se formateó con el sistema de archivos ext4 usando el comando sudo mkfs.ext4 /dev/sdX1. Esto prepara la partición para almacenar datos.

Montar la partición y probar su funcionalidad:
La partición recién creada se montó en el directorio /mnt/nueva_particion utilizando sudo mount. Para verificar que la partición está operativa, se creó un archivo de prueba llamado test.txt con contenido escrito dentro de la partición.

Resultado esperado:
Al completar este ejercicio, se tiene una partición funcional, formateada y montada correctamente, lista para ser utilizada en el sistema. Este proceso es fundamental para la administración de almacenamiento en Linux, especialmente al trabajar con nuevos discos o en entornos virtuales.

# Sistema de archivos
## Ejercicio 1: Concepto y noción de archivo virtual y real
* Archivo virtual:

Es un archivo de uso temporal que es utilizado por los procesos del sistema mientras se están ejecutando dichos procesos.


Estos archivos se crean durante la ejecución de un sistema y los utiliza para el almacenamiento de información, intercambio y organización mientras se ejecuta el sistema, su tamaño es muy variable y terminan al detener la ejecución del sistema, muchos de ellos son borrados, por ejemplo, los archivos *.tmp.

* Archivo temporal:

Es un objeto que contiene programas, datos o cualquier otro elemento. 

Un archivo se muestra de manera real, en la información del espacio que ocupa en un disco duro o sistema de almacenamiento, en otras palabras, su tamaño es en bytes.

### Referencias APA
SISTEMAS OPERATIVOS. (s/f). Blogspot.com. Recuperado el 16 de diciembre de 2024, de https://so-sistemas-operativoss.blogspot.com/2017/12/52-nocion-de-archivo-real-y-virtual.html

Ejemplos de manejo de archivos reales por el sistema operativo:

* Creación y modificación: Al crear un archivo con touch o guardar un documento en un editor de texto, el sistema operativo organiza sus datos en sectores del disco.

* Almacenamiento en diferentes sistemas de archivos: NTFS (Windows), ext4 (Linux), HFS+ (Mac).

* Operaciones básicas: Copiar, mover, renombrar y eliminar archivos con herramientas como cp, mv, rm o mediante interfaces gráficas.

Ejemplos de manejo de archivos virtuales por el sistema operativo:

* Archivos en /proc: En Linux, el directorio /proc contiene archivos virtuales que representan información sobre procesos y el sistema, como /proc/cpuinfo o /proc/meminfo.

* Archivos especiales en /dev: Dispositivos como discos, terminales y puertos son representados como archivos virtuales.

* Tuberías (Pipes): Son archivos temporales usados para transferir datos entre procesos en tiempo real.

Explica un caso práctico donde un archivo virtual sea más útil que un
archivo real.

Supongamos que un administrador de sistemas necesita información detallada sobre el rendimiento del sistema, como el uso de la CPU o la memoria RAM.

Por qué un archivo virtual es útil:
Acceso dinámico: El archivo virtual /proc/cpuinfo proporciona información actualizada al instante sobre el procesador. No hay necesidad de almacenar datos en disco, ya que se generan en memoria.
Eficiencia: Leer archivos virtuales evita el uso de espacio en disco y reduce el tiempo necesario para acceder a datos dinámicos.
Facilidad de análisis: Puede accederse a estos archivos con comandos simples como cat o grep, o ser procesados por herramientas de monitorización.

## Ejercicio 2: Componentes de un sistema de archivos
1. Metadatos:
Definición: Información sobre los archivos y directorios, como su nombre, tamaño, propietario y permisos.
Ejemplos:
Fecha de creación, modificación y último acceso.
Tipo de archivo (texto, binario, enlace simbólico, etc.).
Propósito: Facilita la organización y gestión de archivos al proporcionar detalles esenciales sin acceder al contenido.

2. Tablas de Asignación de Archivos (FAT, inodos, etc.):
Definición: Estructuras que mantienen un seguimiento de qué bloques de datos en el almacenamiento pertenecen a qué archivos.
Tipos comunes:
FAT (File Allocation Table): Utilizado en sistemas FAT32 y exFAT.
Inodos: Usados en sistemas de archivos como ext4.
Master File Table (MFT): Usado por NTFS.
Propósito: Mapea los archivos y directorios a las ubicaciones físicas de sus datos en el disco.

3. Superbloque:
Definición: Estructura de datos que almacena información sobre el sistema de archivos en su conjunto.
Contenido:
Tamaño total del sistema de archivos.
Cantidad de bloques libres y utilizados.
Ubicación de las tablas de asignación.
Propósito: Ayuda al sistema operativo a entender cómo interactuar con el sistema de archivos.

4. Directorios:
Definición: Estructuras jerárquicas que organizan los archivos en carpetas.
Contenido: Enlaces a archivos y subdirectorios, junto con sus identificadores (como inodos).
Propósito: Facilita la navegación y agrupación lógica de archivos.

5. Bloques de Datos:
Definición: Fragmentos del disco donde se almacenan los datos reales de los archivos.
Características:
Los tamaños pueden variar según el sistema de archivos.
Los archivos grandes suelen ocupar múltiples bloques.
Propósito: Contienen el contenido binario o textual de los archivos.

6. Journaling (Registro):
Definición: Registro de transacciones realizado antes de efectuar cambios en el sistema de archivos.
Ejemplo: Ext3, ext4 y NTFS.
Propósito:
Minimiza la pérdida de datos en caso de fallos del sistema.
Facilita la recuperación después de un apagado inesperado.

7. Espacio Libre:
Definición: Áreas no asignadas del disco.
Gestión:
Sistemas como FAT mantienen una lista de bloques libres.
Otros sistemas, como ext4, usan mapas de bits o listas enlazadas.
Propósito: Permite al sistema operativo asignar espacio para nuevos archivos y expansión de los existentes.

8. Puntos de Montaje:
Definición: Lugares en el sistema de archivos donde se adjuntan particiones o discos externos.
Ejemplo: En Linux, un disco adicional podría montarse en /mnt/disco.
Propósito: Proporciona acceso lógico y unificado a múltiples dispositivos de almacenamiento.

9. Estructuras de Indexación:
Definición: Mecanismos para acelerar la búsqueda y recuperación de archivos.
Ejemplo:
Árboles B+ en NTFS.
Tabla hash en ext4.
Propósito: Mejora el rendimiento al acceder a archivos en sistemas grandes.

10. Caché del Sistema de Archivos:
Definición: Copias temporales de datos y metadatos almacenados en memoria para reducir la necesidad de acceso directo al disco.
Propósito: Aumenta la velocidad de las operaciones de lectura y escritura.

![Cuadro comparativo de como funcionan los componentes en EXT4 y NTFS](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/CuadroComparativo.png)

### EXT4
Ventajas:

* Eficiencia y rendimiento: EXT4 es rápido en operaciones básicas como lectura y escritura, gracias a su sistema de bloques y la técnica de extents, que reduce la fragmentación al almacenar archivos grandes.

* Compatibilidad en Linux: Es el sistema de archivos predeterminado en distribuciones de Linux, con amplia integración y soporte nativo.

* Journaling: Su sistema de registro garantiza la integridad de datos tras fallos de energía o errores del sistema.

* Escalabilidad: Soporta volúmenes y archivos de gran tamaño (hasta 1 exabyte para volúmenes y 16 terabytes por archivo), lo que lo hace ideal para discos modernos.

* Gestión de espacio libre: Utiliza mapas de bits que agilizan la asignación de bloques, mejorando el rendimiento general.

Desventajas:

* Interoperabilidad limitada: Aunque existen herramientas para usar EXT4 en Windows, su soporte fuera de Linux es limitado y menos eficiente.

* Funcionalidades avanzadas: Carece de características nativas como la encriptación y la compresión, que están disponibles en NTFS.

* Journaling básico: Aunque es efectivo, no es tan robusto como el USN Journal de NTFS, lo que puede limitar la recuperación en casos extremos.

### NTFS

Ventajas:

* Robustez y características avanzadas: NTFS incluye soporte nativo para encriptación (EFS) y compresión de archivos, lo que mejora la seguridad y optimiza el uso del espacio.

* Journaling avanzado: Su USN Journal ofrece un registro detallado de cambios en archivos, mejorando la recuperación tras errores o interrupciones.

* Compatibilidad con grandes volúmenes: Diseñado para manejar discos de alta capacidad, NTFS es ideal para servidores y sistemas de almacenamiento masivo.

* Interoperabilidad: Es el sistema de archivos predeterminado en Windows y puede ser usado en Linux y macOS con herramientas adecuadas, aunque con limitaciones en características avanzadas.

Desventajas:

* Complejidad: La gestión de sus estructuras, como la Master File Table (MFT), puede generar una mayor sobrecarga en sistemas con recursos limitados.

* Fragmentación: Aunque NTFS maneja bien la fragmentación, puede volverse un problema con el tiempo, requiriendo herramientas de desfragmentación.

* Rendimiento en Linux: Aunque compatible, su uso en sistemas Linux puede ser menos eficiente y más propenso a errores en comparación con EXT4.

* Espacio en disco: Sus estructuras de journaling y metadatos ocupan más espacio, lo que puede ser una desventaja en discos pequeños.

## Ejercicio 3: Organización lógica y física de archivos

![árbol jerárquico de directorios y subdirectorios](https://github.com/emiromero0790/Sistemas-Operativos-C-Java/blob/master/%C3%81rboljer%C3%A1rquicoDiretorios.png)

### Pasos de la traducción de Dirección Lógica a Dirección Física en el Disco
1. Sistema de Archivos y Metadatos:
Cuando se solicita acceder a un archivo, el sistema de archivos (por ejemplo, EXT4 o NTFS) consulta las estructuras de metadatos como la Master File Table (MFT) en NTFS o los inodos en EXT4 para localizar los bloques o clusters donde están almacenados los datos.

2. Asignación de Bloques o Clusters:
Los archivos se dividen en fragmentos llamados bloques (en EXT4) o clusters (en NTFS). Los metadatos contienen referencias a estos bloques en el disco lógico.

3. Controlador del Disco:
El sistema operativo envía la dirección lógica a través del controlador del disco, que traduce esa dirección a un sector físico del disco usando tablas como la Tabla de Asignación de Archivos (FAT) o estructuras específicas del sistema de archivos.

4. Acceso Físico:
Finalmente, el controlador del disco convierte la dirección en coordenadas físicas (cilindro, cabezal y sector en discos mecánicos o celdas en SSD) y recupera o almacena los datos solicitados.

### Ejemplo Práctico: Almacenamiento de un Archivo
Escenario: Se almacena un archivo llamado documento.txt de 5 KB en un disco con EXT4, donde el tamaño de bloque es de 4 KB.

Creación del Archivo:
El sistema de archivos asigna un inodo al archivo, que contiene información como el nombre, tamaño, permisos, y una referencia a los bloques donde se almacenará el contenido.

División en Bloques:
El archivo de 5 KB se divide en dos partes:

Los primeros 4 KB se almacenan en el primer bloque asignado.
El 1 KB restante ocupa un segundo bloque.
Almacenamiento Físico:
Los bloques asignados se localizan físicamente en el disco. Por ejemplo:

Bloque 1: Sector físico 1024

Bloque 2: Sector físico 2048

Referencia en los Metadatos:
El inodo del archivo documento.txt guarda las direcciones lógicas de los bloques (Bloque 1 y Bloque 2). Cuando se necesita acceder al archivo, el sistema usa estas direcciones para ubicar los datos.

## Ejercicio 4: Mecanismos de acceso a los archivos

### Acceso Secuencial
En este mecanismo, los datos se leen o escriben en un orden lineal, desde el principio hasta el final, como si fuera una cinta.

Características:

Los datos deben accederse en el orden en que están almacenados.
Es ideal para operaciones continuas o flujos de datos, como la reproducción de video o el análisis de registros.
Ventajas:

Simple y eficiente para grandes volúmenes de datos que se procesan de manera lineal.
Menos sobrecarga en términos de gestión de almacenamiento.
Desventajas:

Poco eficiente si se necesita acceder a datos aleatorios o específicos.
Ejemplo práctico: Leer un archivo de registro (log.txt) desde el principio hasta el final para analizar eventos.

### Acceso Directo (Aleatorio)
Permite acceder directamente a cualquier ubicación en el almacenamiento sin necesidad de seguir un orden específico.

Características:

Cada dato tiene una dirección única que se puede usar para acceder directamente.
Común en discos duros (HDD), discos sólidos (SSD) y sistemas de bases de datos.
Ventajas:

Muy eficiente para acceder rápidamente a datos específicos.
Ideal para aplicaciones como bases de datos o sistemas operativos.
Desventajas:

Mayor complejidad en la gestión de direcciones de memoria.
Puede ser menos eficiente para grandes volúmenes de datos si el patrón de acceso no está optimizado.
Ejemplo práctico: Leer un registro específico en una base de datos utilizando su clave primaria.

### Acceso Indexado
Utiliza un índice para localizar rápidamente los datos almacenados. El índice actúa como una tabla que contiene referencias a las ubicaciones de los datos.

Características:

Se utiliza un índice intermedio para facilitar el acceso.
Común en sistemas de archivos modernos y bases de datos.
Ventajas:

Rápido acceso a grandes volúmenes de datos bien organizados.
Optimizado para sistemas que requieren búsquedas frecuentes.
Desventajas:

La creación y mantenimiento del índice puede requerir espacio adicional y recursos computacionales.
Si el índice se daña, puede dificultar el acceso a los datos.
Ejemplo práctico: Un sistema de archivos como NTFS utiliza índices para localizar archivos rápidamente.

### Acceso por Mapeo de Memoria
Los datos se asignan directamente a la memoria del sistema, lo que permite que las aplicaciones los accedan como si fueran parte de la memoria principal.

Características:

La lectura y escritura se realizan directamente en la memoria.
Utilizado para mejorar el rendimiento en sistemas modernos.
Ventajas:

Extremadamente rápido, ya que elimina la necesidad de operaciones de E/S adicionales.
Ideal para trabajar con archivos grandes que se procesan en segmentos.
Desventajas:

Puede consumir mucha memoria si los datos no están bien gestionados.
No es ideal para dispositivos con recursos limitados.
Ejemplo práctico: Un sistema operativo mapea un archivo de intercambio (swap) en la memoria virtual.

### Acceso en Red
Permite acceder a los datos almacenados en ubicaciones remotas mediante protocolos como NFS, SMB o FTP.

Características:

Se accede a los datos a través de una red en lugar de un dispositivo local.
Común en servidores de almacenamiento y sistemas distribuidos.
Ventajas:

Facilita la colaboración y el acceso remoto.
Escalable para grandes infraestructuras.
Desventajas:

Dependencia de la conexión de red.
Mayor latencia en comparación con el almacenamiento local.
Ejemplo práctico: Un usuario accede a un archivo compartido en un servidor remoto mediante NFS.


### Acceso secuencial pseudocódigo:
```
Abrir archivo "datos.txt" en modo lectura
Mientras NO EOF (fin del archivo):
    línea = Leer línea del archivo
    Mostrar línea
Cerrar archivo
```

### Acceso directo mediante su posición pseudocódigo:
```
Abrir archivo "datos.bin" en modo lectura
posición = 1024  # Saltar al byte 1024
Mover cursor a posición
datos = Leer 128 bytes desde posición
Mostrar datos
Cerrar archivo
```

### Acceso utilizando un índice psuedocódigo:
```
Abrir archivo "índice.txt" en modo lectura
Abrir archivo "datos.txt" en modo lectura
Clave = Solicitar clave al usuario
posición = Buscar Clave en índice
Si posición != NULL:
    Mover cursor a posición
    datos = Leer línea en esa posición
    Mostrar datos
Sino:
    Mostrar "Clave no encontrada"
Cerrar archivos
```

### Comparación de ventajas de los diferentes mecanismos de acceso:

1. Acceso Secuencial

Ventajas:

Ideal para datos que se leen o procesan de manera lineal, como registros o archivos de texto grandes.
Simplicidad en el código y manejo.
Eficiente para operaciones de lectura continua.

Casos de Uso:
Procesamiento de datos de registro o archivos de log.
Análisis de grandes volúmenes de datos que se acceden de principio a fin.

2. Acceso Directo

Ventajas:

Permite saltar directamente a cualquier ubicación del archivo sin necesidad de recorrerlo desde el principio.
Rápido acceso a datos específicos, útil en bases de datos y sistemas que requieren acceso aleatorio.

Casos de Uso:

Bases de datos y sistemas de almacenamiento donde se necesita acceso directo a registros.
Archivos binarios grandes donde los datos no se leen en orden lineal.

3. Acceso por Índice

Ventajas:

Rápido acceso a datos usando claves o referencias, lo cual es más eficiente para búsquedas frecuentes.
Optimizado para sistemas que manejan datos estructurados o tablas, como sistemas de archivos y bases de datos relacionales.

Casos de Uso:

Bases de datos con índices que mejoran las consultas.
Sistemas de archivos como NTFS o Ext4 donde se utiliza el sistema de índice para localizar archivos rápidamente.

## Ejercicio 5: Modelo jerárquico y mecanismos de recuperación en caso de fallos

### Modelo Jerárquico para un Sistema de Archivos

## Raíz (`/`)
- **home/**
  - **usuario1/**
    - **documentos/**
      - `proyecto1/`
      - `proyecto2/`
    - **descargas/**
      - `imagenes/`
      - `archivos_zip/`
    - **musica/**
      - `album1/`
      - `album2/`
  - **usuario2/**
    - **documentos/**
    - **escritorio/**
- **var/**
  - **log/**
    - `sistema/`
    - `aplicaciones/`
  - **www/**
    - `sitio1/`
    - `sitio2/`
- **etc/**
  - `red/`
  - `seguridad/`

---

### Explicación
1. **Raíz `/`**: Es el nivel superior de todos los sistemas de archivos.
2. **Primer Nivel**: Contiene directorios principales como:
   - **`home/`**: Directorio donde residen los usuarios y sus datos.
   - **`var/`**: Contiene archivos temporales, logs y datos variables.
   - **`etc/`**: Guarda configuraciones del sistema.
3. **Segundo Nivel**: Subdirectorios dentro de los principales, por ejemplo:
   - **`documentos/`** o **`descargas/`** dentro de `home/usuario1/`.
   - **`log/`** y **`www/`** dentro de `var/`.
4. **Tercer Nivel**: Es el nivel más profundo en este modelo, como los subdirectorios `proyecto1/` o `album1/` dentro de `home/usuario1/`.

Este modelo organiza los directorios de forma lógica y eficiente, comúnmente usado en sistemas operativos basados en Unix/Linux.


### Simulación de una Falla en un Directorio y Pasos para su Recuperación

### **Simulación de la Falla**
1. **Identificación del directorio afectado**:  
   Localiza el directorio que será simulado como fallido (por ejemplo, `/home/usuario1/documentos/`).

2. **Generar la falla (simulada)**:  
   - **Eliminación del directorio** (simulando pérdida accidental):  
     ```bash
     rm -rf /home/usuario1/documentos/
     ```
   - **Corrupción del directorio** (modificando permisos para simular inaccesibilidad):  
     ```bash
     chmod 000 /home/usuario1/documentos/
     ```

---

### **Pasos para la Recuperación**

### 1. **Restaurar desde una copia de seguridad**
- Verifica si tienes un respaldo reciente del directorio (local o en un servidor externo).  
- Restaura el directorio desde el respaldo utilizando herramientas como `rsync` o `cp`.  
  **Ejemplo**:  
  ```bash
  rsync -av /backup/documentos/ /home/usuario1/documentos/
  ```
### Herramientas de respaldo
rsync (Linux)

Descripción: Una herramienta versátil para realizar copias de archivos y sincronizar directorios locales o remotos.
Ventajas: Soporte para copias incrementales, transferencia eficiente de datos.
Ejemplo:
```bash
rsync -av /home/usuario /backup/usuario
```
* Time Machine (macOS)

Descripción: Una solución de respaldo nativa de macOS que realiza copias de seguridad incrementales y automáticas.
Ventajas: Interfaz intuitiva, restauración fácil de versiones anteriores de archivos.


* Windows Backup (Windows)

Descripción: Herramienta integrada para realizar respaldos automáticos de archivos y configuraciones.
Ventajas: Fácil de configurar, integra opciones de restauración del sistema.

* Bacula o Amanda (Linux)

Descripción: Soluciones de respaldo de red escalables para grandes infraestructuras.
Ventajas: Manejo centralizado de respaldos para múltiples dispositivos.

* Herramientas basadas en la nube

Ejemplos: Google Drive, Dropbox, OneDrive, o Amazon S3.
Ventajas: Acceso remoto, respaldo automático, sincronización en múltiples dispositivos.

### Técnicas de respaldo

* Respaldo Completo

Descripción: Copia todos los datos seleccionados en cada ciclo de respaldo.
Ventajas: Fácil restauración, incluye todos los archivos.
Desventajas: Consume mucho tiempo y espacio de almacenamiento.

* Respaldo Incremental

Descripción: Solo guarda los datos modificados desde el último respaldo (completo o incremental).
Ventajas: Eficiente en tiempo y almacenamiento.
Desventajas: Restaurar los datos puede ser más complejo porque requiere múltiples respaldos.

* Respaldo Diferencial

Descripción: Guarda todos los datos modificados desde el último respaldo completo.
Ventajas: Más rápido que un respaldo completo, restauración más sencilla que un incremental.
Desventajas: Consume más espacio que un respaldo incremental.

* Técnica de Versionado

Descripción: Mantiene múltiples versiones de los archivos respaldados.
Ventajas: Permite recuperar estados anteriores de los datos.
Desventajas: Requiere más espacio de almacenamiento.

* Respaldo en Múltiples Ubicaciones

Descripción: Almacena respaldos en diferentes ubicaciones físicas (discos externos, servidores remotos, nube).
Ventajas: Protección contra fallas locales (robo, desastres).
Desventajas: Mayor costo y logística.

# Protección y Seguridad
## Ejercicio 1: Concepto y objetivos de protección y seguridad

### Protección

Definición:
La protección se refiere a los mecanismos que aseguran que los recursos del sistema (memoria, archivos, procesos, dispositivos, etc.) sean utilizados únicamente de la manera autorizada. Se enfoca en controlar el acceso de los procesos y usuarios a los recursos.

Características de la protección:

Evita que programas o usuarios no autorizados accedan o modifiquen recursos del sistema.
Asegura la integridad de los datos y recursos compartidos.
Establece reglas y permisos para acceder a archivos, memoria y dispositivos.
Ejemplo de protección:

Sistema de permisos en archivos (lectura, escritura, ejecución) mediante bits de permisos en sistemas Linux (por ejemplo: chmod 644 archivo.txt).

### Seguridad
Definición:
La seguridad se refiere a la implementación de mecanismos y políticas que protegen al sistema operativo y sus recursos contra amenazas externas e internas, como accesos no autorizados, ataques, pérdida de datos y malware.

Características de la seguridad:

Evita el acceso no autorizado al sistema operativo y los datos del usuario.
Protege contra amenazas como virus, hackers, o vulnerabilidades del sistema.
Involucra medidas físicas, lógicas y criptográficas para proteger el sistema.
Ejemplo de seguridad:

Uso de contraseñas fuertes para el acceso al sistema.
Implementación de firewalls para proteger la red.
Uso de cifrado en sistemas de archivos (por ejemplo: LUKS en Linux).

### Objetivos Principales de un Sistema de Protección y Seguridad

### Confidencialidad

Definición:
La confidencialidad asegura que la información y los recursos solo sean accesibles para los usuarios, procesos o entidades autorizadas. Previene que personas no autorizadas puedan acceder a datos sensibles o confidenciales.

Ejemplos:

Control de accesos a archivos mediante permisos en el sistema operativo (lectura, escritura, ejecución).
Cifrado de datos para proteger información almacenada o transmitida (por ejemplo, SSL/TLS en redes).
Autenticación de usuarios mediante contraseñas, tokens o biometría.
Importancia:

Evita el robo de información privada o sensible.
Protege datos personales, financieros o empresariales.

### Integridad

Definición:
La integridad garantiza que los datos y recursos del sistema permanezcan precisos, completos y sin modificaciones no autorizadas. Protege contra alteraciones accidentales o maliciosas de la información.

Ejemplos:

Uso de sumas de verificación (checksums) y funciones hash (como SHA-256) para validar la integridad de archivos.
Control de versiones para evitar modificaciones no deseadas.
Implementación de permisos que restringen la escritura y modificación de datos a usuarios autorizados.
Importancia:

Garantiza la confianza en los datos y el correcto funcionamiento del sistema.
Evita la corrupción o alteración malintencionada de archivos y procesos.

### Disponibilidad

Definición:
La disponibilidad asegura que los recursos y datos del sistema estén accesibles cuando se necesitan. Protege contra interrupciones o fallos del sistema, ya sean intencionados (ataques) o accidentales.

Ejemplos:

Implementación de respaldos periódicos (backups) para recuperar datos en caso de pérdida.
Uso de sistemas de redundancia, como RAID para discos duros.
Protección contra ataques de denegación de servicio (DoS/DDoS) mediante firewalls y sistemas de monitoreo.
Importancia:

Asegura que los servicios críticos estén disponibles en todo momento.
Minimiza el tiempo de inactividad por fallas o ataques.

### Ejemplo Práctico de Aplicación de los Objetivos en un Sistema Operativo

Supongamos que trabajamos en una empresa que utiliza un servidor Linux para gestionar información confidencial de empleados y archivos críticos de la compañía. A continuación, se detalla cómo se aplican los objetivos de confidencialidad, integridad y disponibilidad en un escenario práctico:

### Confidencialidad
Situación: La empresa tiene una carpeta en el servidor llamada /datos/empleados que contiene información personal y financiera de los empleados.

Aplicación:

Permisos y controles de acceso: Solo los administradores y personal de recursos humanos pueden acceder a la carpeta usando permisos chmod y grupos de usuarios en Linux.

```bash

sudo chown root:recursos_humanos /datos/empleados
sudo chmod 770 /datos/empleados

```

Esto garantiza que solo el propietario (root) y el grupo recursos_humanos puedan leer o modificar los archivos.

Cifrado de archivos: La carpeta está cifrada usando herramientas como LUKS o GPG para proteger la información si alguien no autorizado accede físicamente al servidor.

```bash

gpg -c archivo_confidencial.txt

```
Autenticación: Para iniciar sesión en el servidor, los usuarios deben proporcionar una contraseña fuerte o utilizar autenticación de dos factores (2FA) con claves SSH.

### Integridad

Situación: Se almacenan reportes financieros importantes que no deben ser modificados sin autorización.

Aplicación:

Suma de verificación: Al crear y transferir archivos críticos, se generan sumas hash para asegurar que no sean alterados accidentalmente o de forma maliciosa.

```bash

sha256sum reporte_financiero.txt > hash_reporte.txt

```

Si se realiza algún cambio en el archivo, la verificación del hash mostrará que el contenido ha sido alterado.

Control de versiones: Se utiliza un sistema de control de versiones, como Git, para realizar un seguimiento de los cambios y revertir archivos si es necesario.

```bash

git add reporte_financiero.txt
git commit -m "Agregar reporte financiero actualizado"

```
Permisos restringidos: Solo usuarios autorizados tienen permisos de escritura en archivos críticos.

### Disponibilidad

Situación: La información y servicios críticos del servidor deben estar accesibles para empleados durante el horario laboral.

Aplicación:

Respaldo y recuperación (Backups): Se realizan copias de seguridad diarias de los archivos en un almacenamiento externo o en la nube usando herramientas como rsync o tar.

```bash

tar -czvf backup_diario.tar.gz /datos

```
Redundancia: Se implementa un sistema de almacenamiento redundante RAID 1 para garantizar que si un disco falla, los datos permanezcan disponibles en el segundo disco.

Monitoreo del sistema: Se usan herramientas como Nagios o htop para monitorear el servidor y asegurar que funcione correctamente. Si el servidor detecta un fallo, se envían alertas al administrador.

Protección contra ataques: Un firewall (ej., ufw) y un sistema de detección de intrusos (ej., fail2ban) protegen contra ataques externos que podrían saturar el servidor.

## Ejercicio 2: Clasificación aplicada a la seguridad

### Seguridad física

La seguridad física se refiere básicamente a la protección de todos nuestros elementos desde el punto de vista de posibles desastres naturales como incendios, terremotos o inundaciones, así como también de otras amenazas externas como puede ser robo, problemas eléctricos, etc.… Las diferentes medidas que se suelen tomar pasan por adecuar el espacio dedicado al HW de forma que las amenazas mencionadas queden mitigadas lo máximo posible.

### Seguridad lógica

La seguridad lógica, sin embargo, se encarga de proteger todo lo relacionado con el software o la información contenida en los equipos. Complementa perfectamente a la seguridad física mediante el uso de antivirus, encriptación de la información, ataques de hackers externos y otros mecanismos para la protección y privacidad de la información de cada usuario de la red.

### Seguridad de red

Se centra en proteger las comunicaciones y la infraestructura de red contra accesos no autorizados, ataques y otras amenazas.

### Referencias APA

Yañez, C. (2017, noviembre 8). Tipos de seguridad informática. CEAC. https://www.ceac.es/blog/tipos-de-seguridad-informatica

### El Papel de Cada Clasificación en la Protección de un Sistema Operativo

### Seguridad Física: Proteger el Entorno Físico del Sistema Operativo

Rol:
La seguridad física asegura que los recursos del sistema operativo, como servidores, estaciones de trabajo y dispositivos de almacenamiento, no sean dañados, robados o accedidos sin autorización. Es el primer nivel de defensa para proteger los activos que alojan al sistema operativo.

Aspectos clave:

* Acceso controlado: Restringe el acceso físico al hardware mediante tarjetas, cerraduras o autenticación biométrica.

* Prevención de desastres: Incluye sistemas contra incendios, reguladores de energía y enfriamiento adecuado para evitar daños.

* Protección de servidores: Evita que personas no autorizadas tengan acceso directo a las máquinas donde se ejecuta el sistema operativo.

Ejemplo práctico:

En un centro de datos, los servidores que ejecutan sistemas operativos críticos están protegidos con acceso restringido mediante identificación biométrica y cámaras de vigilancia.

### Seguridad Lógica: Proteger el Sistema Operativo y los Datos

Rol:
La seguridad lógica salvaguarda la integridad, confidencialidad y disponibilidad de los sistemas operativos y los datos que administran, utilizando controles basados en software. Protege contra amenazas internas y externas como malware, accesos no autorizados y errores humanos.

Aspectos clave:

* Gestión de usuarios: Controla el acceso al sistema operativo a través de autenticación y permisos de usuario.

* Cifrado: Protege datos confidenciales almacenados o en tránsito.

* Actualizaciones: Mantiene el sistema operativo protegido frente a vulnerabilidades conocidas mediante parches y actualizaciones.

* Auditorías: Monitorea eventos y actividades para detectar usos indebidos o incidentes de seguridad.

Ejemplo práctico:
En un servidor Linux, la seguridad lógica podría incluir el uso de contraseñas seguras, cifrado de datos sensibles mediante GPG, y SELinux para políticas estrictas de permisos.

### Seguridad de Red: Proteger la Conectividad del Sistema Operativo

Rol:
La seguridad de red garantiza que las comunicaciones y conexiones del sistema operativo con otros dispositivos y redes sean seguras. Previene ataques como interceptación de datos, accesos remotos no autorizados y ataques distribuidos.

Aspectos clave:

* Firewalls: Controlan y filtran el tráfico de red según reglas predefinidas para proteger el sistema operativo.

* Sistemas de detección/prevención de intrusos (IDS/IPS): Identifican y bloquean actividades sospechosas en la red.

* Cifrado en tránsito: Protege la transferencia de datos entre sistemas operativos mediante protocolos como TLS o IPSec.

* VPN: Permite conexiones remotas seguras al sistema operativo.

Ejemplo práctico:

Un servidor Windows protegido por un firewall configurado para aceptar solo conexiones a puertos específicos, junto con una VPN para acceso remoto seguro.

### Ejemplos prácticos de herramientas y técnicas utilizadas en cada clasificación de seguridad

1. Seguridad Física: Herramientas y Técnicas
Ejemplos:

* Cámaras de vigilancia y sistemas de acceso controlado: Herramientas como cerraduras electrónicas y sistemas biométricos controlan el acceso físico a los servidores o centros de datos.

* Sistema de detección de intrusos físicos (IDS físicos): Sensores de movimiento, alarmas y monitoreo continuo de acceso ayudan a detectar actividades sospechosas.

* Cajas fuertes o racks con cerradura: Protegen los equipos físicos alojados en servidores o centros de datos.

2. Seguridad Lógica: Herramientas y Técnicas
Ejemplos:

* Autenticación multifactor (MFA): Agrega una capa extra de seguridad, como contraseñas y tokens, para el acceso a sistemas o datos.

* Cifrado de datos: Herramientas como OpenSSL o GPG aseguran que los datos en tránsito o almacenados estén protegidos.

* Gestión de permisos y roles: Herramientas como sudo en Linux o Active Directory en Windows controlan el acceso a archivos y recursos.

* Antivirus y antimalware: Software como ClamAV o Windows Defender detecta y elimina amenazas como virus o malware.

* Firewall y sistemas de monitoreo (IDS/IPS): Herramientas como iptables en Linux o Windows Firewall filtran el tráfico de red y bloquean intrusos.

3. Seguridad de Red: Herramientas y Técnicas
Ejemplos:

* VPN (Virtual Private Network): Herramientas como OpenVPN o IPSec proporcionan conexiones seguras y cifradas para el acceso remoto a la red.

* Firewalls: Herramientas como pfSense o UFW filtran el tráfico de red según reglas específicas para proteger contra accesos no autorizados.

* Antimalware en red: Herramientas como CrowdStrike o Cylance protegen los sistemas de posibles amenazas externas a través de filtros y monitoreo.

* Segmentación de red: Creación de VLANs y segmentación para separar diferentes segmentos de red y asegurar el acceso controlado.

* TLS/SSL: Protocolos como HTTPS aseguran el cifrado de datos en tránsito y previenen ataques de interceptación.

### Ejercicio 3: Funciones del sistema de protección

### Cómo un Sistema de Protección Controla el Acceso a los Recursos

Un sistema de protección utiliza diversas técnicas y mecanismos para controlar el acceso a los recursos de un sistema operativo. El acceso a estos recursos puede ser a través de archivos, directorios, dispositivos de hardware, o redes. Los objetivos principales del control de acceso son la **confidencialidad**, **integridad** y **disponibilidad** de los recursos.

#### 1. **Identificación y Autenticación**  
- **Identificación:** Un sistema requiere que los usuarios se identifiquen, usualmente a través de un nombre de usuario o ID único.  
- **Autenticación:** Una vez identificado, el sistema verifica la identidad del usuario mediante contraseñas, tokens, o mecanismos biométricos.  
  - **Ejemplo:** En un sistema Linux, el uso de `su` o `sudo` requiere autenticación basada en contraseñas para acceder a recursos privilegiados.

#### 2. **Autorización**  
Una vez autenticado, el sistema verifica si el usuario tiene permisos para acceder a un recurso específico.
- **Permisos y Roles:** Los permisos se definen según el tipo de acceso (lectura, escritura, ejecución) y el rol del usuario.
  - **Ejemplo:** En un sistema de archivos, el uso de `chmod` y `chown` permite asignar permisos de lectura, escritura o ejecución a diferentes usuarios.
  - **Role-Based Access Control (RBAC):** Un mecanismo donde el acceso a los recursos se gestiona según roles predefinidos (por ejemplo, administrador, usuario común, invitado).

#### 3. **Monitoreo y Registro de Actividades**  
El sistema de protección monitorea y registra las actividades de acceso para garantizar que se cumplan las políticas de seguridad.
- **Sistema de Monitoreo y Auditoría:** Herramientas como `auditd` en Linux o Event Viewer en Windows registran accesos, errores y acciones inusuales.
  - **Ejemplo:** Una red privada protegida por un firewall puede registrar intentos fallidos de acceso a los servicios.

#### 4. **Cifrado y Protección de Datos en Transito y Almacenamiento**  
El cifrado asegura que los datos solo puedan ser accedidos por usuarios autorizados.
- **TLS/SSL:** Protege las conexiones de red cifrando los datos en tránsito.
- **Cifrado de Almacenamiento:** Métodos como LUKS en Linux protegen los datos cifrados en reposo.
  - **Ejemplo:** Un servidor web utilizando HTTPS asegura que los datos que viajan entre el navegador y el servidor estén cifrados.

#### 5. **Segmentación de Recursos y Redes**  
- **Segmentación:** Divide el acceso a los recursos en diferentes segmentos o subredes para evitar accesos no autorizados.
  - **Ejemplo:** En una red corporativa, se utilizan VLANs para segmentar el tráfico y limitar el acceso a ciertos recursos según políticas de seguridad.

#### 6. **Políticas de Seguridad y Controles de Acceso Granulares**  
- **Seguridad por Nivel de Privilegio:** El sistema controla el acceso a recursos según el nivel de privilegio del usuario o proceso.
  - **Ejemplo:** En sistemas Unix/Linux, el uso de `sudo` permite que los usuarios con privilegios específicos ejecuten comandos bajo su control.

---

### Conclusión  
Un sistema de protección controla el acceso a los recursos mediante mecanismos de identificación, autenticación, autorización, monitoreo, y cifrado. La aplicación de estas técnicas asegura que solo los usuarios y procesos autorizados puedan acceder a los recursos de manera segura, manteniendo los objetivos de confidencialidad, integridad y disponibilidad.

### Funciones Principales en un Sistema de Protección

#### 1. **Autenticación**  
La autenticación verifica la identidad de un usuario o proceso antes de permitir el acceso a los recursos del sistema.  
- **Propósito:** Asegurar que solo las entidades legítimas puedan acceder a los recursos.  
- **Mecanismos comunes:**  
  - **Contraseñas:** Un usuario ingresa una combinación de nombre de usuario y contraseña para validar su identidad.  
  - **Tokens:** Dispositivos o aplicaciones que generan códigos temporales para autenticar usuarios.  
  - **Biometría:** Huellas dactilares, reconocimiento facial o iris para verificar la identidad.  
  - **Ejemplo:** Un usuario inicia sesión en un sistema mediante su nombre de usuario y contraseña en un servidor Linux usando el comando `login`.

#### 2. **Autorización**  
La autorización determina qué acciones o recursos puede acceder un usuario o proceso, una vez autenticado.  
- **Propósito:** Controlar el acceso basado en permisos y roles, asegurando que los usuarios solo puedan realizar las operaciones permitidas.  
- **Mecanismos comunes:**  
  - **Permisos de archivos/directorios:** Lectura, escritura, ejecución, etc.  
  - **Roles y políticas:** Permisos basados en el rol (administrador, usuario común, invitado).  
  - **Ejemplo:** Un administrador usa `chmod` para asignar permisos a un archivo en un sistema de archivos Linux, restringiendo el acceso solo al dueño o un grupo específico.

#### 3. **Auditoría**  
La auditoría registra y monitorea las actividades dentro del sistema para asegurar que las políticas de seguridad se están cumpliendo.  
- **Propósito:** Detectar y prevenir accesos no autorizados, actividades sospechosas o intentos de violación de seguridad.  
- **Mecanismos comunes:**  
  - **Registros de eventos o logs:** Registra accesos, errores, modificaciones y otros eventos relacionados con el uso del sistema.  
  - **Monitoreo en tiempo real:** Herramientas como `auditd` o `Syslog` en Linux, y Event Viewer en Windows, para capturar y analizar datos de seguridad.  
  - **Ejemplo:** Un administrador revisa los logs de acceso al servidor para identificar intentos fallidos de acceso o acceso no autorizado.

---

### Conclusión  
Autenticación, autorización y auditoría son funciones críticas en un sistema de protección. La **autenticación** asegura que los usuarios o procesos son quienes dicen ser, la **autorización** controla el acceso a los recursos, y la **auditoría** monitorea y registra las actividades para garantizar la seguridad del sistema. Juntas, estas funciones protegen los recursos y datos del sistema operativo.

## Ejercicio 3: Funciones del sistema de protección
### Caso Práctico: Protección en un Sistema de Base de Datos

#### Contexto:
Supongamos que tienes una base de datos que almacena información sensible, como datos de clientes, transacciones y registros de ventas. Esta base de datos necesita proteger la información mediante funciones de autenticación, autorización y auditoría.

#### 1. **Autenticación**  
- **Objetivo:** Asegurar que solo los usuarios legítimos accedan a la base de datos.  
- **Proceso:**  
  - Un administrador o usuario intenta acceder a la base de datos mediante su usuario y contraseña.  
  - El sistema de base de datos verifica las credenciales y autentica al usuario.  
  - Si las credenciales son correctas, el sistema le asigna un token o sesión segura.  
- **Función:** Garantiza que solo los usuarios autorizados accedan a los datos.

  ```sql
  -- Ejemplo de inicio de sesión a una base de datos MySQL.
  mysql -u admin -p mi_base_datos
  ```
#### 2. **Autorización**  
Objetivo: Controlar el acceso a los datos según los roles de los usuarios.

Proceso:

* Una vez autenticado, el sistema verifica los permisos asociados al usuario.

* Si el usuario es un "administrador", tiene acceso a todas las tablas y registros.

* Si el usuario es un "operador", solo puede acceder a ciertos datos, como registros de transacciones o consultas específicas.

Función: Asegura que cada usuario solo acceda a los datos para los que tiene permisos.

  ```sql
-- Ejemplo de consulta para verificar permisos en MySQL.
SHOW GRANTS FOR 'operador'@'localhost';
  ```
#### 3. **Auditoría**  
Objetivo: Monitorear y registrar las actividades de acceso a la base de datos.

Proceso:

* El sistema de base de datos registra todos los accesos, consultas, inserciones y modificaciones.

* El administrador revisa los logs para detectar accesos no autorizados o fallos.

* Si se detecta una actividad sospechosa, se toman medidas para corregir el acceso o bloquear el usuario.

Función: Permite rastrear todas las acciones y garantizar la seguridad de los datos.

```bash
tail -f /var/log/mysql/mysql.log
```

## Ejercicio 4: Implantación de matrices de acceso

### Matriz de Acceso

| **Usuarios**        | **Recursos**     | **Leer (R)** | **Escribir (W)** | **Ejecutar (E)** | **Administrar (A)** |
|---------------------|------------------|---------------|-------------------|-------------------|---------------------|
| **Usuario 1**        | Recurso 1        |       R         |          W         |          E         |           A         |
|                     | Recurso 2        |       R         |          W         |          E         |           A         |
|                     | Recurso 3        |       R         |          W         |          E         |           A         |
|                     | Recurso 4        |       R         |          W         |          E         |           A         |
| **Usuario 2**        | Recurso 1        |       R         |          W         |          E         |           -         |
|                     | Recurso 2        |       R         |          -         |          E         |           -         |
|                     | Recurso 3        |       R         |          W         |          -         |           -         |
|                     | Recurso 4        |       R         |          -         |          -         |           -         |
| **Usuario 3**        | Recurso 1        |       R         |          -         |          -         |           -         |
|                     | Recurso 2        |       -         |          W         |          -         |           -         |
|                     | Recurso 3        |       -         |          -         |          -         |           -         |
|                     | Recurso 4        |       R         |          W         |          -         |           A         |

#### Explicación:
- **Usuario 1**: Tiene acceso completo a todos los recursos.  
- **Usuario 2**: Solo puede leer y ejecutar en ciertos recursos, y no tiene permisos de escritura ni administración.  
- **Usuario 3**: Tiene acceso limitado a algunos recursos, con permisos de lectura y escritura, pero sin acceso administrativo.

### Cómo se utiliza la Matriz de Acceso en un Sistema Operativo

La **Matriz de Acceso** es una herramienta clave para controlar el acceso a recursos en un sistema operativo. Este mecanismo permite definir, por usuario, qué operaciones pueden realizar sobre cada recurso. La matriz establece permisos específicos para cada combinación de usuario y recurso, asegurando que solo los usuarios con los permisos apropiados puedan interactuar con los recursos de manera controlada.

#### 1. **Control de Acceso Basado en Usuarios y Recursos**  
En un sistema operativo, cada usuario tiene un conjunto de permisos asignados que determinan su capacidad para acceder y manipular recursos como archivos, carpetas, bases de datos, dispositivos, etc. La matriz de acceso define:
- **Leer (R)**: Permiso para leer el recurso.
- **Escribir (W)**: Permiso para modificar o escribir en el recurso.
- **Ejecutar (E)**: Permiso para ejecutar el recurso (por ejemplo, un script o un programa).
- **Administrar (A)**: Permiso completo, que incluye leer, escribir y ejecutar además de administrar los permisos del recurso.

#### 2. **Uso Práctico en un Sistema Operativo**  
- **Ejemplo de lectura y escritura**:  
  Si un usuario necesita acceso solo para leer y escribir un archivo, la matriz de acceso reflejará permisos de lectura y escritura, pero no de ejecución o administración.
  
  - **Usuario 2**:  
    - Recurso 1: `R, W`  
    - Recurso 2: `R, E`  
    - Recurso 3: `R, W`  
    - Recurso 4: `R`  

- **Ejemplo de acceso completo**:  
  Si un usuario requiere acceso completo a todos los recursos, la matriz refleja permisos de lectura, escritura, ejecución y administración.

  - **Usuario 1**:  
    - Recurso 1: `R, W, E, A`  
    - Recurso 2: `R, W, E, A`  
    - Recurso 3: `R, W, E, A`  
    - Recurso 4: `R, W, E, A`

#### 3. **Beneficios y Seguridad**  
- **Seguridad y privacidad**: La matriz de acceso permite asignar permisos específicos según los roles y necesidades del usuario, evitando accesos no autorizados.
- **Simplificación de permisos**: Los administradores pueden otorgar o revocar permisos fácilmente basados en la matriz, lo que facilita la gestión de recursos.
- **Auditoría y seguimiento**: La matriz de acceso también facilita el monitoreo y la auditoría de las acciones realizadas por los usuarios sobre los recursos.

La matriz de acceso es fundamental en sistemas operativos para garantizar que cada usuario tenga los permisos adecuados y protegidos para interactuar con los recursos de acuerdo con su función y necesidad.

### Escenario de Acceso No Permitido

#### **Configuración de la Matriz de Acceso:**

| **Usuarios**        | **Recursos**     | **Leer (R)** | **Escribir (W)** | **Ejecutar (E)** | **Administrar (A)** |
|---------------------|------------------|---------------|-------------------|-------------------|---------------------|
| **Usuario 2**        | Recurso 1        |       R         |          W         |          E         |           -         |
|                     | Recurso 2        |       R         |          -         |          E         |           -         |
|                     | Recurso 3        |       R         |          W         |          -         |           -         |
|                     | Recurso 4        |       R         |          -         |          -         |           -         |

#### **Acción del Usuario 2: Intentar acceso a un recurso no permitido.**

Supongamos que el **Usuario 2** intenta acceder a un recurso donde no tiene permisos de escritura o administración:

1. **Usuario 2 intenta escribir en Recurso 1:**

   ```bash
   echo "Intento de escritura" > /ruta/recurso1.txt
    ```
    
Resultado esperado: El sistema operativo detecta que el usuario 2 solo tiene permisos de lectura y ejecución para Recurso 1.

Mensaje de error:
```bash
Permiso denegado: no tienes permisos para escribir en este recurso.
```

Usuario 2 intenta ejecutar un archivo en Recurso 2:
```bash
./ejecutable_recurso2
```
Resultado esperado: El sistema operativo detecta que el usuario 2 tiene permisos de lectura y ejecución, pero no permisos de escritura ni administración.

Mensaje de error:
```bash
Permiso denegado: no puedes ejecutar este archivo.
```
### Conclusión:

La matriz de acceso protege los recursos limitando los permisos que los usuarios pueden tener. El Usuario 2 no puede realizar operaciones no autorizadas (escribir o ejecutar) en los recursos, ya que la matriz de acceso restringe esos permisos. Esto garantiza que solo los usuarios con permisos específicos puedan acceder y manipular los recursos de manera segura.

## Ejercicio 5: Protección basada en el lenguaje

### Concepto de Protección Basada en el Lenguaje

La **protección basada en el lenguaje** se refiere a un enfoque que utiliza mecanismos específicos del lenguaje de programación para asegurar que los programas accedan solo a los recursos necesarios y apropiados durante su ejecución. Este concepto se centra en garantizar la seguridad mediante el uso de políticas y restricciones definidas a nivel de lenguaje.

#### Principios Fundamentales:

1. **Control de Acceso:**
   - El lenguaje establece reglas claras sobre qué partes del código pueden acceder a recursos específicos (como archivos, memoria, dispositivos, etc.).
   - Estas reglas impiden que el código acceda a información o recursos que no debería manejar.

2. **Encapsulamiento y Seguridad:**
   - El lenguaje puede encapsular los datos y protegerlos contra accesos no autorizados.
   - Restricciones en el acceso a objetos o datos aseguran que solo el código autorizado pueda interactuar con ellos.

3. **Políticas Definidas:**
   - El lenguaje puede proveer estructuras o bibliotecas que permitan definir políticas de acceso, como permisos de lectura, escritura o ejecución.
   - Los programas que no respetan estas políticas serán rechazados o limitados en sus funciones.

#### Ejemplo Práctico:

- En lenguajes como Java, los permisos de acceso a archivos, bases de datos o memoria se manejan a través de declaraciones explícitas o niveles de acceso definidos.
  
  ```java
  File file = new File("/ruta/al/archivo.txt");
  if (file.canRead()) {
  }
    ```

    En C, se utiliza el concepto de punteros y permisos de acceso a memoria para controlar el acceso:

    ```C
    FILE *file = fopen("archivo.txt", "r");
    if (file != NULL) {
    fclose(file);
    }
    ```

### Ejemplo de Protección Basada en Lenguaje: Java y Rust

#### **Java: Gestión de Memoria y Accesos Seguros**

En Java, el acceso a recursos, memoria y archivos se controla a través de restricciones y permisos definidos explícitamente mediante el uso de la **API de Seguridad de Java (Java Security API)** y los mecanismos de acceso seguro.

- **Ejemplo de acceso seguro a archivos:**
  
  ```java
  import java.io.File;
  import java.io.FileReader;
  import java.io.IOException;

  public class AccesoArchivo {
      public static void main(String[] args) {
          File file = new File("archivo.txt");
          
          if (file.canRead()) {
              try (FileReader fr = new FileReader(file)) {
                  int data = fr.read();
                  while (data != -1) {
                      System.out.print((char) data);
                      data = fr.read();
                  }
              } catch (IOException e) {
                  e.printStackTrace();
              }
          } else {
              System.out.println("No se tienen permisos para leer el archivo.");
          }
      }
  }
    ```

    Acceso Seguro: La función canRead() verifica si el archivo tiene permisos de lectura antes de acceder a él.

    Gestión de Excepciones: Java maneja excepciones como IOException para asegurarse de que los errores de acceso y lectura se tratan adecuadamente.

    #### Rust: Gestión de Punteros y Accesos Seguros

    Rust es un lenguaje que enfatiza el control de memoria y ofrece características como ownership, borrowing y el sistema de tipos para evitar accesos no autorizados y problemas relacionados con memoria.

 - **Ejemplo de acceso seguro a memoria y archivo:**
    ```rust
    use std::fs::File;
    use std::io::{self, Read};

    fn main() -> io::Result<()> {
    let file_path = "archivo.txt";
    
    let mut file = File::open(file_path)?;
    
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    
    println!("Contenido del archivo: \n{}", contents);
    Ok(())
    }

    ```
    Gestión de Punteros: Rust evita accesos no autorizados a la memoria gracias al sistema de ownership. Solo una parte del código puede "poseer" un puntero a un recurso específico, lo que reduce el riesgo de acceso simultáneo no controlado.

    No hay Acceso Imprudente: El uso de File::open y la función read_to_string asegura que se abren y leen los archivos con manejo explícito de errores.

    ### Comparación del Enfoque Basado en Lenguaje (Java y Rust) con Otros Mecanismos de Protección en Sistemas Operativos

#### 1. **Enfoque Basado en Lenguaje (Java y Rust)**

- **Java**:
  - **Mecanismo de Seguridad**: Utiliza la **Java Security API** para manejar permisos y restricciones. Las excepciones ayudan a controlar errores y accesos indebidos.
  - **Ventajas**: Abstracción y manejo automático de excepciones. Permite la gestión de permisos basados en roles o políticas.
  - **Desventajas**: Dependiente de un entorno de ejecución (JVM) que puede tener limitaciones en ciertos escenarios como sistemas distribuidos o aplicaciones en la nube.

- **Rust**:
  - **Mecanismo de Seguridad**: Utiliza **ownership, borrowing y referencias** para garantizar que solo una parte del código pueda acceder a ciertos recursos.
  - **Ventajas**: No hay acceso simultáneo no autorizado gracias al sistema de ownership. Compila con verificación exhaustiva, lo que reduce errores como desbordamientos de búfer.
  - **Desventajas**: Complejidad en la gestión del ownership puede ser un desafío para los desarrolladores nuevos o el mantenimiento del código.

#### 2. **Mecanismos Clásicos en Sistemas Operativos**

- **ACLs (Access Control Lists)**:
  - **Descripción**: Mecanismos que definen permisos a nivel de archivo o directorio, donde se pueden asignar permisos detallados a diferentes usuarios o grupos.
  - **Ventajas**: Permiten un control granular sobre quién puede acceder o modificar ciertos archivos o directorios.
  - **Desventajas**: A menudo más difíciles de administrar en sistemas grandes y complejos.

- **Usuarios y Grupos**:
  - **Descripción**: Los sistemas operativos como Linux utilizan roles y permisos basados en usuarios y grupos para controlar el acceso.
  - **Ventajas**: Es un modelo bien entendido y ampliamente utilizado. Permite la herencia de permisos y asignación basada en políticas.
  - **Desventajas**: Puede ser complicado de configurar y mantener en entornos más complejos.

- **SELinux (Security-Enhanced Linux)**:
  - **Descripción**: Implementa un sistema de control de acceso con políticas basadas en etiquetas para asegurar un acceso restrictivo y controlado.
  - **Ventajas**: Permite la aplicación de políticas de seguridad más precisas y detalladas.
  - **Desventajas**: Es más difícil de configurar y puede requerir un mayor conocimiento técnico.

- **Firewall y Seguridad de Red**:
  - **Descripción**: Regulan el acceso a través de reglas en las interfaces de red, bloqueando o permitiendo ciertos tipos de tráfico.
  - **Ventajas**: Protege contra accesos no autorizados a través de la red.
  - **Desventajas**: Puede ser más difícil de configurar y monitorear, especialmente en redes grandes y dinámicas.

#### 3. **Comparación de Mecanismos Basados en Lenguaje con otros Mecanismos**

- **Seguridad Basada en Lenguaje** (Java, Rust):
  - **Ventaja**: Protege el acceso a recursos mediante la semántica del lenguaje, garantizando que el acceso no autorizado sea imposible o extremadamente difícil.
  - **Desventaja**: Puede ser más restrictiva y menos flexible para entornos donde se necesite un control preciso o granular.
  
- **ACLs y Usuarios/Grupos**:
  - **Ventaja**: Flexibilidad y granularidad para aplicaciones más complejas.
  - **Desventaja**: Requieren mantenimiento adicional y gestión de políticas más cuidadosa.

- **SELinux y Seguridad de Red**:
  - **Ventaja**: Ofrecen niveles muy específicos de control y políticas ajustadas.
  - **Desventaja**: Pueden ser más complicados y difíciles de administrar, lo que puede aumentar la carga de gestión.

En conclusión, los mecanismos basados en lenguajes como Java y Rust tienen la ventaja de ser intrínsecos al desarrollo, ofreciendo seguridad desde la compilación y evitando problemas comunes relacionados con memoria. Sin embargo, para sistemas más grandes o distribuidos, los mecanismos como ACLs y SELinux pueden ofrecer un control más preciso y granular, aunque con una mayor complejidad en su implementación.

## Ejercicio 6: Validación y amenazas al sistema

### Tipos de amenazas comunes

#### 1. **Malware (Malicious Software)**
- **Descripción**: El malware son programas diseñados con la intención de dañar, robar o interrumpir el funcionamiento de sistemas, redes o dispositivos.
- **Ejemplos**:
  - **Virus**: Software malicioso que se replica y se propaga a través de otros archivos o sistemas.
  - **Troyanos**: Programas que parecen legítimos pero esconden funciones maliciosas.
  - **Ransomware**: Software que bloquea el acceso a los sistemas o datos hasta que se paga un rescate.
- **Impacto**: Pérdida de datos, interrupción de servicios, robo de información confidencial, y daño a la integridad del sistema.

---

#### 2. **Ataques de Fuerza Bruta**
- **Descripción**: Consiste en intentar todas las combinaciones posibles para descubrir contraseñas o claves de acceso, utilizando programas automatizados que prueban combinaciones hasta que encuentran una válida.
- **Ejemplos**:
  - **Contraseñas**: Programas que prueban repetidamente combinaciones de caracteres para acceder a cuentas o sistemas.
  - **Cracking de SSH o RDP**: Intento de acceder a servidores remotos con nombres de usuario y contraseñas predeterminados o robadas.
- **Impacto**: Brechas de seguridad que pueden llevar al acceso no autorizado, robo de datos, o control completo del sistema.

---

#### 3. **Inyección de Código (Code Injection)**
- **Descripción**: Consiste en inyectar código malicioso o malintencionado en aplicaciones o sistemas con el fin de manipular su comportamiento o exponer vulnerabilidades.
- **Ejemplos**:
  - **SQL Injection**: Código malicioso insertado en consultas SQL para obtener acceso no autorizado a bases de datos.
  - **Cross-Site Scripting (XSS)**: Inyección de scripts maliciosos en sitios web para robar información del usuario o ejecutar acciones no autorizadas.
- **Impacto**: Vulneración de datos, fuga de información sensible, modificación o eliminación de datos, y ataques a la integridad de las aplicaciones.

### Mecanismos de validación

#### 1. **Autenticación Multifactor (MFA - Multi-Factor Authentication)**

- **Descripción**: La autenticación multifactor requiere que el usuario proporcione dos o más factores diferentes para verificar su identidad. Los factores típicos incluyen lo siguiente:
  - **Factor 1: Algo que el usuario sabe (contraseña)**.
  - **Factor 2: Algo que el usuario posee (código enviado a un dispositivo móvil, como un SMS o un token de autenticación)**.
  - **Factor 3: Algo que el usuario es (biometría, como huellas dactilares o reconocimiento facial)**.

- **Objetivo**: Aumentar el nivel de seguridad al requerir múltiples verificaciones antes de conceder acceso. Aunque una de las capas de verificación pueda ser comprometida, el atacante tendría que superar todas las verificaciones.

- **Ventajas**:
  - Mayor seguridad frente a ataques como phishing o contraseñas robadas.
  - Reducción de brechas de seguridad debido a que se requiere una combinación de factores.

---

#### 2. **Control de Integridad**

- **Descripción**: El control de integridad asegura que los datos y el sistema no han sido alterados de manera no autorizada. Esto se logra a través de mecanismos que verifican la exactitud y la confianza de los datos.

- **Técnicas comunes**:
  - **Hashes**: Generar una función hash para verificar si un archivo ha sido modificado. Si el hash de un archivo cambia, significa que el archivo ha sido alterado.
    - Ejemplo: Usar algoritmos como SHA-256 o MD5 para calcular la huella digital de un archivo y comparar su integridad con la huella esperada.
  - **Integridad de los datos en tránsito**: Uso de protocolos como TLS/SSL para cifrar el tráfico y verificar que los datos transferidos no han sido manipulados.
  - **Integridad del sistema**: Verificación periódica del sistema para detectar archivos modificados o datos corruptos.

- **Objetivo**: Detectar cambios no autorizados en los datos o en el sistema y prevenir accesos no autorizados o manipulaciones malintencionadas.

- **Ventajas**:
  - Asegura la confidencialidad y la integridad de los datos.
  - Detecta anomalías o violaciones de seguridad.
  - Proporciona auditoría y registro para identificar accesos o manipulaciones inadecuadas.


### Esquema de Validación para un Sistema Operativo con Múltiples Usuarios

1. **Autenticación de Usuarios**:
   - **Usuario y Contraseña**: Cada usuario debe ingresar un nombre de usuario y una contraseña única.
   - **Autenticación Multifactor (MFA)**: Se puede requerir un segundo factor de autenticación como un código enviado a un dispositivo móvil o autenticación biométrica.
   
2. **Control de Accesos Basado en Roles (RBAC - Role-Based Access Control)**:
   - **Asignación de Roles**: Definir roles (administrador, usuario estándar, invitado) con permisos específicos.
   - **Acceso a Recursos**: Cada rol tiene permisos específicos a archivos, directorios, o aplicaciones.
   - **Ejemplo de Permisos**:
     - **Administrador**: Acceso completo a todos los recursos.
     - **Usuario Estándar**: Acceso limitado a recursos específicos, como documentos o aplicaciones.
     - **Invitado**: Acceso solo lectura o restricciones de acceso a ciertos datos.

3. **Verificación de Integridad**:
   - **Hashes y Firmas Digitales**: Verificación periódica de integridad mediante el uso de hashes (SHA-256, MD5) para validar que los archivos y el sistema no han sido modificados.
   - **Auditoría**: Registro de actividades para rastrear accesos y cambios realizados por los usuarios.

4. **Gestión de Sesiones**:
   - **Tiempo de Sesión Limitado**: Limitar el tiempo de inactividad para sesiones de usuario, lo que ayuda a prevenir el acceso no autorizado.
   - **Cierre de Sesión Automático**: Si el usuario no interactúa durante un período predefinido.
   
5. **Privilegios Elevados (sudo o su)**:
   - **Escalado de Privilegios**: Solo los administradores o usuarios autorizados pueden usar comandos que requieren privilegios elevados.
   - **Auditoría de Privilegios**: Registrar y revisar el uso de privilegios elevados para garantizar que solo los usuarios autorizados los utilicen.

6. **Políticas de Contraseñas**:
   - **Requisitos de Contraseña**: Mínimo de longitud, caracteres especiales, y no reutilización de contraseñas.
   - **Reseteo de Contraseñas**: Establecer políticas para el cambio regular de contraseñas.
   
7. **Revocación de Acceso**:
   - **Bloqueo de Cuentas**: Inhabilitar cuentas de usuario sospechosas o comprometidas.
   - **Revisión Periódica**: Revisar cuentas de usuario y permisos asignados regularmente.

## Ejercicio 7: Cifrado

### ¿Qué es el cifrado simétrico ?
El cifrado simétrico, también conocido como cifrado de clave secreta, usa una clave única para cifrar y descifrar datos. Es necesario compartir esta clave con el destinatario. Digamos que usted quiere enviar un mensaje de «Mamá, te quiero». Usted primero escribiría el mensaje, y después configuraría una clave secreta para cifrarlo. Después, simplemente lo enviaría. Cuando mamá reciba el mensaje, entonces deberá introducir la misma clave secreta para descifrar el correo electrónico.

### ¿Qué es el cifrado asimétrico ?
Como indicamos anteriormente, el cifrado asimétrico requiere de dos claves para funcionar. En primer lugar, una clave pública debe publicarse para poder cifrar los datos. En segundo lugar, una clave privada que se usa para descifrar los datos.

La clave pública y la clave privada no son lo mismo, pero están relacionadas. Usted crea su mensaje, y después lo cifra con la clave pública del destinatario. Después, si el destinatario desea descifrar su mensaje, tendrá que hacerlo con su clave privada. Mantenga la clave privada en privado en todo momento. La mejor práctica sería almacenarla localmente. Para lograr esto, hace falta un nivel de conocimientos superior a la media.

El software de correo electrónico del destinatario verá si la clave privada coincide con la clave pública, y entonces solicitará al usuario que escriba la frase de contraseña para descifrar el mensaje.

### Referencias APA

Salman Nadeem, M. (2023, febrero 23). Cifrado simétrico vs. asimétrico: ¿cuál es la diferencia? Mailfence Blog; Mailfence. https://blog.mailfence.com/es/cifrado-simetrico-vs-asimetrico/

### Ejemplo Práctico de Cifrado Simétrico y Asimétrico en Sistemas Operativos

#### 1. **Cifrado Simétrico (AES - Advanced Encryption Standard)**:
   - **Descripción**: El cifrado simétrico utiliza la misma clave tanto para el proceso de cifrado como de descifrado.
   - **Ejemplo Práctico**:  
     - **Protección de Archivos**: Supongamos que un sistema operativo necesita cifrar un archivo de texto confidencial (`documento.txt`).  
     - El archivo se cifra usando una clave compartida entre el emisor y el receptor utilizando el algoritmo AES-256.  
     - Para descifrar el archivo, ambos deben utilizar la misma clave privada compartida previamente.
   
   - **Proceso**:  
     ```bash
     openssl enc -aes-256-cbc -in documento.txt -out documento_cifrado.txt -k "clave_secreta"
     openssl enc -d -aes-256-cbc -in documento_cifrado.txt -out documento_descifrado.txt -k "clave_secreta"
     ```

#### 2. **Cifrado Asimétrico (RSA - Rivest-Shamir-Adleman)**:
   - **Descripción**: El cifrado asimétrico utiliza una clave pública para cifrar y una clave privada para descifrar.
   - **Ejemplo Práctico**:  
     - **Seguridad de Comunicaciones**: Un servidor web necesita asegurar las comunicaciones entre el cliente y el servidor utilizando TLS/SSL.  
     - El servidor genera una clave pública y privada. La clave pública se utiliza para cifrar los datos enviados por el cliente.  
     - Solo el servidor que tiene la clave privada puede descifrar estos datos.
   
   - **Proceso**:  
     1. El servidor genera un par de claves (`public_key.pem`, `private_key.pem`).
     2. El cliente cifra sus datos usando la clave pública del servidor.
     3. El servidor descifra los datos usando su clave privada.
   
     ```bash
     # Generar clave pública y privada
     openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
     openssl rsa -in private_key.pem -pubout -out public_key.pem
     
     # Cliente cifra datos con la clave pública
     openssl rsautl -encrypt -pubin -in datos.txt -inkey public_key.pem -out datos_cifrado.txt
     
     # Servidor descifra datos con la clave privada
     openssl rsautl -decrypt -inkey private_key.pem -in datos_cifrado.txt -out datos_descifrados.txt
     ```
### Simulación del Proceso de Cifrado y Descifrado

#### 1. **Cifrado** (Simétrico - AES-256-CBC):

Supongamos que tenemos el archivo `documento.txt` que queremos cifrar con la clave `clave_secreta`.

```bash
# Cifrar el archivo con AES-256-CBC
openssl enc -aes-256-cbc -in documento.txt -out documento_cifrado.txt -k "clave_secreta"
```
2. Descifrado:
Ahora, para descifrar el archivo cifrado documento_cifrado.txt, usamos la misma clave.

```bash
openssl enc -d -aes-256-cbc -in documento_cifrado.txt -out documento_descifrado.txt -k "clave_secreta"
```

3. Verificación:
El archivo descifrado (documento_descifrado.txt) debería contener el contenido original del archivo.

#### 1. **Cifrado** (Asimétrico con RSA):

Supongamos que hemos generado un par de claves (clave pública public_key.pem y clave privada private_key.pem).

```bash
openssl rsautl -encrypt -pubin -in documento.txt -inkey public_key.pem -out documento_cifrado_rsa.txt
```
5. Descifrado:
Ahora, usando la clave privada para descifrar el archivo cifrado.
```bash
openssl rsautl -decrypt -inkey private_key.pem -in documento_cifrado_rsa.txt -out documento_descifrado_rsa.txt
```
















