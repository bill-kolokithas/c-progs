// FIFO Abstract Data Type Structure

#include <stdio.h>
#include "ch19ex1-queue.h"

int main(void)
{
    Queue q1, q2;
    int n, i;

    q1 = create();
    q2 = create();

    for (i = 1; i <= 100; i++)
        push(q1, i);

    print_queue(q1);

    for (i = 1; i <= 50; i++)
        pop(q1);

    print_queue(q1);

    for (i = 1; i <= 25; i++)
        push(q1, i);

    print_queue(q1);

    for (i = 1; i <= 40; i++)
        pop(q1);

    puts("");
    print_queue(q1);
    puts("");

    make_empty(q1);

    for (i = 1; i <= 8; i++) {
        push(q1, i);
        printf("q1 push(%d)\n", i);
    }
    printf("q1  num(%d) *\n", check_numItems(q1));

    for (i = 1; i <= 6; i++)
        printf("q1  pop(%d)\n", pop(q1));

    printf("q1  num(%d) *\n", check_numItems(q1));

    for (i = 1; i <= 2; i++) {
        push(q1, i);
        printf("q1 push(%d)\n", i);
    }
    printf("q1  num(%d) *\n", check_numItems(q1));

    for (i = 1; i <= 1; i++)
        printf("q1  pop(%d)\n", pop(q1));

    printf("q1  num(%d) *\n", check_numItems(q1));
    printf("q1  top(%d) check\n", check_head(q1));
    printf("q1  bot(%d) check\n", check_tail(q1));

    n = pop(q1);
    printf("q1  pop(%d)\n", n);
    push(q2, n);
    printf("q2 push(%d)\n", n);
    n = pop(q1);
    printf("q1  pop(%d)\n", n);
    push(q2, n);
    printf("q2 push(%d)\n", n);

    printf("q1  num(%d) *\n", check_numItems(q1));
    destroy(q1);
    printf("q1  num(%d) destroyed\n", check_numItems(q1));

    while (!is_empty(q2))
        printf("q2  pop(%d)\n", pop(q2));

    push(q2, 3);
    printf("q2 push(%d)\n", 3);
    push(q2, 5);
    printf("q2 push(%d)\n", 5);

    printf("q2  top(%d) check\n", check_head(q2));
    printf("q2  bot(%d) check\n", check_tail(q2));

    printf("q2  num(%d) *\n", check_numItems(q2));
    make_empty(q2);

    if (is_empty(q2))
        printf("q2  num(%d) emptied\n", check_numItems(q2));
    else
        printf("q2 is not empty\n");

    destroy(q2);
    printf("q2  num(%d) destroyed\n", check_numItems(q2));

    return 0;
}