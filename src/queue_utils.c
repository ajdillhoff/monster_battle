#include <stdio.h>
#include <stdlib.h>

#include "queue_utils.h"

void *dequeue(Node **head, Node **tail) {
    if (*head == NULL) {
        return NULL;
    }

    void *val = (*tail)->data;

    if (*head == *tail) {
        free(*tail);
        *head = NULL;
        *tail = NULL;
    } else {
        Node *prev = (*tail)->prev;
        prev->next = NULL;
        free(*tail);
        *tail = prev;
    }

    return val;
}

void enqueue(void *data, Node **head, Node **tail) {
    Node *new_node = calloc(1, sizeof(Node));
    new_node->data = data;
    new_node->next = *head;

    if (*head != NULL) {
        (*head)->prev = new_node;
    } else {
        *tail = new_node;
    }

    *head = new_node;
}
