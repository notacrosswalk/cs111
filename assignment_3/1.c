#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} Node;

Node *newNode(int x) {
  Node *p = (Node *)calloc(1, sizeof(Node));
  p->data = x;
  return p;
}

void printList(Node *head) {
  if (head == NULL)
    return;
  while (head->next != NULL) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("%d\n", head->data);
}

Node *createList(int *arr, int n) {
  Node *head = NULL;
  Node *current = head;
  for (int i = 0; i < n; i++) {
    if (head == NULL) {
      head = newNode(arr[i]);
      current = head;
    } else {
      current->next = newNode(arr[i]);
      current = current->next;
    }
  }
  return head;
}

Node *userInput() {
  printf("Enter the number of nodes you'd like to generate.\n");
  int n = 0;
  scanf("%d", &n);
  if (n <= 0) {
    printf("That's an invalid value. Exiting the program.\n");
    exit(0);
  }
  int arr[n];
  printf("Enter the values to generate the linked list.\n");
  for (int i = 0; i < n; i++)
    scanf("%d", &arr[i]);
  printf("\nThe generated linked list is\n");
  Node *head = createList(arr, n);
  printList(head);
  return head;
}

Node *reverseList(Node *head) {
  if (head == NULL || head->next == NULL)
    return head;
  Node *previousNode = NULL;
  Node *nextNode = head->next;
  while (head != NULL) {
    head->next = previousNode;
    previousNode = head;
    head = nextNode;
    if (head != NULL)
      nextNode = head->next;
  }
  return previousNode;
}

void deleteList(Node *head) {
  if (head == NULL)
    return;
  Node *temp = NULL;
  while (head != NULL) {
    temp = head->next;
    free(head);
    head = temp;
  }
}

Node *reverseAtMiddle(Node *head) {
  Node *fast = head;
  Node *slow = head;
  Node *pslow = NULL;
  if (fast == NULL)
    return fast;
  while (fast->next != NULL) {
    fast = fast->next->next;
    pslow = slow;
    slow = slow->next;
    if (fast == NULL)
      break;
  }
  if (pslow == NULL)
    return slow;
  pslow->next = reverseList(slow);
  return pslow->next;
}

int isPalindrome(Node *head) {
  Node *a = head;
  Node *b = reverseAtMiddle(head);
  Node *c = b;
  while (a != NULL && b != NULL && a != c) {
    if (a->data != b->data)
      return 0;
    a = a->next;
    b = b->next;
  }
  return 1;
}

Node *findMiddle(Node *head) {
  Node *fast = head;
  Node *slow = head;
  if (fast == NULL)
    return fast;
  while (fast->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == NULL)
      break;
  }
  return slow;
}

void generatePause() {
  char c = 0;
  printf("Press any key (but not Enter/Return) to continue.\n");
  scanf("\n%c", &c);
}

void removeDuplicates(Node *head) {
  if (head == NULL || head->next == NULL)
    return;
  Node *current = head;
  Node *p = NULL;
  while (current != NULL) {
    p = current;
    while (p->next != NULL) {
      if (p->next->data == current->data)
        p->next = p->next->next;
      else
        p = p->next;
      if (p == NULL)
        break;
    }
    current = current->next;
  }
}

void runMenu() {
  int condition = 1;
  while (condition != 0) {
    printf("MENU\n");
    printf("(a) Reverse the linked list.\n");
    printf("(b) Remove duplicates in the linked list.\n");
    printf("(c) Find the middle element in the linked list.\n");
    printf("(d) Check if the given linked list is a palindrome.\n");
    printf("0 - exit");
    printf("\nPick an option.\n");
    char c = '\0';
    Node *head = NULL;
    scanf("\n%c", &c);
    switch (c) {
    case 'A':
    case 'a':
      head = userInput();
      printf("The reversed linked list is\n");
      printList(reverseList(head));
      generatePause();
      break;
    case 'B':
    case 'b':
      head = userInput();
      removeDuplicates(head);
      printf("The linked list after removing duplicates is\n");
      printList(head);
      generatePause();
      break;
    case 'C':
    case 'c':
      head = userInput();
      printf("%d is the middle element in the linked list.\n",
             (findMiddle(head))->data);
      generatePause();
      break;
    case 'D':
    case 'd':
      head = userInput();
      if (isPalindrome(head) == 0)
        printf("It is not a palindrome.\n");
      else
        printf("It is a palindrome.\n");
      generatePause();
      break;
    case '0':
      condition = 0;
      break;
    default:
      printf("That's an invalid choice. Terminating the execution of the "
             "program.\n");
      exit(0);
    }
    printf("\e[1;1H\e[2J"); // RegEx to clear the screen
  }
}

int main() {
  runMenu();
  return 0;
}