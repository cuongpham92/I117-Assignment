#include <stdlib.h>
#include "queue.h"
void queue_init(queue q) {
  *q = NULL;
}

bool queue_isempty(queue q) {
  return (*q == NULL);
}

void queue_enqueue(queue q, int x) {
  list listX = list_make(x);  // list with only x
  list_append(q, listX);
}

int queue_dequeue(queue q) {
  list tmp = *q;
  int x = (*q)->x;
  *q = (*q)->next;
  free(tmp);
  return x;
}
