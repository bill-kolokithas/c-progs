#include <stdio.h>
#include <stdlib.h>
#include "ch19ex1-queue.h"

struct node {
    Item data;
    struct node *next;
};

struct queue_type {
    struct node *top, *bot;
};

static void terminate(const char *message) {
  
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Queue create(void)
{
    Queue q = malloc(sizeof(struct queue_type));
    if (q == NULL)
        terminate("Error in create: Queue could not be created.");
    
    q->top = NULL;

    return q;
}

void destroy(Queue q)
{
    make_empty(q);
    free(q);
}

void make_empty(Queue q)
{
    while (!is_empty(q))
        pop(q);
}

bool is_empty(Queue q)
{
    return q->top == NULL;
}

bool is_full(Queue q)
{
    return false;
}

void push(Queue q, Item i)
{
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
        terminate("Error in push: Queue is full.");

    new_node->data = i;
    new_node->next = NULL;

    if (q->top == NULL)
        q->top = new_node;
    else
        q->bot->next = new_node;

    q->bot = new_node;
}

Item pop(Queue q) {
  
    struct node *old_top;
    Item i;

    if (is_empty(q))
        terminate("Error in pop: Queue is empty.");

    old_top = q->top;
    i = old_top->data;
    q->top = old_top->next;
    free(old_top);

    return i;
}

Item check_top(Queue q) {

    if (!is_empty(q))
        return q->top->data;
    else
        terminate("Queue is empty.");
}

Item check_bot(Queue q) {

    if (!is_empty(q))
        return q->bot->data;
    else
        terminate("Queue is empty.");
}