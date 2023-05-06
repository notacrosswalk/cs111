#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
} Node;

Node *head = NULL;

// TODO Free memory

void push(char x)
{
    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = x;
    newNode->next = head;
    head = newNode;
}

char top()
{
    if(head == NULL)
        return -1;
    return head->data;
}

char pop()
{
    if(head == NULL)
        return -1;
    char data = head->data;
    Node *temp = head;
    head = head->next;
    free(temp);
    temp = NULL;
    return data;
}

int empty()
{
    if(head == NULL)
        return 1;
    else
        return 0;
}

void freeStack()
{
    while(head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
}

char *input()
{
    int n = 0;
    printf("Enter the length of the string.\n");
    scanf("\n%d", &n);
    char *str = calloc(n + 1, sizeof(char));
    printf("Enter the string.\n");
    gets(str);
    return str;
}

void isPalindrome()
{
    char *str = input();
    int i = 0;
    while(str[i] != '\0')
    {
        push(str[i]);
        i++;
    }
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == top())
            pop();
        else 
        {
            printf("Not Palindrome.\n");
            exit(0);
        }
        i++;
    }
    // CHECK
    printf("Palindrome.\n");
    free(str);
    freeStack();
    str = NULL;
}

int main()
{
    isPalindrome();
    return 0;
}