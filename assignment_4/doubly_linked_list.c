#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Node;

void printList(Node *head)
{
    if (head == NULL)
        return;

    Node *current = head;

    printf("Head to tail:\n");
    while (current->next != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("%d\n", current->data);

    printf("Tail to head:\n");
    while (current->prev != NULL)
    {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("%d\n", current->data);
}

void input(Node **head, int *k)
{
    int n = 0;
    printf("Enter the number of nodes you'd like to generate.\n");
    scanf("%d", &n);

    if (n < 1)
    {
        printf("That's an invalid input. Terminating the execution.\n");
        exit(0);
    }

    *head = NULL;
    Node *p = NULL;

    printf("Enter the elements of the doubly linked list.\n");
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        scanf("%d", &x);
        Node *newNode = calloc(1, sizeof(Node));
        newNode->data = x;
        newNode->prev = p;
        if (p != NULL)
            p->next = newNode;
        if (*head == NULL)
            *head = newNode;
        p = newNode;
    }

    printf("Enter the value of k.\n");
    scanf("%d", k);

    if (k < 0)
    {
        printf("That's an invalid input. Terminating the execution.\n");
        exit(0);
    }
}

void deleteList(Node *head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
}

Node *ordinaryReverse(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *current = head;
    Node *temp = NULL;

    while (current->next != NULL)
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }

    temp = current->next;
    current->next = current->prev;
    current->prev = temp;

    return current;
}

Node *reverse()
{
    // Input
    Node *head = NULL;
    int k = 0;
    input(&head, &k);

    // Taking care of edge cases
    if (head->next == NULL || k < 2)
        return head;

    // Finding the length of the Doubly Linked List
    int length = 0;
    Node *current = head;
    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    // Declaring variables
    int c = 1;
    Node *phead = NULL;
    Node *chead = NULL;
    current = head;
    Node *temp = NULL;
    Node *newHead = NULL;

    // Edge case
    if (length <= k)
    {
        return ordinaryReverse(head);
    }

    // Reverse elements in groups of k until the length that is a multiple of k
    while (c <= (length / k) * k)
    {
        temp = current->next;
        if (c % k == 1)
        {
            chead = current;
            current->next = NULL;
            current->prev = temp;
        }
        else if (c % k == 0)
        {
            if (newHead == NULL)
                newHead = current;
            current->next = current->prev;
            current->prev = phead;
            if (phead != NULL)
                phead->next = current;
            phead = chead;
        }
        else
        {
            current->next = current->prev;
            current->prev = temp;
        }
        c++;
        current = temp;
    }

    // Check if there are any left over nodes
    if (c == length + 1)
    {
        phead->next = NULL;
    }
    else
    {
        current->prev = NULL;
        temp = ordinaryReverse(current);
        phead->next = temp;
        if (temp != NULL)
        {
            temp->prev = phead;
        }
    }

    // Return the new head
    return newHead;
}

void sortOrdinary(Node *head, Node *nextHead)
{
    if(head == NULL || head->next == NULL)
    {
        return;
    }


    Node *current = head;
    while(current != nextHead)
    {
        Node *p = current;
        while(p->next != nextHead)
        {
            if(p->data > p->next->data)
            {
                int temp = p->data;
                p->data = p->next->data;
                p->next->data = p->data;
            }
            p = p->next;
        }
        current = current->next;
    }
}

Node *sort()
{
    // Input
    Node *head = NULL;
    int k = 0;
    input(&head, &k);
    
    // Taking care of edge cases
    if (head->next == NULL || k < 2)
        return head;

    // Finding the length of the Doubly Linked List
    int length = 0;
    Node *current = head;
    while (current != NULL)
    {
        length++;
        current = current->next;
    }
    
    if(k >= length)
    {
        sortOrdinary(head, NULL);
        return head;
    }

    int c = 1;
    current = head;
    Node *chead = head;

    while(c <= (length/k)*k)
    {
        if(c%k == 0)
        {
            sortOrdinary(chead, current->next);

        }
        else if(c%k == 1)
        {
            chead = current;
        }

        current = current->next;
        c++;
    }
    
    sortOrdinary(current, NULL);
    
    return head;
}

Node *rotate()
{

    // Input
    Node *head = NULL;
    int k = 0;
    input(&head, &k);

    // Edge case
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    // Find the length of the list
    Node *current = head;
    int length = 0;
    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    k = k % length; // In case k > length

    // Edge case
    if (k == 0)
    {
        return head;
    }

    // Traverse the list upto the point which becomes the new tail
    int c = 0;
    current = head;
    while (++c < length - k)
    {
        current = current->next;
    }

    Node *temp = current;
    current = current->next;
    temp->next = NULL; // Making the new tail's next null
    current->prev = NULL;
    
    Node *newHead = current;
    
    while (current->next != NULL)
        current = current->next;
    current->next = head;
    head->prev = current;
    return newHead;
}

void runMenu()
{
    printf("***MENU***\n");
    printf("1 - Reverse a doubly linked list in groups of k.\n");
    printf("2 - Sort a doubly linked list in groups of k.\n");
    printf("3 - Rotate a doubly linked list by k positions.\n");
    printf("0 - Exit the program.\n");
    printf("Enter your choice.\n");
    
    int choice = -1;
    scanf("\n%d", &choice);
    
    Node *head = NULL;

    switch(choice)
    {
        case 1:
            head = reverse();
            printList(head);
            deleteList(head);
            head = NULL;
            break;
        case 2:
            head = sort();
            printList(head);
            deleteList(head);
            head = NULL;
            break;
        case 3:
            head = rotate();
            printList(head);
            deleteList(head);
            head = NULL;
            break;
        default:
            printf("Goodbye!\n");
            exit(0);
    }
}

int main()
{
    runMenu();
    return 0;
}
