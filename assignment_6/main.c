#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

typedef struct bt_node_t 
{
    int data;
    struct bt_node_t *left;
    struct bt_node_t *right;
} TreeNode;

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

TreeNode* newTreeNode(int x)
{
    TreeNode* newNode = (TreeNode *) calloc(1, sizeof(TreeNode));
    newNode->data = x;
    return newNode;
}

void deleteTree(Node *root)
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
    if(root_1 != root_2)
    {
        return false;
    }
    return traverse_and_check(root_1->left, root_2->left) && traverse_and_check(root_1->right, root_2->right); 
}

bool mirror(TreeNode *root_1, TreeNode *root_2)
{
    unmirror(root_1);
    return traverse_and_check(root_1, root_2);    
}

void runMenu()
{

}

int main()
{
    runMenu();
    return 0;
}