#include <stdlib.h>
#include <stdio.h>

#include "edge/memory.h"
#include "edge/lexer.h"
#include "edge/token.h"

int main() {
    size_t position = 0;

    edge_lexer_t *lexer = edge_lexer_new("'Hello World!'");
    edge_lexer_tokenize(lexer);
    
    for(; position < lexer->tokens->offset; position++) {
        printf("%d | %s\n", edge_list_token_get(lexer->tokens, position)->type, edge_list_token_get(lexer->tokens, position)->literal);
    }

    edge_lexer_destroy(lexer);
    return 0;
}