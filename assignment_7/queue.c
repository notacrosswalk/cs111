#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node_t
{
    int data;
    struct node_t* next;
};

struct queue_t
{
    struct node_t* front;
    struct node_t* rear;
} Queue;

bool underflow()
{
    if(Queue.front)
    {
        return false;
    }
    return true;
}

bool overflow()
{
    struct node_t* test = (struct node_t*) malloc(sizeof(struct node_t));
    bool result = false;
    if(!test) result = !result;
    free(test);
    test = NULL;
    return result;   
}

void enqueue(int val)
{
    struct node_t* newNode = (struct node_t*) calloc(1, sizeof(struct node_t));
    if(newNode == NULL)
    {
        printf("Overflow!\n");
        return;
    }
    newNode->data = val;
    if(Queue.front)
    {
        Queue.rear->next = newNode;
        Queue.rear = newNode;
    }
    else
    {
        Queue.front = newNode;
        Queue.rear = newNode;
    }
}

int dequeue()
{
    if(Queue.front)
    {
        int val = Queue.front->data;
        struct node_t* temp = Queue.front;
        Queue.front = Queue.front->next;
        free(temp);
        temp = NULL;
        return val;
    }
    return -1;
}

void peek()
{
    if(Queue.front)
    {
        printf("Element at the front: %d\n", Queue.front->data);
        return;
    }
    printf("-1\n");
}

void display()
{
    struct node_t* current = Queue.front;
    if(current)
    {
        printf("The elements in the queue are\n");
    }
    else
    {
        printf("The queue is empty.\n");
    }
    while(current)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void delete_queue()
{
    while(!underflow())
    {
        dequeue();
    }
}

int main()
{
    if(underflow())
    {
        printf("Underflow!\n");
    }
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    display();
    if(!underflow())
    {
        printf("No underflow.\n");
    }
    peek();
    dequeue();
    dequeue();
    dequeue();
    display();
    delete_queue();

    return 0;
}