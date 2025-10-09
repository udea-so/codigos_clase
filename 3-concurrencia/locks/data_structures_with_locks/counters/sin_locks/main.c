#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "counter_wo_locks.h"

#define FALSE 0
#define TRUE 1

#define CNT_END 1000000
#define NUM_THREADS 16

int real_value = 0;
counter_t cnt;

int cnt_value;
int num_threads;
int cnt_end;
int flag_time; 

//
struct timeval t_start, t_end; // Variables para medir el tiempo

// Prototipos de las funciones

void *counting(void *);

// Funcion main

int main(int argc, char *argv[]) {
  int c;
  // Parametros por defecto
  flag_time = FALSE;
  num_threads = NUM_THREADS;
  cnt_end = CNT_END;

  extern char *optarg;
  if(argc > 1) {
    // Determinacion de parametros
    while ((c = getopt(argc, argv, "n:c:tvh")) != EOF) {
      switch (c) {
        case 't':
          // Medicion del tiempo activada
          flag_time = TRUE;     
          break;
        case 'n':
          // Definir el numero de hilos
          num_threads = atoi(optarg);
          break;
        case 'c':
          // Valor final del contador
          num_threads = atoi(optarg);
          break;
        case 'h':
          // Explicacion de como usar el comando
          printf("Uso: %s -n <num_threads> -c <end_counter_value> [-t]\n",argv[0]);
          return 0;    
        default:
          break;
      }
    }
  }
  // printf("Parametros\n");
  // printf("-> Numero de hilos: %d\n", num_threads);
  // printf("-> Valor contador por hilo: %d\n\n", cnt_end);
  init(&cnt);
  int i; 
  pthread_t tid[num_threads];
  if (flag_time == TRUE) {
    gettimeofday(&t_start, NULL);  // Marca de tiempo inicial
    for (i = 0; i < num_threads; i++) {
      pthread_create(&tid[i], NULL, counting, &cnt);
    }
    for (i = 0; i < num_threads; i++) {
      pthread_join(tid[i], NULL);
    }
    gettimeofday(&t_end, NULL); // Marca de tiempo final
    // Se obtiene el tiempo en milisegundos
    float time_elapsed_ms = ((t_end.tv_sec - t_start.tv_sec) * 1000.0) +
                             ((t_end.tv_usec - t_start.tv_usec)/1000.0);
    // Se imprime el tiempo gastado
    printf("-> Tiempo gastado: %f ms\n", time_elapsed_ms);
  }
  else {
    for (i = 0; i < num_threads; i++) {
      pthread_create(&tid[i], NULL, counting, &cnt);
    }
    for (i = 0; i < num_threads; i++) {
      pthread_join(tid[i], NULL);
    }
  }
  // Despliegue de la salida  
  printf("-> El contador debe quedar en: %d\n", num_threads * cnt_end);
  printf("-> El valor real del contador es: %d\n", get(&cnt));
  return 0;
}

// Definiciones de las funciones
void *counting(void *cnt_t) { 
  counter_t *r_cnt = (counter_t*)cnt_t;
  for(int i = 0; i < cnt_end; i++) {
    increment(r_cnt);
  } 
  return NULL; 
}
