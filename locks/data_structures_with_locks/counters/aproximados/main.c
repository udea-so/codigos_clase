#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "counter.h"

#define MAXCNT 1000000
#define NUMTHREADS 4
#define THRESHOLD 1024
typedef struct {
    counter_t *c;
    int max_value;
    int threadID;
    int amt;
} args_t;

void *counting(void *args);

int main() {        
    /* heap variables - shared between threads */
    // --- counter_t *counter = (counter_t *)malloc(sizeof(counter));
    int counter_by_thread = MAXCNT;
    counter_t counter;
    init(&counter,THRESHOLD);
    pthread_t tid[NUMTHREADS];
    //pthread_t *tid = malloc(NUMTHREADS*sizeof(pthread_t));
    
    args_t args = {
                     .c = &counter, 
                     .amt = 1,
                     .max_value = counter_by_thread};
    int i;
    for(i = 0; i < NUMTHREADS; i++) {
        // Un hilo pro procesador        
        args.threadID = i;
        pthread_create(&tid[i], NULL, counting, &args);
        //pthread_create(tid + i, NULL, counting, &args);        
        // printf("Iniciando hilo: %d\n",i+1);
    }
    for(i = 0; i < NUMTHREADS; i++) {
        // pthread_join(tid[i], NULL);
        pthread_join(*(tid + i), NULL);
    }
    printf("\n");
    printf("\nEl contador debe quedar en: %d\n",NUMTHREADS*MAXCNT);
    printf("\nEl valor del contador es: %d\n",get(&counter));

    // --free(counter);
    // free(tid);
    return 0;
}

/* Function Thread */
void *counting(void *args) {
    args_t *rvals = (args_t*)args;    
    for(int i = 0; i < rvals->max_value; i++) {
        update(rvals->c,rvals->threadID,rvals->amt);
    }    
    return NULL;
}
