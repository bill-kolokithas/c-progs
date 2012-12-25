#include <stdio.h>
#include <stdlib.h>
#include "ch19ex1-queue.h"

#define STARTING_SIZE 2


struct queue_type {
    int *queue;
    int num_items, tail, head, size;
};

static void terminate(const char *message) {

    printf("%s\n", message);
    exit(EXIT_FAILURE);
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

    q->num_items = q->head = 0;
    q->tail = -1;
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
        if (q->head < q->size / 2) {
            for (j = 0; j < q->head; j++)
                q->queue[q->size + j] = q->queue[j];
            q->tail = q->size + --j;
        } else {
            for (j = q->head; j < q->size; j++)
                q->queue[q->size + j] = q->queue[j];
            q->head += q->size;
        }
        q->size *= 2;
    }
    q->tail = (q->tail + 1) % q->size;
    q->queue[q->tail] = i;
    q->num_items++;
}

Item pop(Queue q) {

    Item i;

    if (is_empty(q))
        terminate("Error in pop: Queue is empty.");

    if (q->num_items < q->size / 2 - q->size / 8) {
        int j;
        q->size /= 2;

        if (q->tail > q->size) {
            int k;
            j = (q->head >= q->size) ? q->head : q->size;
            for (k = 0; j <= q->tail; j++, k++)
                q->queue[k] = q->queue[j];

            q->head = q->head >= q->size ? 0 : q->head;
            q->tail = --k;
        }
        else if (q->head >= q->size) {
            q->head -= q->size;
            for (j = q->head; j < q->size; j++)
                q->queue[j] = q->queue[q->size + j];
        }
        if ((q->queue = realloc(q->queue, (q->size) * sizeof(Item))) == NULL)
            terminate("Error in pop: Could not decrease Queue.");
    }
    i = q->queue[q->head++];
    q->head %= q->size;
    q->num_items--;

    return i;
}

void print_queue(Queue q) {

    int i = q->head % 10;

    while (i--)
        printf("    ");

    for (i = q->head; i < q->head + q->num_items; i++) {
        if (i % 10 == 0)
            puts("");
        printf("%4d", q->queue[i % q->size]);
    }
    puts("\n");
}

Item check_head(Queue q) {

    if (is_empty(q))
        terminate("Queue is empty.");

    return q->queue[q->head];
}

Item check_tail(Queue q) {

    if (is_empty(q))
        terminate("Queue is empty.");

    return q->queue[q->tail];
}

int check_numItems(Queue q) {

    return q->num_items;
}