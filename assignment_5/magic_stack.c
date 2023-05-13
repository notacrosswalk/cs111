#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int **st;
int top;
int *front;
int *rear;
int *size;
int n;
int k;
int min_index;
int max_index;

void print_stack()
{
    for(int i = top; i >= 0; i--)
    {
        printf("%d: ", i);
        if(front[i] == -1)
        {
            continue;
        }
        if(rear[i] < front[i])
        {
            for(int j = front[i]; j <= n; j++)
            {
                printf("%d ", st[i][j]);
            }
            for(int j = 0; j <= rear[i]; j++)
            {
                printf("%d ", st[i][j]);
            }
        }
        else
        {
            for(int j = front[i]; j <= rear[i]; j++)
            {
                printf("%d ", st[i][j]);
            }
        }
        printf("\n");
    }
}

void generate_stack()
{
    st = (int **) calloc(n, sizeof(int *));
    for(int i = 0; i < n; i++)
    {
        st[i] = (int *) calloc(k, sizeof(int));
    }
    front = (int *) calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        front[i] = -1;
    }
    rear = (int *) calloc(n, sizeof(int));
    size = (int *) calloc(n, sizeof(int));
}

void free_stack()
{
    for(int i = 0; i < n; i++)
    {
        free(st[i]);
        st[i] = NULL;
    }
    free(st);
    st = NULL;
    free(front);
    free(rear);
    front = NULL;
    rear = NULL;
}

void sort()
{
    int largest_index = 0;
    for(int i = 0; i < n; i++)
    {
        if(size[i] < size[min_index])
        {
            min_index = i;
        }
        if(size[i] > size[max_index])
        {
            max_index = i;
        }
        if(front[i] != -1)
        {
            if(st[i][front[i]] > st[largest_index][front[largest_index]])
            {
                largest_index = i;
            }
        }
    }
    int *temp = st[largest_index];
    st[largest_index] = st[top];
    st[top] = temp;
}

void push(int x)
{
    if(size[min_index] == k)
    {
        printf("Overflow!\n");
        exit(0);
    }
    int r = rear[min_index];
    if(r == k - 1)
        r = 0;
    else
        r += 1;
    st[min_index][r] = x;
    rear[min_index] = r;
    size[min_index] += 1;
    if(size[min_index] == 1)
    {
        top = min_index;
    }
    sort();
}

int pop()
{
    if(size[max_index] <= 1)
    {
        printf("Underflow!\n");
        exit(0);
    }
    int f = front[max_index];
    int data = st[max_index][f];
    if(f == k - 1)
        f = 0;
    else
        f += 1;
    front[max_index] = f;
    size[max_index] -= 1;
    sort();
    return data;
}

bool search()
{
    for(int i = top; i >= 0; i--)
    {
        if(size[i] != 1)
            return false;
    }
    return true;
}


int main()
{
    return 0;
}