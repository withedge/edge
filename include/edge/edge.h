#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>

typedef struct {
    int severity;
    const char *message;
} edge_error_t;

edge_error_t *edge_error_new(int, const char *);

typedef struct {
    edge_error_t **data;
    size_t capacity;
    size_t offset;
} edge_list_error_t;

edge_list_error_t *edge_list_error_new();
void edge_list_error_destroy(edge_list_error_t *);

edge_error_t *edge_list_error_get(edge_list_error_t *, size_t);
void edge_list_error_push(edge_list_error_t *, edge_error_t *);
void edge_list_error_remove(edge_list_error_t *, size_t);

typedef struct {
    edge_list_error_t *errors;
} edge_t;

edge_t *edge_new();
void edge_destroy(edge_t *);

#endif