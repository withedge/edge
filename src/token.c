#include <stdlib.h>

#include "edge/memory.h"

#include "edge/token.h"

void edge_list_token_grow(edge_list_token_t *list) {
    if((list->capacity - list->offset) <= 1) {
        list->capacity += 32;
        list->data = edge_realloc(list->data, list->capacity, sizeof(edge_token_t *));
    }
}

edge_list_token_t *edge_list_token_new() {
    edge_list_token_t *list = edge_malloc(sizeof(edge_list_token_t));
    list->offset = (size_t) 0;
    list->capacity = (size_t) 32;
    list->data = edge_alloc(list->capacity, sizeof(edge_token_t *));

    return list;
}

edge_token_t *edge_list_token_get(edge_list_token_t *list, size_t offset) {
    return list->data[offset];
}

void edge_list_token_push(edge_list_token_t *list, edge_token_t *item) {
    edge_list_token_grow(list);
    list->data[list->offset] = item;
    list->offset++;
}

void edge_list_token_remove(edge_list_token_t *list, size_t offset) {
    if(!(offset > (list->offset - 1))) {
        size_t position = offset;
        for(; position < list->offset - 1; position++) {
            list->data[position] = list->data[position + 1];
        }
        list->offset--;
    } 
}

void edge_list_token_destroy(edge_list_token_t *list) {
    size_t position = 0;
    for(; position < list->offset + 1; position++) {
        edge_free(list->data[position]);
        edge_list_token_remove(list, position);
    }
    edge_free(list->data);

    list->capacity = 32;
    list->offset = 0;
    edge_free(list);
}