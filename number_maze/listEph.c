#include <stdio.h>
#include <stdlib.h>

#include "listEph.h"
void list_print(list l) {
  printf("[");
  if (l != NULL) { //Special case for the first element; there is no ","
    printf("%d", l->x);
    l = l->next;
  }
  while (l != NULL) {
    printf(", %d", l->x);
    l = l->next;
  }
  printf("]\n");
}

bool list_member(int x, list l) {
  return l != NULL && (x == l->x || list_member(x, l->next));
}

list list_make(int x) {
  list newList = malloc(sizeof(struct cons));
  newList->x = x;
  newList->next = NULL;
  return newList;
}

void list_cons(int x, list *l) {
  list tmp = *l;
  *l = malloc(sizeof(struct cons));
  (*l)->x = x;
  (*l)->next = tmp;
}

void list_free(list l) {
  if (l != NULL) {
    list_free(l->next);
    free(l);
  }
}

void list_append(list *l1, list l2) {
  while (*l1 != NULL)
    l1 = &((*l1)->next);
  *l1 = l2;
}

void list_reverse(list *l) {
  list previous = NULL;
  list current = *l;
  list next;
  while (current != NULL) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  *l = previous;
}
