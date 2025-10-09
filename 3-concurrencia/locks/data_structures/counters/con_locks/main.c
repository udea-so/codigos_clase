#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "counter_locks.h"


volatile counter_t my_counter;
int N_THREADS = 4;
int COUNTER = 100000000;

struct timeval start, end; // Variables para medir el tiempo

volatile counter_t my_counter;

void* my_thread(void* arg){
  int i;
  for (i = 0; i < COUNTER; i++){
    increment(&my_counter);
  }
  return NULL;
}

int main(int argc, char *argv[]){
  /** 
   * Obtencion de los argumentos (Nota: No hay validacion de que los argumentos sean correctos)
   */ 
  if(argc < 2) {
    // Sin argumentos
    printf("Usando parametros por default para: counter_locks -t N_THREADS -c COUNTER\n");
  }
  else if (argc < 4) {
    // Usando el argumento -t (Numero de hilos)
    if(strcmp(argv[1],"-t") == 0) {
      N_THREADS = atoi(argv[2]);      
    }    
  }
  else {
    if(strcmp(argv[1],"-t") == 0) {
      N_THREADS = atoi(argv[2]);
      COUNTER = atoi(argv[4]);
    } 
    else if (strcmp(argv[3],"-t") == 0) {
      N_THREADS = atoi(argv[4]);
      COUNTER = atoi(argv[2]);
    }            
  }
  printf("- N_THREADS = %d\n",N_THREADS);
  printf("- COUNTER = %d\n", COUNTER);
  
  // Inicializacion del contador
  init(&my_counter);
  pthread_t threads[N_THREADS];

  gettimeofday(&start, NULL);  // Tiempo inicial
  int i;
  for (i = 0; i < N_THREADS; i++){
    int rc = pthread_create(&threads[i], NULL, my_thread, NULL);
    assert(rc == 0);
  }
  
  for (i = 0; i < N_THREADS; i++){
    pthread_join(threads[i], NULL);
  }

  gettimeofday(&end, NULL); // Tiempo final
  
  int value = get(&my_counter);
  float time = ((end.tv_sec - start.tv_sec) * 1000.0) +
               ((end.tv_usec - start.tv_usec)/1000.0);
  
  // Despliegue de los valores del contador (esperado y real) y del tiempo gastado
  printf("counter expected value is %d\n", N_THREADS*COUNTER);
  printf("My counter value is %d\n", value);
  printf("Execution time %3.2f ms\n", time);

  return 0;
}
