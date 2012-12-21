#ifndef CH19EX1_QUEUE_H
#define CH19EX1_QUEUE_H

#include <stdbool.h>

typedef int Item;

typedef struct queue_type *Queue;

Queue create(void);
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
bool is_full(Queue q);
void push(Queue q, Item i);
Item pop(Queue q);
Item check_tail(Queue q);
Item check_head(Queue q);
int check_numItems(Queue q);
void print_queue(Queue q);

#endif