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

bool search_helper(struct node_t* root, int val)
{
    if(root == NULL)
        return false;
    else if(root->data == val)
        return true;
    else if(root->data < val)
        return search(root->left, val);
    else
        return search(root->right, val);
}

bool search(struct node_t* root_1, struct node_t* root_2)
{
    if(root_1 == NULL)
        return true;
    
    else if(!search_helper(root_2, root_1->data))
        return false;

    else
        return search(root_1->left, root_2) && search(root_1->right, root_2);
}

int main()
{
    struct node_t* root_1 = create_tree();
    struct node_t* root_2 = create_tree();
    if(search(root_1, root_2))
        printf("True.\n");
    else
        printf("False.\n");
    return 0;
}