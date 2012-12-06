#include <stdio.h>
#include <stdlib.h>
#include "ch19ex1-queue.h"

#define MAX_SIZE 5


struct queue_type {
    int queue[MAX_SIZE];
    int num_items, empty_slot, remove_slot;
};

static void terminate(const char *message) {

    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Queue create(void) {

    Queue q = malloc(sizeof(struct queue_type));
    if (q == NULL)
        terminate("Error in create: Queue could not be created.");

    make_empty(q);

    return q;
}

void destroy(Queue q) {

    make_empty(q);
    free(q);
}

void make_empty(Queue q) {

    q->num_items = q->empty_slot = q->remove_slot = 0;
}

bool is_empty(Queue q) {

    return q->num_items == 0;
}

bool is_full(Queue q) {

    return q->num_items == MAX_SIZE;
}

void push(Queue q, Item i) {

    q->empty_slot %= MAX_SIZE;

    if (is_full(q))
        terminate("Error in push: Queue is full");

    q->queue[q->empty_slot++] = i;
    q->num_items++;
}

Item pop(Queue q) {

    Item i;

    if (is_empty(q))
        terminate("Error in pop: Queue is empty.");

    i = q->queue[q->remove_slot++];
    q->remove_slot %= MAX_SIZE;
    q->num_items--;

    return i;
}

Item check_top(Queue q) {

    if (!is_empty(q))
        return q->queue[q->remove_slot];
    else
        terminate("Queue is empty.");
}

Item check_bot(Queue q) {

    if (!is_empty(q))
        return q->queue[(q->empty_slot - 1) % MAX_SIZE];
    else
        terminate("Queue is empty.");
}