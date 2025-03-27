#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * new_list = (List *)malloc(sizeof(List));
    assert(new_list != NULL);
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->current = NULL;

    return new_list;

}

void * firstList(List * list) {
    if (list->head != NULL) {
        list->current = list->head;
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL) {
        list->current = list->current->next;
        if (list->current != NULL) {
            return list->current->data;
        }
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL) {
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL) {
        list->current = list->current->prev;
        if (list->current != NULL) {
            return list->current->data;
        }
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * new_node = createNode(data);
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->current = new_node;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * new_node = createNode(data);
    if (list->current == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->current->next;
        new_node->prev = list->current;
        if (list->current->next != NULL) {
            list->current->next->prev = new_node;
        } else {
            list->tail = new_node;
        }
        list->current->next = new_node;
    }
    list->current = new_node;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current != NULL) {
        return NULL;
    }
    void * node_to_delete = list->current;
    void * left = NULL;
    void * right = NULL;

    if (node_to_delete->left != NULL) {
        left = node_to_delete->prev;
    }      

    if (node_to_delete->next != NULL) {
        right = node_to_delete->next;
    }
    // punteros void a null no hacen problema no?      
    left->next = right;
    right->prev = left;
     
    free(node_to_delete);
    list->current = NULL;
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}