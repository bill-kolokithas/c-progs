// FIFO Abstract Data Type Structure

#include <stdio.h>
#include "ch19ex1-queue.h"

int main(void)
{
    Queue q1, q2;
    int n, i;

    q1 = create();
    q2 = create();

    for (i = 0; i < 8; i++)
        push(q1, i);

    for (; i > 2; i--)
        pop(q1);

    printf("%d\n", check_top(q1));
    printf("%d\n", check_bot(q1));

    n = pop(q1);
    printf("Popped %d from q1\n", n);
    push(q2, n);
    printf("num items %d\n", check_numItems(q1));
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