// This is an implementation of list as EPHEMERAL data structure

#ifndef LISTEPH_H
#define LISTEPH_H
#include <stdbool.h>

struct cons {
  int x;
  struct cons *next;
};

typedef struct cons *list;

void list_print(list l);
bool list_member(int x, list l);

list list_make(int x); //Create (and return) a list containing only x
void list_cons(int x, list *l); //Add x as the first element of l
void list_free(list l);

void list_append(list *l1, list l2); //Append l2 at the end of l1
void list_reverse(list *l);

#endif //LISTEPH_H
