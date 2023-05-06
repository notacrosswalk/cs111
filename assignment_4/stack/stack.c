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

void checkParentheses()
{
    char *str = input();
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            push(str[i]);
        }
        else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
        {
            if(str[i] == ')' && top == '(')
                pop();
            else if(str[i] == ']' && top == '[')
                pop();
            else if(str[i] == '}' && top == '{')
                pop();
            else
            {
                printf("Not Balanced.\n");
                exit(0);
            }
        }
        i++;
    }
    if(empty())
        printf("Balanced.\n");
    else
        printf("Not Balanced.\n");
    free(str);
    str = NULL;
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
    str = NULL;
}

void runMenu()
{
    printf("******MENU******\n");
    printf("1 - Check for balanced parentheses\n");
    printf("2 - Check if a string is palindrome\n");
    printf("Choose one of the options to continue.\n");
    char c = 0;
    scanf("\n%c", &c);
    switch(c)
    {
        case '1': 
            checkParentheses();
            freeStack();
            break;
        case '2': 
            isPalindrome(); 
            freeStack();
            break;
        default: printf("That's an invalid choice. The program execution" 
                        "will terminate now.\n");
                 exit(0);
    }
}

int main()
{
    runMenu();
    return 0;
}