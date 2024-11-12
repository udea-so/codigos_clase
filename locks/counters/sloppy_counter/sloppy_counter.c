#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include "common.h"
#include "common_threads.h"
#include "sloppy_counter.h"

#define CNT_END 10000000
#define NUM_THREADS 4
#define THRESHOLD 16
#define AMT 1

/*
gcc -Wall -I../include sloppy_counter.c -lpthread -o sloppy_counter
*/

int real_value = 0;
counter_t cnt;
int cnt_value;
int num_threads;

typedef struct {
    counter_t *c;
    int max_value;
    int threadID;
    int amt;
} args_t;


// Prototipos de las funciones

void *counting(void *);

// Funcion main

int main() {
  init(&cnt, THRESHOLD);
  int counter_by_thread = CNT_END;
  double t_ini, t_end;
  pthread_t tid[NUM_THREADS];

  args_t args = {
                  .c = &cnt, 
                  .amt = 1,
                  .max_value = counter_by_thread
                };
  
  int i;
  t_ini = GetTime(); // Marca de tiempo inicial

  for (i = 0; i < NUM_THREADS; i++) {
    // Inicializando argumentos
    args.threadID = i;   
    pthread_create(&tid[i], NULL, counting, &args);
  }
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }
  t_end = GetTime(); // Marca de tiempo final

  printf("-> Tiempo gastado: %lf seg\n", t_end - t_ini);
  printf("-> El contador debe quedar en: %d\n", NUM_THREADS * CNT_END);
  printf("-> El valor real del contador es: %d\n", get(&cnt));

  return 0;
}

// Definiciones de las funciones

/* Function Thread */
void *counting(void *args) {
    args_t *rvals = (args_t*)args;    
    for(int i = 0; i < rvals->max_value; i++) {
        update(rvals->c,rvals->threadID,rvals->amt);
    }    
    return NULL;
}