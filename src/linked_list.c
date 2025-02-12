#include "../include/linked_list.h"
#include <stdlib.h>
#include <string.h>

Node* create_node(const char *file_path) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return NULL;

    new_node->file_path = strdup(file_path);
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, const char *file_path) {
    Node *new_node = create_node(file_path);
    if (!new_node) return;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void free_list(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->file_path);
        free(temp);
    }
}
