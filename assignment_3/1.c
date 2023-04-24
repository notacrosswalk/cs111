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
  printf("Enter the values to generate the Linked List.\n");
  for (int i = 0; i < n; i++)
    scanf("%d", &arr[i]);
  return createList(arr, n);
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

int main() {
  Node *head = userInput();
  printList(head);
  // printf("%d\n", findMiddle(head)->data);
  // printList(reverseList(head));
  // printf("%d\n", isPalindrome(head));
  deleteList(head);
  return 0;
}