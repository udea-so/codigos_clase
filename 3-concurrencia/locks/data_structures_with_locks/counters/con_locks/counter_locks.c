#include <assert.h>
#include <pthread.h>
#include "counter_locks.h"

void init(counter_t *c) {
  c->value = 0;
  int rc = pthread_mutex_init(&c->lock, NULL);
  assert(rc == 0);
}

void increment(counter_t *c) {
  int rc = pthread_mutex_lock(&c->lock);
  assert(rc == 0);
  c->value++;
  rc = pthread_mutex_unlock(&c->lock);
  assert(rc == 0);
}

void decrement(counter_t *c) {
  int rc = pthread_mutex_lock(&c->lock);
  assert(rc == 0);
  c->value--;
  rc = pthread_mutex_unlock(&c->lock);
  assert(rc == 0);
}

int get(counter_t *c) {
  int rc = pthread_mutex_lock(&c->lock);
  assert(rc == 0);
  int result = c->value;
  rc = pthread_mutex_unlock(&c->lock);
  assert(rc == 0);
  return result;
}
