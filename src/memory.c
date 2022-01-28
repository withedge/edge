#include <stdlib.h>

#include "edge/memory.h"

void *edge_malloc(size_t a_size) {
    void *v_result = malloc(a_size);
    if(v_result == NULL) {
        abort();
    }

    return v_result;
}

void *edge_alloc(unsigned int a_n, size_t a_size) {
    void *v_result = calloc(a_n, a_size);
    if(v_result == NULL) {
        abort();
    }

    return v_result;
}

void *edge_realloc(void *a_ptr, unsigned int a_n, size_t a_size) {
    void *v_result = realloc(a_ptr, a_n * a_size);
    if(v_result == NULL) {
        abort();
    }

    return v_result;
}

void edge_free(void *a_ptr) {
    free(a_ptr);
}