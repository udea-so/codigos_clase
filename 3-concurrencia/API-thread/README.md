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

### `t2.c`

```bash
./t2
```

**Descripción**:  
Ejemplo de paso de argumentos a un hilo mediante estructuras, y uso de `pthread_join` para recuperar un valor de retorno asignado dinámicamente. El hilo imprime los argumentos recibidos y retorna una estructura con valores enteros.


## Referencias

* https://hpc-tutorials.llnl.gov/posix/
* https://beej.us/guide/bggdb/
* https://sourceware.org/glibc/manual/
* https://man7.org/linux/man-pages/man3/pthread_create.3.html