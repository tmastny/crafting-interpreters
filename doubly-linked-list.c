#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  char* data;
  struct Node *next;
  struct Node *prev;
} Node;

Node* Node_init(char* data, Node* next, Node* prev) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->next = next;
  node->prev = prev;

  return node;
}

typedef struct LinkedList {
  Node *head;
  Node *tail;
} LinkedList;

LinkedList* LinkedList_init() {
  LinkedList *ll = malloc(sizeof(LinkedList));
  Node *head = Node_init(NULL, NULL, NULL);
  Node *tail = Node_init(NULL, NULL, head);

  head->next = tail;

  ll->head = head;
  ll->tail = tail;

  return ll;
}

void LinkedList_append(LinkedList *ll, char* data) {
  Node *last = ll->tail->prev;
  Node *new = Node_init(data, ll->tail, last);

  last->next = new;
  ll->tail->prev = new;
}

int main(int argc, char* argv[]) {

  LinkedList *ll = LinkedList_init();

  for (int i = 1; i < argc; i++) {
    LinkedList_append(ll, argv[i]);
  }

  printf("Printing front to back:\n");
  Node *curr = ll->head->next;
  while (curr->data != NULL) {
    printf(curr->data);
    printf("\n");
    curr = curr->next;
  }

  printf("\nPrinting back to front:\n");
  curr = ll->tail->prev;
  while (curr->data != NULL) {
    printf(curr->data);
    printf("\n");

    curr = curr->prev;
  }

  return 0;
}
