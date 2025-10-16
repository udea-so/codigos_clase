# Ejemplos de Programación con Hilos en C (`pthread`)

Este repositorio contiene tres ejemplos básicos en C que ilustran distintos aspectos de la programación con hilos usando la biblioteca `pthread`.

> [!Note]
> Si tiene dudas en los siguientes conceptos es bueno que de un repaso antes de analizar los ejemplos.
> * **Apuntadotes** [[link]](https://udea-so.github.io/intro-c/content/CH_02-S02.html)
> * **Estructuras** [[link]](https://udea-so.github.io/intro-c/content/CH_02-S04.html)
> * **Memoria dinamica** [[link]](https://udea-so.github.io/intro-c/content/CH_02-S05.html)

En el siguiente [link](slides/) puede encontrar un resumen teorico rapido sobre el manejo de concurrencia en C.

## Archivos

- [`t0.c`](./t0.c): Ejecución simple de dos hilos concurrentes.
- [`t1.c`](./t1.c): Ejemplo de condición de carrera (*data race*) con variable global compartida.
- [`t2.c`](./t2.c): Paso de argumentos a un hilo y retorno de resultados mediante `pthread_join`.


## Compilación

Para compilar cualquiera de los programas:

```bash
gcc -Wall -o <nombre_salida> <archivo>.c -lpthread
```

Ejemplos:

```bash
gcc -Wall -o t0 t0.c -lpthread
gcc -Wall -o t1 t1.c -lpthread
gcc -Wall -o t2 t2.c -lpthread
```

## Ejecución

### `t0.c`

```bash
./t0
```

**Descripción**:  
Crea dos hilos que imprimen las letras `"A"` y `"B"` respectivamente. Muestra la ejecución concurrente básica sin sincronización.

```
Hilo Principal (main)
      |
      V
[ Inicia y imprime "main: begin" ]
      |
      +--------------------[ pthread_create(&p1, "A") ]----+
      |                                                    |
      +--------[ pthread_create(&p2, "B") ]---+            V
      |                                       |       Hilo p1 ("A")
      |                                       |            |
      V                                       |            V
[ Espera en pthread_join(p1, NULL) ]          |       [ Imprime "A" ]
      |  <------------------------------------(finaliza)-- |
      |
      V
[ Espera en pthread_join(p2, NULL) ]          V
      |  <-------------------------------- Hilo p2 ("B")
      |                                       |
      |                                       V
      |                                  [ Imprime "B" ]
      |  <------------------------------------(finaliza)-- |
      V
[ Imprime "main: end" ]
      |
      V
[ Termina el programa ]
```

---

### `t1.c`

```bash
./t1 <n>
```

Donde `<n>` es el número de veces que cada hilo debe incrementar el contador.

**Ejemplo**:

```bash
./t1 1000000
```

**Descripción**:  
Crea dos hilos que incrementan una variable global `counter` compartida. Como no hay mecanismos de sincronización (ej. mutex), puede generarse una condición de carrera.  
El valor final de `counter` puede diferir del esperado (`n * 2`).

| Hilo A ("p1") | Memoria Compartida | Hilo B ("p2") |
| :--- | :---: | :--- |
| **(Registro_A: ?)** | **(counter: 50)** | **(Registro_B: ?)** |
| 1. Lee `counter` en su registro. | | |
| **(Registro_A: 50)** | | |
| *<-- ¡INTERRUPCIÓN DEL SISTEMA! El Hilo A es pausado. -->* | | |
| | | 1. Lee `counter` en su registro. |
| | **(counter: 50)** | **(Registro_B: 50)** |
| | | 2. Incrementa su registro. |
| | | **(Registro_B: 51)** |
| | | 3. Escribe el registro en `counter`. |
| | **(counter: 51)** | |
| *<-- ¡EL HILO A SE REANUDA! -->* | | |
| 2. Incrementa su registro (basado en el valor viejo que leyó). | | |
| **(Registro_A: 51)** | | |
| 3. Escribe su registro en `counter`. | | |
| | **(counter: 51)** | |

### `t2.c`

```bash
./t2
```

**Descripción**:  
Ejemplo de paso de argumentos a un hilo mediante estructuras, y uso de `pthread_join` para recuperar un valor de retorno asignado dinámicamente.  
El hilo imprime los argumentos recibidos y retorna una estructura con valores enteros.


### Esquema: Flujo de Datos y Memoria en t2.c

Este esquema muestra cómo la memoria se asigna y cómo los punteros viajan entre el hilo `main` y `mythread`.

| STACK (Memoria local y rápida) | HEAP (Memoria dinámica) |
| :--- | :--- |
| **Hilo Principal (`main`)** | |
| `myarg_t args;` | |
| `args.a = 10;` | |
| `args.b = 20;` | |
| `pthread_t p;` | |
| `myret_t* m;` (puntero vacío) | |
| | |
| **1. Crear Hilo** | |
| `pthread_create(&p, ..., &args)` | |
| (Se pasa la dirección de `args`) | |
| `|` | |
| `+--------------------------------------->` | |
| | **Hilo de Trabajo (`mythread`)** |
| | `myarg_t* m = arg;` |
| | (El puntero `m` apunta a `args` en el STACK de `main`) |
| | `printf("%d %d\n", m->a, m->b);` // Imprime "10 20" |
| | |
| | **2. Reservar Memoria** |
| | `myret_t* r = malloc(...)` |
| | | `+----------------->` **[ Bloque de memoria para `myret_t` ]** |
| | | `r->x = 1;` |
| | | `r->y = 2;` |
| | |
| | **3. Retornar Puntero** |
| | `return (void*) r;` |
| | `|` |
| `<---------------------------------------+` | |
| | |
| **4. Esperar y Recibir** | |
| `pthread_join(p, (void**)&m)` | |
| (El puntero `m` de `main` ahora apunta al bloque en el HEAP) | |
| | |
| `printf("returned %d %d\n", m->x, m->y);` // Imprime "returned 1 2" | |
| | |
| **5. Liberar Memoria** | |
| `free(m);` | `[ El bloque de memoria se libera ]` |
| **Fin del programa** | |

