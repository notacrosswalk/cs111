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
    printf("Magic Stack:\n");
    for (int i = top; i >= 0; i--)
    {
        if (front[i] == -1)
        {
            continue;
        }
        printf("Block index %d: ", i);
        if (rear[i] < front[i])
        {
            for (int j = front[i]; j <= n; j++)
            {
                printf("%d ", st[i][j]);
            }
            for (int j = 0; j <= rear[i]; j++)
            {
                printf("%d ", st[i][j]);
            }
        }
        else
        {
            for (int j = front[i]; j <= rear[i]; j++)
            {
                printf("%d ", st[i][j]);
            }
        }
        printf("\n");
    }
}

void generate_stack()
{
    st = (int **)calloc(n, sizeof(int *));
    if (st == NULL)
    {
        printf("Memory couldn't be allocated for the magic stack.\n");
        exit(0);
    }
    for (int i = 0; i < n; i++)
    {
        st[i] = (int *)calloc(k, sizeof(int));
    }
    front = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        front[i] = -1;
    }
    rear = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        rear[i] = -1;
    }
    size = (int *)calloc(n, sizeof(int));
}

void free_stack()
{
    for (int i = 0; i < n; i++)
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
    min_index = 0;
    max_index = 0;
    for (int i = 0; i < n; i++)
    {
        if (size[i] < size[min_index])
        {
            min_index = i;
        }
        if (size[i] > size[max_index])
        {
            max_index = i;
        }
    }
    for (int i = top; i >= 0; i--)
    {
        int largest_index = i;
        for (int j = i; j >= 0; j--)
        {
            if (front[j] != -1)
            {
                if (st[j][front[j]] > st[largest_index][front[largest_index]])
                {
                    largest_index = j;
                }
            }
        }
        int *temp = st[largest_index];
        st[largest_index] = st[i];
        st[i] = temp;
        int temp_front = front[largest_index];
        front[largest_index] = front[i];
        front[i] = temp_front;
        int temp_rear = rear[largest_index];
        rear[largest_index] = rear[i];
        rear[i] = temp_rear;
        int temp_size = size[largest_index];
        size[largest_index] = size[i];
        size[i] = temp_size;
    }
}

void push(int x)
{
    if (size[min_index] == k)
    {
        printf("Overflow!\n");
        return;
    }
    if (size[min_index] == 0)
    {
        front[min_index] = 0;
        top = min_index;
    }
    int r = rear[min_index];
    if (r == k - 1)
        r = 0;
    else
        r += 1;
    st[min_index][r] = x;
    rear[min_index] = r;
    size[min_index] += 1;
    sort();
}

int pop()
{
    if (size[max_index] <= 1)
    {
        printf("Underflow!\n");
        return -1;
    }
    int f = front[max_index];
    int data = st[max_index][f];
    if (f == k - 1)
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
    for (int i = top; i >= 0; i--)
    {
        if (size[i] != 1)
            return false;
    }
    return true;
}

void input()
{
    printf("Enter n:\n");
    scanf("%d", &n);
    printf("Enter k:\n");
    scanf("%d", &k);
}

void run()
{
    int c = 1;
    do
    {
        printf("------------\n");
        printf("0 - Exit.\n");
        printf("1 - Push a value.\n");
        printf("2 - Pop a value.\n");
        printf("Enter your choice.\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a value to push.\n");
            int x;
            scanf("%d", &x);
            push(x);
            print_stack();
            break;
        case 2:
            printf("The popped value is %d.\n", pop());
            print_stack();
            break;
        default:
            c = 0;
            break;
        }
    } while (c);
}

int main()
{
    input();
    generate_stack();
    run();
    free_stack();
    return 0;
}