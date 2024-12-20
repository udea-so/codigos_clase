#ifndef __sloppy_counter_h__
#define __sloppy_counter_h__

#include "common.h"
#include "common_threads.h"
#include <stdio.h>

#define NUMCPUS 4  // Numero de CPUS: cat /proc/cpuinfo | grep 'processor' | wc -l
                   // La CPU AMD Ryzen 5 3500U tiene 4 cores fisicos y 8 hilos (threads): NUMCPUS = 8 

typedef struct __counter_t {
  int global;                       // global count
  pthread_mutex_t glock;            // global lock
  int local[NUMCPUS];               // local count (per cpu)
  pthread_mutex_t llock[NUMCPUS];   // ... and locks
  int threshold;                    // update frequency
} counter_t;

// init: record threshold, init locks, init values
//       of all local counts and global count
void init(counter_t *c, int threshold) {
  c->threshold = threshold;
  c->global = 0;
  pthread_mutex_init(&c->glock, NULL);
  int i;
  for (i = 0; i < NUMCPUS; i++) {
    c->local[i] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

// update: usually, just grab local lock and update local amount
//         once local count has risen by 'threshold', grab global
//         lock and transfer local values to it
void update(counter_t *c, int threadID, int amt) {
  // printf("%d\n", threadID);
  // printf("%d\n", c->threshold);
  
  pthread_mutex_lock(&c->llock[threadID]);
  c->local[threadID] += amt;   // assumes amt > 0
  if (c->local[threadID] >= c->threshold) { // transfer to global
	pthread_mutex_lock(&c->glock);
	c->global += c->local[threadID];
	pthread_mutex_unlock(&c->glock);
	c->local[threadID] = 0;
  }
  pthread_mutex_unlock(&c->llock[threadID]);
}

// get: just return global amount (which may not be perfect)
int get(counter_t *c) {
  pthread_mutex_lock(&c->glock);
  int val = c->global;
  pthread_mutex_unlock(&c->glock);
  return val; 	// only approximate!
}

#endif // __sloppy_counter_h__