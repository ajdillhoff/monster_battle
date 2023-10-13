#ifndef QUEUE_UTILS_H_
#define QUEUE_UTILS_H_

typedef struct node Node;
struct node {
    void *data;
    Node *prev;
    Node *next;
};

void *dequeue(Node **head, Node **tail);
void enqueue(void *data, Node **head, Node **tail);

#endif // QUEUE_UTILS_H_
