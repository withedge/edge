#include <stdlib.h>

#include "edge/memory.h"

#include "edge/edge.h"

edge_t *edge_new() {
    edge_t *edge = edge_malloc(sizeof(edge_t));
    edge->errors = edge_list_error_new();

    return edge;
}

void edge_destroy(edge_t *edge) {
    edge_list_error_destroy(edge->errors);
    edge_free(edge);
}

edge_error_t *edge_error_new(int severity, const char *message) {
    edge_error_t *error = edge_malloc(sizeof(edge_error_t));
    error->severity = severity;
    error->message = message;

    return error;
}

void edge_list_error_grow(edge_list_error_t *list) {
    if((list->capacity - list->offset) <= 1) {
        list->capacity += 32;
        list->data = edge_realloc(list->data, list->capacity, sizeof(edge_error_t *));
    }
}

edge_list_error_t *edge_list_error_new() {
    edge_list_error_t *list = edge_malloc(sizeof(edge_list_error_t));
    list->offset = 0;
    list->capacity = 32;
    list->data = edge_alloc(list->capacity, sizeof(edge_error_t *));

    return list;
}

edge_error_t *edge_list_error_get(edge_list_error_t *list, size_t offset) {
    return list->data[offset];
}

void edge_list_error_push(edge_list_error_t *list, edge_error_t *item) {
    edge_list_error_grow(list);
    list->data[list->offset] = item;
    list->offset++;
}

void edge_list_error_remove(edge_list_error_t *list, size_t offset) {
    if(!(offset > (list->offset - 1))) {
        size_t position = offset;
        for(; position < list->offset - 1; position++) {
            list->data[position] = list->data[position + 1];
        }
        list->offset--;
    } 
}

void edge_list_error_destroy(edge_list_error_t *list) {
    size_t position = 0;
    for(; position < list->offset + 1; position++) {
        edge_free(list->data[position]);
        edge_list_error_remove(list, position);
    }
    edge_free(list->data);

    list->capacity = 32;
    list->offset = 0;
    edge_free(list);
}