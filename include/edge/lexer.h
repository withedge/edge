#ifndef EDGE_LEXER_H
#define EDGE_LEXER_H

#include <stdlib.h>

#include "edge/token.h"

typedef struct {
    const char *source;
    size_t offset;
} edge_lexer_t;

edge_lexer_t *edge_lexer_new(const char *);
void edge_lexer_destroy(edge_lexer_t *);

edge_token_t *edge_lexer_go_next(edge_lexer_t *);

#endif