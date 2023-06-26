#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct binary_tree_node_t
{
    int data;
    struct binary_tree_node_t *left;
    struct binary_tree_node_t *right;
} TreeNode;

/***
 * Queue Implementation
 */

struct node_t
{
    TreeNode *data;
    struct node_t *next;
};

struct queue_t
{
    struct node_t *front;
    struct node_t *rear;
} Queue;

bool q_underflow()
{
    if (Queue.front)
    {
        return false;
    }
    return true;
}

bool q_overflow()
{
    struct node_t *test = (struct node_t *)malloc(sizeof(struct node_t));
    bool result = false;
    if (!test)
        result = !result;
    free(test);
    test = NULL;
    return result;
}

void q_enqueue(TreeNode *val)
{
    struct node_t *newNode = (struct node_t *)calloc(1, sizeof(struct node_t));
    if (newNode == NULL)
    {
        printf("Overflow!\n");
        return;
    }
    newNode->data = val;
    if (Queue.front)
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

TreeNode *q_dequeue()
{
    if (Queue.front)
    {
        TreeNode *val = Queue.front->data;
        struct node_t *temp = Queue.front;
        Queue.front = Queue.front->next;
        free(temp);
        temp = NULL;
        return val;
    }
    return NULL;
}

void q_delete_queue()
{
    while (!q_underflow())
    {
        q_dequeue();
    }
}

/***
 *  Binary Tree Functions
 */
TreeNode* newTreeNode(int val)
{
    TreeNode* newNode = (TreeNode*) calloc(1, sizeof(TreeNode));
    newNode->data = val;
    return newNode;
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


bool isBST(TreeNode* root)
{
    if(root == NULL) return true;
    if(root->left)
        if(root->left->data >= root->data)
            return false;
    if(root->right)
        if(root->right->data <= root->data)
            return false;
    return isBST(root->left) && isBST(root->right);
}

int main()
{
    TreeNode* root = input_tree();
    if(isBST(root))
        printf("It is a BST.\n");
    else
        printf("It is not a BST.\n");
    return 0;
}