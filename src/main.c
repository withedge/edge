#include <stdlib.h>
#include <stdio.h>

#include "edge/memory.h"
#include "edge/lexer.h"
#include "edge/token.h"

#include "edge/edge.h"

int main() {
    size_t position = 0;

    edge_t *edge = edge_new();

    edge_lexer_t *lexer = edge_lexer_new(edge, "100_000'Hello World!'100_000");
    edge_lexer_tokenize(lexer);

    if(edge->errors->offset > 0) {
        for(; position < edge->errors->offset; position++) {
            printf("error[%d]: %s\n", edge_list_error_get(edge->errors, position)->severity, edge_list_error_get(edge->errors, position)->message);
        }
    } else {
        for(; position < lexer->tokens->offset; position++) {
            printf("token[%d]: %s\n", edge_list_token_get(lexer->tokens, position)->type, edge_list_token_get(lexer->tokens, position)->literal);
        }
    }

    edge_lexer_destroy(lexer);
    edge_destroy(edge);
    return 0;
}