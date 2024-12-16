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













