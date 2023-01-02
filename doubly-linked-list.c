#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void LinkedList_delete(LinkedList *ll, char* data) {
  Node *curr = ll->head->next;

  while (strcmp(curr->data, data) != 0) {
    if (curr->data == NULL) {
      return;
    }
    curr = curr->next;
  }

  Node *prev = curr->prev;
  prev->next = curr->next;

  Node *next = curr->next;
  next->prev = curr->prev;

  free(curr);
}

void LinkedList_printnext(LinkedList *ll) {
  printf("Printing front to back:\n");
  Node *curr = ll->head->next;
  while (curr->data != NULL) {
    printf(curr->data);
    printf("\n");
    curr = curr->next;
  }
}


void LinkedList_printprev(LinkedList *ll) {
  printf("\nPrinting back to front:\n");
  Node *curr = ll->tail->prev;
  while (curr->data != NULL) {
    printf(curr->data);
    printf("\n");

    curr = curr->prev;
  }
}

int main(int argc, char* argv[]) {

  LinkedList *ll = LinkedList_init();

  int i = 1;
  while (strcmp(argv[i], ",") != 0) {
    LinkedList_append(ll, argv[i]);
    i++;
  }

  LinkedList_printnext(ll);
  LinkedList_printprev(ll);

  LinkedList_delete(ll, argv[i + 1]);

  printf("\n\nDeleted element:\n");
  LinkedList_printnext(ll);

  return 0;
}
