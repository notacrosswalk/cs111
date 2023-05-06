#include <stdio.h>
#include <stdlib.h>

int top = -1;

char *generateStack(int size)
{
    char *stack = malloc(size*sizeof(char));
    top = -1;
    return stack;
}

void push(char *stack, char x)
{
    stack[++top] = x;
}

char topOfStack(char *stack)
{
    if(top == -1)
        return -1;
    return stack[top];
}

char pop(char *stack)
{
    if(top == -1)
        return -1;
    char data = stack[top--];
    return data;
}

int empty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

char *input(int *size)
{
    int n = 0;
    printf("Enter the length of the string.\n");
    scanf("\n%d", &n);
    char *str = calloc(n + 1, sizeof(char));
    printf("Enter the string.\n");
    gets(str);
    *size = n;
    return str;
}

void checkParentheses()
{
    int size = 0;
    char *str = input(&size);
    int top = -1;
    char *stack = generateStack(size);
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            push(stack, str[i]);
        }
        else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
        {
            if(str[i] == ')' && top == '(')
                pop(stack);
            else if(str[i] == ']' && top == '[')
                pop(stack);
            else if(str[i] == '}' && top == '{')
                pop(stack);
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

int main()
{
    checkParentheses();
    return 0;
}