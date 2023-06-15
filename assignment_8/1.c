#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct book_t
{
    long long ISBN;
    char *title;
    char *author;
    int quantity;
    struct book_t *left;
    struct book_t *right;
};

struct book_t *root = NULL;

struct book_t *insert_into_tree(struct book_t *parent, struct book_t *node)
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

void insert()
{
    long long isbn;
    char *title = NULL;
    char *author = NULL;
    int quantity = 0;

    printf("Enter the following details to insert a record.\n");

    printf("ISBN:\n");
    scanf("%lli", &isbn);

    printf("Title string length:\n");
    int l_title = 0;
    scanf("%d", &l_title);
    title = (char *)calloc(1, sizeof(char) * (l_title + 1));
    printf("Title:\n");
    scanf("\n%[^\n]s", title);

    printf("Author string length:\n");
    int l_author = 0;
    scanf("%d", &l_author);
    author = (char *)calloc(1, sizeof(char) * (l_author + 1));
    printf("Author:\n");
    scanf("\n%[^\n]s", author);

    printf("Quantity:\n");
    scanf("%d", &quantity);

    struct book_t *new_book = (struct book_t *)calloc(1, sizeof(struct book_t));
    new_book->ISBN = isbn;
    new_book->title = title;
    new_book->author = author;
    new_book->quantity = quantity;

    root = insert_into_tree(root, new_book);
}

struct book_t *search_bst(struct book_t *parent, long long *isbn)
{
    if (parent == NULL)
    {
        return NULL;
    }

    else if ((*isbn) < parent->ISBN)
    {
        return search_bst(parent->left, isbn);
    }

    else if ((*isbn) > parent->ISBN)
    {
        return search_bst(parent->right, isbn);
    }

    else
    {
        return parent;
    }
}

void search()
{

    long long isbn = 0;
    printf("Enter the ISBN of the book you'd like to search for.\n");
    scanf("%lli", &isbn);

    struct book_t *hit = search_bst(root, &isbn);

    if (!hit)
    {
        printf("That book wasn't found in the records!\n");
    }

    else
    {
        printf("Search Result:\n");
        printf("ISBN: %lli\nTitle: %s\nAuthor: %s\nQuantity Available: %d\n",
               hit->ISBN, hit->title, hit->author, hit->quantity);
    }
}

void display(struct book_t *node)
{
    if (node == NULL)
    {
        return;
    }

    display(node->left);

    printf("\nISBN: %lli\nTitle: %s\nAuthor: %s\nQuantity Available: %d\n",
           node->ISBN, node->title, node->author, node->quantity);

    display(node->right);
}

void update()
{
    printf("Enter the ISBN of the book whose quantity you'd like to update.\n");
    long long isbn = 0;
    scanf("%lli", &isbn);

    struct book_t *hit = search_bst(root, &isbn);

    if (!hit)
    {
        printf("A book with the given ISBN could not be found!\n");
    }

    else
    {
        printf("Current Quantity: %d\n", hit->quantity);

        printf("Enter the quantity you'd like to update it to:\n");
        scanf("%d", &(hit->quantity));

        printf("The book's quantity has been successfully updated to %d.\n",
               hit->quantity);
    }
}

struct book_t *find_min(struct book_t *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    while (node->left)
    {
        node = node->left;
    }

    return node;
}

struct book_t *delete_book(struct book_t *node, long long *isbn)
{
    if (node == NULL)
    {
        return NULL;
    }

    else if ((*isbn) < node->ISBN)
    {
        node->left = delete_book(node->left, isbn);
    }

    else if ((*isbn) > node->ISBN)
    {
        node->right = delete_book(node->right, isbn);
    }

    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            node = NULL;
        }

        else if (node->left == NULL)
        {
            struct book_t *temp = node->right;
            free(node);
            node = temp;
        }

        else if (node->right == NULL)
        {
            struct book_t *temp = node->left;
            free(node);
            node = temp;
        }

        else
        {
            struct book_t *temp = find_min(node->right);

            node->ISBN = temp->ISBN;
            node->quantity = temp->quantity;
            node->author = temp->author;
            node->quantity = temp->quantity;

            node->right = delete_book(node->right, &(temp->ISBN));
        }
    }

    return node;
}

void delete()
{
    printf("Enter the ISBN of the book you'd like to delete.\n");
    long long isbn = 0;
    scanf("%lli", &isbn);

    struct book_t *hit = search_bst(root, &isbn);

    if (!hit)
    {
        printf("Book not found!\n.");
    }
    else
    {
        delete_book(root, &isbn);
        printf("The record has been deleted!\n");
    }
}

void clear_memory(struct book_t *node)
{
    if (node == NULL)
        return;

    clear_memory(node->left);
    clear_memory(node->right);

    free(node->title);
    free(node->author);
    free(node);
}

void run_menu()
{
    int choice = 0;
    do
    {
        printf("\nMENU\n");
        printf("0 - Exit\n");
        printf("1 - Insert a book\n");
        printf("2 - Search for a book\n");
        printf("3 - Display all books\n");
        printf("4 - Update book quantity\n");
        printf("5 - Remove a book\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            insert();
            break;
        case 2:
            search();
            break;
        case 3:
            display(root);
            break;
        case 4:
            update();
            break;
        case 5:
            delete ();
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 0);

    clear_memory(root);
    root = NULL;
}

int main()
{
    run_menu();
    return 0;
}