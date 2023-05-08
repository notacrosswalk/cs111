#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/***
 * The infix converter functions were written with only the binary operators
 * (+, - , *, /, ^) and the parentheses '(' and ')' in mind.
 * Since the associativity of these operators is left to right, the exceptional
 * case for operators with right to left associativity has not been considered.
*/

typedef struct node
{
    char data;
    struct node *next;
} Node;

Node *head;

void push(char x)
{
    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = x;
    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

char pop()
{
    if(head == NULL)
    {
        return -1;
    }
    char data = head->data;
    Node *temp = head;
    head = head->next;
    free(temp);
    temp = NULL;
    return data;
}

char top()
{
    if(head == NULL)
    {
        return -1;
    }
    return head->data;
}

bool empty()
{
    if(head == NULL)
    {
        return true;
    }
    return false;
}

void emptyStack()
{
    while(head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
}

bool isOperator(char c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')': 
            return true;
            break;
        default:
            return false;
    }   
}

short precedence(char c)
{
    switch(c)
    {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
}

void infixToPostfix(char *str)
{
    int i = 0;
    emptyStack();
    while(str[i] != '\0')
    {
        if(isOperator(str[i]))
        {
            while(!empty())
            {
                if(str[i] == ')')
                {
                    char c = pop();
                    if(c == '(')
                    {
                        break;
                    }
                    else
                    {
                        printf("%c", c);
                    }
                }
                else if(top() == '(')
                {
                    break;
                }
                else if(precedence(top()) >= precedence(str[i]))
                {
                    printf("%c", pop()); 
                }
                else
                {
                    break;
                }
            }
            if(str[i] != ')')
            {
                push(str[i]);
            }
        }
        else
        {
            printf("%c", str[i]);
        }
        i++;
    }

    while(!empty())
    {
        printf("%c ", pop());
    }

    printf("\n");
    emptyStack();
}

void infixToPrefix(char *str)
{
    emptyStack();

    short length = strlen(str);

    char newStr[length+1];
    
    short i = 0;
    short j = length - 1;
    for(i = 0; i < length; i++)
    {
        if(str[i] == '(')
        {
            newStr[j--] = ')';
        }
        else if(str[i] == ')')
        {
            newStr[j--] = '(';
        }
        else
        {
            newStr[j--] = str[i];
        }
    }
    newStr[length] = '\0';

    char result[length + 1];

    i = 0;
    j = 0;



    while(newStr[i] != '\0')
    {
        if(isOperator(newStr[i]))
        {
            while(!empty())
            {
                if(newStr[i] == ')')
                {
                    char c = pop();
                    if(c == '(')
                    {
                        break;
                    }
                    else
                    {
                        result[j++] = c;
                    }
                }
                else if(top() == '(')
                {
                    break;
                }
                else if(precedence(top()) >= precedence(newStr[i]))
                // >= as discussed in the tutorial
                {
                    result[j++] = pop();
                }
                else
                {
                    break;
                }
            }
            if(newStr[i] != ')')
            {
                push(newStr[i]);
            }
        }
        else
        {
            result[j++] = newStr[i];
        }
        i++;
    }

    while(!empty())
    {
        result[j++] = pop();
    }
    
    result[j] = '\0';

    for(short i = 0; i < j/2; i++)
    {
        char temp = result[i];
        result[i] = result[j - i - 1];
        result[j - i - 1] = temp;
    }

    printf("%s\n", result);
    emptyStack();
}

void runInfix()
{
    char str[] = "8*(5^4+2)-6^2/(9*3)";
    printf("The infix expression is\n");
    printf("%s\n", str);

    printf("The postfix expression is\n");
    infixToPostfix(str);

    printf("The prefix expression is\n");
    infixToPrefix(str);
}

void runMenu()
{
    printf("MENU\n");
    printf("1 - Infix Conversions\n");
    printf("2 - Magic Stack\n");
    printf("0 - Exit\n");
    printf("Enter your choice.\n");

    short choice = -1;
    scanf("%hi", &choice);

    switch(choice)
    {
        case 1: 
            runInfix();
            break;
        case 2:
            // runMagicStack();
            break;
        default:
            printf("Goodbye!\n");
            break;
    }
}

int main()
{
    runMenu();
    return 0;
}