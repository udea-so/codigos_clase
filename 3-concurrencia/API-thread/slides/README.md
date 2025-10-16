# API Threads

En la siguiente diapositiva [[link]](27-Interlude_Thread_API.pdf) se resume el contenido de capitulo 27 del libro de Remzi **Interlude: Thread API** [[link]](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-api.pdf)

## Guía Rápida: API de Pthreads con Sintaxis

La siguiente tabla es un resumen rapido de los principales funciones y estructuras de datos para el manejo de concurrencia en C.

| Función | Prototipo   | Descripción  | 
| ------- | ----------- | ------------ | 
| `pthread_t` | —       | Tipo de dato que representa un hilo POSIX.  | 
| `pthread_create` | `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);` | Crea un nuevo hilo y comienza su ejecución en la función `start_routine`.   | 
| `pthread_join` | `int pthread_join(pthread_t thread, void **retval);` | Espera a que el hilo especificado termine. Útil para sincronizar con el hilo y obtener su valor de retorno. | 
| `pthread_exit` | `void pthread_exit(void *retval);` | Termina el hilo actual y opcionalmente devuelve un valor. No se usa explícitamente en los ejemplos, pero es útil si el hilo no retorna por `return`. | 
| `pthread_attr_t`  |    | Tipo de datos para atributos de hilo (no usado en los ejemplos, pero importante para configuración avanzada).  
| `volatile` (modificador) | — | No es parte de `pthread`, pero en `t1.c` se usa con `counter` para evitar optimizaciones de compilador en variables compartidas. |

> [!tip]
> En los siguientes links puede encontar varios ejemplos para profundizar los conceptos tratados en la tabla anterior:
> * **Hilos** [[link]](https://udea-so.github.io/udea-so/docs/laboratorio/tutoriales/hilos/threads)
> * **Sincronizacion** [[link]](https://udea-so.github.io/udea-so/docs/laboratorio/tutoriales/hilos/sincronizacion)


## Recursos


* https://oslab.kaist.ac.kr/ee415-spring-2022/
* https://www.cse.iitb.ac.in/~mythili/os/