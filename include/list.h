#ifndef LIST_H
#define LIST_H

typedef struct {
    void *next;
    void *value;
} list_node;

list_node *list_new(void);
void list_dispose(list_node *node);
void list_dispose_full(list_node *node);

void list_push(list_node *node, void *value);
void list_erase(list_node *node, void *value);

#endif // !LIST_H