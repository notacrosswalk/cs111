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

void i_push(char x)
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

char i_pop()
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

char i_top()
{
    if(head == NULL)
    {
        return -1;
    }
    return head->data;
}

bool i_empty()
{
    if(head == NULL)
    {
        return true;
    }
    return false;
}

void i_emptyStack()
{
    while(head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
}

bool i_isOperator(char c)
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

short i_precedence(char c)
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
    i_emptyStack();
    while(str[i] != '\0')
    {
        if(i_isOperator(str[i]))
        {
            while(!i_empty())
            {
                if(str[i] == ')')
                {
                    char c = i_pop();
                    if(c == '(')
                    {
                        break;
                    }
                    else
                    {
                        printf("%c", c);
                    }
                }
                else if(i_top() == '(')
                {
                    break;
                }
                else if(i_precedence(i_top()) >= i_precedence(str[i]))
                {
                    printf("%c", i_pop()); 
                }
                else
                {
                    break;
                }
            }
            if(str[i] != ')')
            {
                i_push(str[i]);
            }
        }
        else
        {
            printf("%c", str[i]);
        }
        i++;
    }

    while(!i_empty())
    {
        printf("%c ", i_pop());
    }

    printf("\n");
    i_emptyStack();
}

void infixToPrefix(char *str)
{
    i_emptyStack();

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
        if(i_isOperator(newStr[i]))
        {
            while(!i_empty())
            {
                if(newStr[i] == ')')
                {
                    char c = i_pop();
                    if(c == '(')
                    {
                        break;
                    }
                    else
                    {
                        result[j++] = c;
                    }
                }
                else if(i_top() == '(')
                {
                    break;
                }
                else if(i_precedence(i_top()) >= i_precedence(newStr[i]))
                // >= as discussed in the tutorial
                {
                    result[j++] = i_pop();
                }
                else
                {
                    break;
                }
            }
            if(newStr[i] != ')')
            {
                i_push(newStr[i]);
            }
        }
        else
        {
            result[j++] = newStr[i];
        }
        i++;
    }

    while(!i_empty())
    {
        result[j++] = i_pop();
    }
    
    result[j] = '\0';

    for(short i = 0; i < j/2; i++)
    {
        char temp = result[i];
        result[i] = result[j - i - 1];
        result[j - i - 1] = temp;
    }

    printf("%s\n", result);
    i_emptyStack();
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

int **st;
int top;
int *front;
int *rear;
int *size;
int n;
int k;
int min_index;
int max_index;

void ii_print_stack()
{
    printf("Magic Stack:\n");
    for (int i = top; i >= 0; i--)
    {
        if (front[i] == -1)
        {
            continue;
        }
        printf("Block index %d: ", i);
        if (rear[i] < front[i])
        {
            for (int j = front[i]; j <= n; j++)
            {
                printf("%d ", st[i][j]);
            }
            for (int j = 0; j <= rear[i]; j++)
            {
                printf("%d ", st[i][j]);
            }
        }
        else
        {
            for (int j = front[i]; j <= rear[i]; j++)
            {
                printf("%d ", st[i][j]);
            }
        }
        printf("\n");
    }
}

void ii_generate_stack()
{
    st = (int **)calloc(n, sizeof(int *));
    if (st == NULL)
    {
        printf("Memory couldn't be allocated for the magic stack.\n");
        exit(0);
    }
    for (int i = 0; i < n; i++)
    {
        st[i] = (int *)calloc(k, sizeof(int));
    }
    front = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        front[i] = -1;
    }
    rear = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        rear[i] = -1;
    }
    size = (int *)calloc(n, sizeof(int));
}

void ii_free_stack()
{
    for (int i = 0; i < n; i++)
    {
        free(st[i]);
        st[i] = NULL;
    }
    free(st);
    st = NULL;
    free(front);
    free(rear);
    front = NULL;
    rear = NULL;
}

void ii_sort()
{
    min_index = 0;
    max_index = 0;
    for (int i = 0; i < n; i++)
    {
        if (size[i] < size[min_index])
        {
            min_index = i;
        }
        if (size[i] > size[max_index])
        {
            max_index = i;
        }
    }
    for (int i = top; i >= 0; i--)
    {
        int largest_index = i;
        for (int j = i; j >= 0; j--)
        {
            if (front[j] != -1)
            {
                if (st[j][front[j]] > st[largest_index][front[largest_index]])
                {
                    largest_index = j;
                }
            }
        }
        int *temp = st[largest_index];
        st[largest_index] = st[i];
        st[i] = temp;
        int temp_front = front[largest_index];
        front[largest_index] = front[i];
        front[i] = temp_front;
        int temp_rear = rear[largest_index];
        rear[largest_index] = rear[i];
        rear[i] = temp_rear;
        int temp_size = size[largest_index];
        size[largest_index] = size[i];
        size[i] = temp_size;
    }
}

void ii_push(int x)
{
    if (size[min_index] == k)
    {
        printf("Overflow!\n");
        return;
    }
    if (size[min_index] == 0)
    {
        front[min_index] = 0;
        top = min_index;
    }
    int r = rear[min_index];
    if (r == k - 1)
        r = 0;
    else
        r += 1;
    st[min_index][r] = x;
    rear[min_index] = r;
    size[min_index] += 1;
    ii_sort();
}

int ii_pop()
{
    if (size[max_index] <= 1)
    {
        printf("Underflow!\n");
        return -1;
    }
    int f = front[max_index];
    int data = st[max_index][f];
    if (f == k - 1)
        f = 0;
    else
        f += 1;
    front[max_index] = f;
    size[max_index] -= 1;
    ii_sort();
    return data;
}

bool ii_search()
{
    for (int i = top; i >= 0; i--)
    {
        if (size[i] != 1)
            return false;
    }
    return true;
}

void ii_input()
{
    printf("Enter n:\n");
    scanf("%d", &n);
    printf("Enter k:\n");
    scanf("%d", &k);
}

void runMagicStack()
{
    ii_input();
    ii_generate_stack();
    int c = 1;
    do
    {
        printf("------------\n");
        printf("0 - Exit.\n");
        printf("1 - Push a value.\n");
        printf("2 - Pop a value.\n");
        printf("Enter your choice.\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter a value to push.\n");
            int x;
            scanf("%d", &x);
            ii_push(x);
            ii_print_stack();
            break;
        case 2:
            printf("The popped value is %d.\n", ii_pop());
            ii_print_stack();
            break;
        default:
            c = 0;
            break;
        }
    } while (c);
    ii_free_stack();
}

void runMenu()
{
    printf("MENU\n");
    printf("1 - Infix Conversions\n");
    printf("2 - Magic Stack\n");
    printf("Enter your choice.\n");
    int choice = 0;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1: runInfix(); break;
        case 2: runMagicStack(); break;
        default: printf("Invalid choice!\n"); break;
    }
}


int main()
{
    runMenu();
    return 0;
}