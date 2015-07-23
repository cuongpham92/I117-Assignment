#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "listEph.h"

typedef list *queue;

void queue_init(queue q);
bool queue_isempty(queue q);
void queue_enqueue(queue q, int x);
int queue_dequeue(queue q);

#endif //QUEUE_H
