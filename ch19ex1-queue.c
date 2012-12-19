#include <stdio.h>
#include <stdlib.h>
#include "ch19ex1-queue.h"

#define STARTING_SIZE 2


struct queue_type {
    int *queue;
    int num_items, bot, top, size;
};

static void terminate(const char *message) {

    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

static int mod(int n1, int n2) {

    return n1 < 0 ? (n1 % n2) + n2 : n1 % n2;
}

Queue create(void) {

    Queue q;

    if ((q = malloc(sizeof(struct queue_type))) == NULL)
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

    q->num_items = q->bot = q->top = q->size = 0;
}

bool is_empty(Queue q) {

    return q->num_items == 0;
}

bool is_full(Queue q) {

    return q->num_items == q->size;
}

void push(Queue q, Item i) {

    if (is_full(q)) {
        if ((q->queue = realloc(q->queue, (q->size * 2) * sizeof(Item))) == NULL)
            terminate("Error in push: Could not increase Queue.");

        int j;
        if (q->top < q->size / 2) {
            for (j = 0; j < q->top; j++)
                q->queue[q->size + j] = q->queue[j];
            q->bot = q->size + j;
        }
        else {
            for (j = q->top; j < q->size * 2; j++)
                q->queue[q->size + j] = q->queue[j];
            q->top += q->size;
        }
        q->size *= 2;
    } else
        q->bot %= q->size;

    q->queue[q->bot++] = i;
    q->num_items++;
}

Item pop(Queue q) {

    Item i;

    if (is_empty(q))
        terminate("Error in pop: Queue is empty.");

    if (q->num_items < q->size / 2 - q->size / 8) {
        int j;
        q->size /= 2;

        if (q->bot > q->size) {
            for (j = (q->top >= q->size) ? q->top : q->size; j < q->bot; j++)
                q->queue[q->bot - j] = q->queue[j];

            q->top = q->top >= q->size ? 0 : q->top;
            q->bot -= q->size;
        }
        else if (q->top >= q->size) {
            for (j = 0; j < q->size; j++)
                q->queue[q->size - j] = q->queue[q->size * 2 - j];
            q->top -= q->size;
        }
        if ((q->queue = realloc(q->queue, (q->size) * sizeof(Item))) == NULL)
            terminate("Error in pop: Could not decrease Queue.");
    }
    i = q->queue[q->top++];
    q->top %= q->size;
    q->num_items--;

    return i;
}

Item check_top(Queue q) {

    if (is_empty(q))
        terminate("Queue is empty.");

    return q->queue[q->top];
}

Item check_bot(Queue q) {

    if (is_empty(q))
        terminate("Queue is empty.");

    return q->queue[mod(q->bot - 1, q->size)];
}

int check_numItems(Queue q) {

    return q->num_items;
}