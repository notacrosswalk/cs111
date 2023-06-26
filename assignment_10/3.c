#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node_t
{
    int data;
    struct node_t* left;
    struct node_t* right;
};

struct node_t* insert_into_tree(struct node_t *parent, struct node_t * node)
{
    if (parent == NULL)
    {
        parent = node;
    }

    else if (node->ISBN < parent->ISBN)
    {
        parent->left = insert_into_tree(parent->left, node);
    }

    else if (node->ISBN > parent->ISBN)
    {
        parent->right = insert_into_tree(parent->right, node);
    }

    return parent;
}

struct node_t* create_tree()
{
    printf("Number of elements:\n");
    int n;
    scanf("%d", &n);

    printf("Enter the elements.\n");
    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    struct node_t* root = NULL;

    for(int i = 0; i < n; i++)
    {
        struct node_t* new_node = (struct node_t*) 
                                  calloc(1, sizeof(struct node_t));
        new_node->data = arr[i];
        root = insert_into_tree(root, new_node);
    }

    return root;
}

void f(struct node_t* root, int k1, int k2)
{
    if(root == NULL)
        return;
    
    if(root->data >= k1 && root->data <= k2)
    {
        printf("%d\n", root->data);
        f(root->left, k1, k2);
        f(root->right, k1, k2);
    }
}

int main()
{
    struct node_t* root = create_tree();
    
    printf("Enter K1.\n");
    int k1;
    scanf("%d", &k1);

    printf("Enter K2.\n");
    int k2;
    scanf("%d", &k2);

    f(root, k1, k2);
    return 0;
}