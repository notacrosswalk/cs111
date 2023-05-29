#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node_t
{
    int data;
    struct node_t* next;
};

struct stack_t
{
    struct node_t* top;
} Stack;

bool underflow()
{
    if(Stack.top)
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

void push(int val)
{
    struct node_t* newNode = (struct node_t*) calloc(1, sizeof(struct node_t));
    if(newNode == NULL)
    {
        printf("Overflow!\n");
        return;
    }
    newNode->data = val;
    newNode->next = Stack.top;
    Stack.top = newNode;
}

int pop()
{
    if(Stack.top)
    {
        int val = Stack.top->data;
        struct node_t* temp = Stack.top;
        Stack.top = Stack.top->next;
        free(temp);
        temp = NULL;
        return val;
    }
    return -1;
}

void peek()
{
    if(Stack.top)
    {
        printf("Element at the top: %d\n", Stack.top->data);
        return;
    }
    printf("-1\n");
}

void display()
{
    struct node_t* current = Stack.top;
    if(current)
    {
        printf("The elements of the stack are\n");
    }
    else
    {
        printf("The stack is empty.\n");
    }
    while(current)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void delete_stack()
{
    while(!underflow())
    {
        pop();
    }
}

int main()
{
    if(underflow())
    {
        printf("Underflow!\n");
    }
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    display();
    if(!underflow())
    {
        printf("No underflow.\n");
    }
    peek();
    pop();
    pop();
    pop();
    display();
    delete_stack();
    
    return 0;
}