#include <stdio.h>
#include <stdlib.h>
#include "ch19ex1-queue.h"

#define STARTING_SIZE 2


struct queue_type {
    int *queue;
    int num_items, empty_slot, remove_slot, size;
};

static void terminate(const char *message) {

    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

static int mod(int n1, int n2) {

    return n1 < 0 ? (n1 % n2) + n2 : n1 % n2;
}

Queue create(void) {

    Queue q = malloc(sizeof(struct queue_type));
    if (q == NULL)
        terminate("Error in create: Queue could not be created.");

    if ((q->queue = malloc(STARTING_SIZE * sizeof(Item))) == NULL)
        terminate("Error in create: Queue could not be created.");

    make_empty(q);
    q->size = STARTING_SIZE;

    return q;
}

void destroy(Queue q) {

    make_empty(q);
    free(q->queue);
    free(q);
}

void make_empty(Queue q) {

    q->num_items = q->empty_slot = q->remove_slot = q->size = 0;
}

bool is_empty(Queue q) {

    return q->num_items == 0;
}

bool is_full(Queue q) {

    return q->num_items == q->size;
}

void push(Queue q, Item i) {

    int j;

    if (is_full(q)) {
        if ((q->queue = realloc(q->queue, (q->size * 2) * sizeof(Item))) == NULL)
            terminate("Error in push: Could not increase Queue.");
        q->size *= 2;
        for (j = 0; j < q->remove_slot; j++)
            q->queue[q->size / 2 + j] = q->queue[j];
        q->empty_slot = q->size / 2 + j;
    } else
        q->empty_slot %= q->size;

    q->queue[q->empty_slot++] = i;
    q->num_items++;
}

Item pop(Queue q) {

    Item i;

    if (is_empty(q))
        terminate("Error in pop: Queue is empty.");

    i = q->queue[q->remove_slot++];
    q->remove_slot %= q->size;
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
        return q->queue[mod(q->empty_slot - 1, q->size)];
    else
        terminate("Queue is empty.");
}

int check_numItems(Queue q) {

    return q->num_items;
}