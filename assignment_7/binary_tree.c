#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

bool empty(TreeNode *root)
{
    if (!root)
        return false;
    return true;
}

// Inserts in the first available position in level order traversal
void insert(TreeNode *root, int val)
{
    if (root == NULL)
        return;
    TreeNode *current = root;
    TreeNode **dest = NULL;
    q_enqueue(root);
    while (!q_underflow())
    {
        current = q_dequeue();
        if (current->left)
            q_enqueue(current->left);
        else
        {
            dest = &(current->left);
            break;
        }
        if (current->right)
            q_enqueue(current->right);
        else
        {
            dest = &(current->right);
            break;
        }
    }
    TreeNode *newNode = (TreeNode *)calloc(1, sizeof(TreeNode));
    newNode->data = val;
    *dest = newNode;
    q_delete_queue();
}

TreeNode *delete(TreeNode *root, int val)
{
    if (root == NULL)
        return root;
    if (root->left == NULL && root->right == NULL)
    {
        if (root->data == val)
        {
            free(root);
            root = NULL;
            return root;
        }
        return root;
    }
    TreeNode *current = root;
    TreeNode *dest = NULL;
    TreeNode *last = NULL;
    q_enqueue(root);
    while (!q_underflow())
    {
        current = q_dequeue();
        if (current->data == val)
        {
            dest = current;
        }
        if (current->left)
        {
            last = current->left;
            q_enqueue(current->left);
        }
        if (current->right)
        {
            last = current->right;
            q_enqueue(current->right);
        }
    }
    if (dest != NULL)
    {
        dest->data = current->data;
        if (last->left == current)
            last->left = NULL;
        if (last->right == current)
            last->right = NULL;
        free(current);
        current = NULL;
    }

    q_delete_queue();
    return root;
}

void preorder_traversal(TreeNode* root)
{
    if(root == NULL) return;
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void inorder_traversal(TreeNode* root)
{
    if(root == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

void postorder_traversal(TreeNode* root)
{
    if(root == NULL) return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
}

TreeNode* search(TreeNode* root, int val)
{
    TreeNode* current = NULL;
    TreeNode* result = NULL;
    q_enqueue(root);
    while(!q_underflow())
    {
        current = q_dequeue();
        if(current->data == val)
        {
            result = current;
            break;
        }
        if(current->left) q_enqueue(current->left);
        if(current->right) q_enqueue(current->right);
    }
    q_delete_queue();
    return result;
}

int helper_max(int x, int y)
{
    if(x > y) return x;
    return y;
}

int height(TreeNode* root)
{
    if(root == NULL) return 0;
    return 1 + helper_max(height(root->left), height(root->right));    
}

void count(TreeNode* root, int* c)
{
    if(root == NULL) return;
    *c += 1;
    count(root->left);
    count(root->right);
}

int minimum(TreeNode* root)
{
    if(root == NULL)
    {
        return -1;
    }
    int result = INT_MAX;
    q_enqueue(root);
    while(!q_underflow())
    {
        TreeNode* current = q_dequeue();
        if(current->data < result) result = current->data;
        if(current->left) q_enqueue(current->left);
        if(current->right) q_enqueue(current->right);
    }
    q_delete_queue();
    return result;
}

int maximum(TreeNode* root)
{
    if(root == NULL)
    {
        return -1;
    }
    int result = INT_MIN;
    q_enqueue(root);
    while(!q_underflow())
    {
        TreeNode* current = q_dequeue();
        if(current->data > result) result = current->data;
        if(current->left) q_enqueue(current->left);
        if(current->right) q_enqueue(current->right);
    }
    q_delete_queue();
    return result;
}

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

void level_order(TreeNode* root)
{
    if(root == NULL) return;
    printf("The level order traversal of the tree is\n");
    q_enqueue(root);
    while(!q_underflow())
    {
        TreeNode* current = q_dequeue();
        printf("%d ", current->data);
        if(current->left) q_enqueue(current->left);
        if(current->right) q_enqueue(current->right);
    }
    q_delete_queue();
}

void runMenu()
{
    TreeNode* root = input_tree();
    level_order(root);
    do
    {
        printf("MENU\n");
        printf("0 - Exit the menu.\n");
        printf("1 - Check if the binary tree is empty.\n");
        printf("2 - Add a new node to the binary tree.\n");
        printf("3 - Remove a node from the binary tree.\n");
        printf("4 - Print the preorder traversal.\n");
        printf("5 - Print the inorder traversal.\n");
        printf("6 - Print the postorder traversal.\n");
        printf("7 - Search for a value in the tree.\n");
        printf("8 - Find the height of the tree.\n");
        printf("9 - Count the number of nodes in the binary tree.\n");
        printf("10 - Find the minimum value in the tree.\n");
        printf("11 - Find the maximum value in the tree.\n");
        int choice = 0;
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                if(empty()) printf("The tree is empty.\n");
                else printf("The tree is not empty.\n");
                break;
            case 2: 
                printf("Enter the value you want to insert.\n");
                int val = 0;
                scanf("%d", &val);
                insert(root, val);
                level_order(root);
                break;
            case 3:
                printf("Enter the value you want to remove.\n");
                int val = 0;
                scanf("%d", &val);
                root = delete(root, val);
                level_order(root);
                break;
            case 4:
                preorder_traversal(root);
                break;
            case 5:
                inorder_traversal(root);
                break;
            case 6:
                postorder_traversal(root);
                break;
            case 7:
                int s = 0;
                printf("Enter the value to search.\n");
                scanf("%d", &s);
                if(!search(root, s))
                    printf("Not found.\n");
                else
                    printf("The value was found in the tree.\n");
            case 8:
                printf("%d\n", height(root));
                break;
            case 9:
                int c = 0;
                count(root, &c);
                printf("%d\n", c);
                break;
            case 10:
                printf("%d\n", minimum(root));
                break;
            case 11:
                printf("%d\n", maximum(root));
                break;
        }
    } while(choice != 0);
}

int main()
{
    runMenu();
    return 0;
}