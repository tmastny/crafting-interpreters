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

int main(int argc, char* argv[]) {

  Node *head = Node_init(NULL, NULL, NULL);
  Node *tail = head;

  for (int i = 1; i < argc; i++) {
    Node *new = Node_init(argv[i], NULL, tail);
    tail->next = new;
    tail = new;
  }

  Node *endtail = malloc(sizeof(Node));
  endtail->data = NULL;
  endtail->next = NULL;
  endtail->prev = tail;
  tail->next = endtail;
  tail = endtail;

  printf("Printing front to back:\n");
  Node *curr = head->next;
  while (curr->data != NULL) {
    printf(curr->data);
    printf("\n");
    curr = curr->next;
  }

  printf("\nPrinting back to front:\n");
  curr = tail->prev;
  while (curr->data != NULL) {
    printf(curr->data);
    printf("\n");

    curr = curr->prev;
  }


  return 0;
}
