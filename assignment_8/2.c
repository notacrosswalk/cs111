#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct priority_queue
{
    int *arr;
    int size;
} PQ;

void initialize_pq(int n)
{
    if(n < 1)
    {
        printf("Invalid value.\n");
        return;
    }

    PQ.size = n;
    PQ.arr = (int *) calloc(n, sizeof(int));
}

int left(int i)
{
    return (2*i) + 1;
}