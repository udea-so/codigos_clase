#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"
#include "common_threads.h"
#include "counter_lock.h"

#define CNT_END 1000000
#define NUM_THREADS 4

int real_value = 0;
counter_t cnt;
int cnt_value;
int num_threads;

void *counting(void *cnt_t)
{
    counter_t *r_cnt = (counter_t *)cnt_t;
    for (int i = 0; i < CNT_END; i++)
    {
        increment(r_cnt);
    }
    return NULL;
}

int main() {
    init(&cnt);
    int i;
    pthread_t tid[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&tid[i], NULL, counting, &cnt);
    }
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }
    
    printf("-> El contador debe quedar en:%d\n",NUM_THREADS*CNT_END);
    printf("-> El valor real del contador es: %d\n",get(&cnt));

  return 0;
}
