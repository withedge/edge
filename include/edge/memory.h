#ifndef EDGE_MEMORY_H
#define EDGE_MEMORY_H

#include <stdlib.h>

void *edge_malloc(size_t);
void *edge_alloc(unsigned int, size_t);
void *edge_realloc(void *, unsigned int, size_t);
void edge_free(void *);

#endif