#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct pqnode_t
{
    int priority;
    char *name;
    int id;
    struct pqnode_t* parent;
    struct pqnode_t *left;
    struct pqnode_t *right;
};

struct pqnode_t *root = NULL;

/*
    Queue Implementation
*/

struct node_t
{
    struct pqnode_t* data;
    struct node_t* next;
};

struct queue_t
{
    struct node_t* front;
    struct node_t* rear;
} Queue;

bool q_underflow()
{
    if(Queue.front)
    {
        return false;
    }
    return true;
}

bool q_overflow()
{
    struct node_t* test = (struct node_t*) malloc(sizeof(struct node_t));
    bool result = false;
    if(!test) result = !result;
    free(test);
    test = NULL;
    return result;   
}

void q_enqueue(struct pqnode_t* val)
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

struct pqnode_t* q_dequeue()
{
    if(Queue.front)
    {
        struct pqnode_t* val = Queue.front->data;
        struct node_t* temp = Queue.front;
        Queue.front = Queue.front->next;
        free(temp);
        temp = NULL;
        return val;
    }
    return NULL;
}

void q_delete_queue()
{
    while(!underflow())
    {
        dequeue();
    }
}

void swap(struct pqnode_t *p, struct pqnode_t *q)
{
    if (!p || !q)
        return;

    int temp_priority = p->priority;
    char *temp_name = p->name;
    int temp_id = p->id;

    p->priority = q->priority;
    p->name = q->name;
    p->id = q->id;

    q->priority = temp_priority;
    q->name = temp_name;
    q->id = temp_id;
}

void heapify(struct pqnode_t* node)
{
    if(!node) return NULL;
    if(!node->parent) return node;

    if(node->priority < node->parent->priority)
    {
        swap(node, node->parent);
        heapify(node->parent);
    }
}

void add_patient()
{
    int id = 0;
    printf("\nPatient ID:\n");
    scanf("%d", &id);

    int name_l = 0;
    printf("Patient Name Length:\n");
    scanf("%d", &name_l);

    char* name = (char*) calloc(1, sizeof(char)*(name_l + 1));
    printf("Patient Name:\n");
    scanf("\n%s", name);

    int priority = 0;
    printf("Patient Priority:\n");
    scanf("%d", &priority);

    struct pqnode_t* new_node = (struct pqnode_t*) 
                                calloc(1, sizeof(struct pqnode_t));

    new_node->id = id;
    new_node->name = name;
    new_node->priority =priority; 

    if(root == NULL)
    {
        root = new_node;
        return;
    }


    struct pqnode_t* current = NULL;
    q_enqueue(root);
    while (!q_underflow())
    {
        current = q_dequeue();
        if (current->left)
            q_enqueue(current->left);
        else
        {
            current->left = new_node;
            new_node->parent = current;
            break;
        }
        if (current->right)
            q_enqueue(current->right);
        else
        {
            current->right = new_node;
            new_node->parent = current;
            break;
        }
    }

    q_delete_queue();

    heapify(new_node);
}

void treat()
{
    if()
}