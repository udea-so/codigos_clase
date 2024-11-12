#ifndef COUNTER_LOCKS_H_
#define COUNTER_LOCKS_H_

typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c);
void increment(counter_t *c);
void decrement(counter_t *c);
int get(counter_t *c);

#endif // COUNTER_LOCKS_H_
