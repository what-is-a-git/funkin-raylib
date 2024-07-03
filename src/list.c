#include "list.h"

#include <stdlib.h>

list_node *list_new(void) {
    list_node *node = (list_node*) malloc(sizeof(list_node));
    node->next = NULL;
    node->value = NULL;
    return node;
}

void list_dispose(list_node *node) {
    if (node->next == NULL) {
        free(node);
        return;
    }

    list_node *last = node;
    while (last->next != NULL) {
        list_node *about_to_free = last;
        last = last->next;
        free(about_to_free);
    }

    free(last);
}

void list_dispose_full(list_node *node) {
    if (node->next == NULL) {
        free(node->value);
        free(node);
        return;
    }

    list_node *last = node;
    while (last->next != NULL) {
        list_node *about_to_free = last;
        last = last->next;
        free(about_to_free->value);
        free(about_to_free);
    }

    free(last->value);
    free(last);
}

void list_push(list_node *node, void *value) {
    list_node *last = node;
    while (last->next != NULL) {
        last = last->next;
    }

    list_node *pushed = list_new();
    pushed->value = value;
    last->next = pushed;
}

void list_erase(list_node *node, void *value) {
    if (node->value == value) {
        if (node->next != NULL) {
            // copy values of next for this node
            list_node *raw_next = node->next;
            node->value = ((list_node*)node->next)->value;
            node->next = ((list_node*)node->next)->next;
            list_dispose(raw_next);
        } else {
            node->value = NULL;
            return;
        }
    }

    list_node *last = NULL;
    list_node *iter = node;

    while (iter->next != NULL) {
        if (iter->value == value) {
            last->next = iter->next;
            list_dispose(iter);
            iter = last->next;
            continue;
        }

        last = iter;
        iter = iter->next;
    }
}