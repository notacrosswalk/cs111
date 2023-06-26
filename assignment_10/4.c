#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100


struct binary_heap_t
{
    int arr[MAX_SIZE];
    int size;
};

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(struct binary_heap_t* heap, int index)
{
    if(index == 0) 
        return;

    int parent_index = (index - 1) / 2;

    if(heap->arr[index] < heap->arr[parent_index])
    {
        swap(&heap->arr[index], &heap->arr[parent_index]);
        heapify_up(heap, parent_index);
    }
}

void heapify_down(struct binary_heap_t* heap, int index)
{
    int smallest = index;

    int l_child = 2*index + 1;
    int r_child = 2*index + 2;

    if(l_child < heap->size && heap->arr[l_child] < heap->arr[index])
    {
        smallest = l_child;
    }

    if(r_child < heap->size && heap->arr[r_child] < heap->arr[smallest])
    {
        smallest = r_child;
    }

    if(smallest != index)
    {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapify_down(heap, smallest);
    }
}

void add_number(struct binary_heap_t* heap, int n)
{
    if(heap->size == MAX_SIZE)
    {
        printf("The queue is full. Insertions are not possible.\n");
        return;
    }

    heap->arr[heap->size] = n;
    heapify_up(heap, heap->size);
    heap->size++;
}

int delete(struct binary_heap_t* heap)
{
    if(heap->size == 0)
    {
        printf("Queue is empty.\n");
        return -1;
    }

    int n = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    return n;
}

void run_menu()
{
    struct binary_heap_t heap;
    heap.size = 0;

    printf("Enter the number of elements you'd like to insert.\n");
    int n;
    scanf("%d", &n);

    printf("Enter the numbers themselves.\n");
    for(int i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);

        add_number(heap, temp);
    }

    printf("Enter the value of k.\n");
    int k;
    scanf("%d", &k);

    for(int i = 0; i < k; i++)
    {
        if(i == k - 1)
            printf("%d\n", delete(heap));
        else
            delete(heap);
    }
}

int main()
{
    run_menu();
    return 0;
}
