// FIFO Abstract Data Type Structure

#include <stdio.h>
#include "ch19ex1-queue.h"

int main(void)
{
    Queue q1, q2;
    int n;

    q1 = create();
    q2 = create();

    push(q1, 1);
    push(q1, 2);
    push(q1, 3);
    push(q1, 4);
    push(q1, 5);
    pop(q1);
    pop(q1);
    printf("%d\n", check_numItems(q1));
    // pop(q1);
    // pop(q1);

    printf("%d\n", check_top(q1));
    printf("%d\n", check_bot(q1));

    n = pop(q1);
    printf("Popped %d from q1\n", n);
    push(q2, n);
    n = pop(q1);
    printf("Popped %d from q1\n", n);
    push(q2, n);

    destroy(q1);

    while (!is_empty(q2))
        printf("Popped %d from q2\n", pop(q2));

    push(q2, 3);
    make_empty(q2);
    if (is_empty(q2))
        printf("q2 is empty\n");
    else
        printf("q2 is not empty\n");

    destroy(q2);

    return 0;
}