#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/** 
 * Struct definitions
*/

typedef struct bt_node_t 
{
    int data;
    struct bt_node_t *left;
    struct bt_node_t *right;
} TreeNode;

typedef struct queue_node_t
{
    int data;
    struct queue_node_t *next;
} QueueNode;

struct queue_t
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

typedef struct stack_node_t
{
    TreeNode *data;
    struct stack_node_t *next;
} StackNode;

struct stack_t
{
    StackNode* top;
} Stack_1, Stack_2;

/** 
 * Stack implementation
 */

bool isEmpty(struct stack_t* Stack)
{
    if(Stack->top == NULL)
    {
        return true;
    }
    return false;
}

void empty_stack(struct stack_t* Stack)
{
    while(Stack->top != NULL)
    {
        StackNode *temp = Stack->top;
        Stack->top = Stack->top->next;
        free(temp);
    }
}

void push(struct stack_t* Stack, TreeNode* x)
{
    StackNode *newNode = (StackNode*) calloc(1, sizeof(StackNode));
    if(newNode == NULL)
    {
        printf("Stack Overflow.\n");
        exit(0);
    }
    newNode->data = x;
    newNode->next = Stack->top;
    Stack->top = newNode;
}

TreeNode* pop(struct stack_t* Stack)
{
    if(Stack->top == NULL)
    {
        return NULL;
    }
    TreeNode* data = Stack->top->data;
    StackNode *temp = Stack->top;
    Stack->top = Stack->top->next;
    free(temp);
    temp = NULL;
    return data;
}

/**
 * Queue implementation
 */

void clear_queue()
{
    while(Queue.front != NULL)
    {
        QueueNode *temp = Queue.front;
        Queue.front = Queue.front->next;
        free(temp);
    }
    Queue.rear = NULL;
}

void enqueue(int x)
{
    QueueNode* newNode = (QueueNode*) calloc(1, sizeof(QueueNode));
    if(newNode == NULL)
    {
        printf("Stack Overflow!\n");
        exit(0);
    }
    newNode->data = x;
    if(Queue.front == NULL)
    {
        Queue.front = newNode;
        Queue.rear = newNode;
    }
    else
    {
        Queue.rear->next = newNode;
        Queue.rear = newNode;
    }
}

int dequeue()
{
    if(Queue.front == NULL)
    {
        return -1;
    }
    int data = Queue.front->data;
    QueueNode* temp = Queue.front;
    Queue.front = Queue.front->next;
    free(temp);
    temp = NULL;
    return data;
}

/**
 * Binary Tree implementation
 */

TreeNode* newTreeNode(int x)
{
    TreeNode* newNode = (TreeNode *) calloc(1, sizeof(TreeNode));
    newNode->data = x;
    return newNode;
}

void deleteTree(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
    root = NULL;
}

TreeNode* input_tree()
{
    int n;
    printf("Enter the number of levels in the binary tree\n"
            "you'd like to construct.\n");
    scanf("%d", &n);
    if(n < 1)
    {
        printf("The number of levels has to be a positive integer.\n");
        exit(0);
    }
    int size = (int)pow(2, n) - 1;
    int arr[size];
    printf("Enter the nodes of the tree in a level order traversal.\n");
    printf("Enter -1 if a child is NULL.\n");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", arr+i);
    }
    TreeNode* node_ptrs[size];
    TreeNode* root = newTreeNode(arr[0]);
    node_ptrs[0] = root;
    for(int i = 1; i < size; i++)
    {
        if(arr[i] == -1)
        {
            node_ptrs[i] = NULL;
        }
        else
        {
            node_ptrs[i] = newTreeNode(arr[i]); 
        }
        TreeNode *parent = NULL;
        int parent_index = 0;
        if(i%2)
        {
            parent_index = (i - 1)/2;
            parent = node_ptrs[parent_index];
            parent->left = node_ptrs[i];
        }
        else
        {
            parent_index = (i - 2)/2;
            parent = node_ptrs[parent_index];
            parent->right = node_ptrs[i];
        }
    }
    return root;
}

void preorder_traversal(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

/** 
 * Circular Queue
 */

void runCQueue()
{
    // Input

    printf("Enter n.\n");
    int n;
    scanf("%d", &n);

    printf("Enter the values of k.\n");
    int k[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &k[i]);
    }

    // Process

    for(int i = 0; i < n; i++)
    {

        // Generate circular array
        
        int size = k[i];
        int a[k[i]];
        bool flag[k[i]];
    
        for(int j = 0; j < k[i]; j++)
        {
            a[j] = j + 1;
            flag[j] = true;
        }

        // Eliminate alternate elements

        bool _switch = true;

        int j = 0;
        while(true)
        {
            if(size == 1)
            {
                break;
            }
            if(j == k[i])
            {
                j = 0;
            }
            if(_switch && flag[j])
            {
                flag[j] = false;
                _switch = false;
                size--;
            }
            if(flag[j])
            {
                _switch = true;
            }
            j++;
        }

        for(int j = 0; j < k[i]; j++)
        {
            if(flag[j] == true)
            {
                printf("%d ", a[j]);
                enqueue(a[j]);
            }
        }
    }
    printf("\n");

    // Print the front and rear of the queue
    printf("%d %d\n", Queue.front->data, Queue.rear->data);

    clear_queue();
}

/**
 * Zig-zag traversal
 */

void zig_zag_traversal(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }

    TreeNode *current = root;
    
    struct stack_t* present_stack = &Stack_1;
    struct stack_t* other_stack = &Stack_2;
    
    push(present_stack, current);
    
    bool l_to_r = true;
    
    while(!isEmpty(present_stack))
    {
        current = pop(present_stack);

        if(current != NULL)
        {
            if(l_to_r)
            {
                if(current->left != NULL)
                    push((other_stack), current->left);
                if(current->right != NULL)
                    push((other_stack), current->right);
            }
            else
            {
                if(current->right != NULL)
                    push((other_stack), current->right);
                if(current->left != NULL)
                    push((other_stack), current->left);
            }

            printf("%d ", current->data);
        }

        if(isEmpty(present_stack))
        {
            struct stack_t* temp = present_stack;
            present_stack = other_stack;
            other_stack = temp;
            l_to_r = !l_to_r;
        }
    }
    printf("\n");

    empty_stack(present_stack);
    empty_stack(other_stack);
}

void runZigZag()
{
    TreeNode *root = input_tree();

    printf("The zig-zag traversal is:\n");
    zig_zag_traversal(root);

    deleteTree(root);
}

/**
 * Mirror 
 */

void unmirror(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    unmirror(root->left);
    unmirror(root->right);
}

bool traverse_and_check(TreeNode *root_1, TreeNode *root_2)
{
    if(root_1 == NULL && root_2 == NULL)
    {
        return true;
    }
    if(root_1 == NULL)
    {
        return false;
    }
    if(root_2 == NULL)
    {
        return false;
    }
    if(root_1->data  != root_2->data)
    {
        return false;
    }
    return traverse_and_check(root_1->left, root_2->left) 
            && traverse_and_check(root_1->right, root_2->right); 
}

void mirror(TreeNode *root_1, TreeNode *root_2)
{
    unmirror(root_1);

    bool result =  traverse_and_check(root_1, root_2);    

    if(result)
    {
        printf("Yes, they are mirrors of each other.\n");
    }
    else
    {
        printf("No, they are not mirrors of each other.\n");
    }
}

void runMirror()
{
    TreeNode *root_1 = input_tree();
    TreeNode *root_2 = input_tree();
    
    mirror(root_1, root_2);
    deleteTree(root_1);
    deleteTree(root_2);
}

/**
 * Main program
 */

void runMenu()
{
    printf("MENU\n");
    printf("1 - Circular queues question\n");
    printf("2 - Check if two trees are mirrors of each other\n");
    printf("3 - Zigzag tree traversal\n");
    int choice = 0;
    printf("Enter your choice.\n");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: 
            runCQueue();
            break;
        case 2:
            runMirror();
            break;
        case 3:
            runZigZag();
            break;
        default:
            printf("That is an invalid value.\n");
            exit(0);
    }
}

int main()
{
    runMenu();
    return 0;
}