#include <stdlib.h>

#include "edge/memory.h"

void *edge_malloc(size_t size) {
    void *result = malloc(size);
    if(result == NULL) {
        abort();
    }
    return result;
}

void *edge_alloc(unsigned int n, size_t size) {
    void *result = calloc(n, size);
    if(result == NULL) {
        abort();
    }
    return result;
}

void *edge_realloc(void *ptr, unsigned int n, size_t size) {
    void *result = realloc(ptr, n * size);
    if(result == NULL) {
        abort();
    }
    return result;
}

void edge_free(void *ptr) {
    free(ptr);
}