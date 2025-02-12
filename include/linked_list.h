#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    char *file_path;
    struct Node *next;
} Node;

Node* create_node(const char *file_path);
void append_node(Node **head, const char *file_path);
void free_list(Node *head);

#endif