#include <stdlib.h>
#include <stdio.h>

#include "edge/memory.h"
#include "edge/lexer.h"
#include "edge/token.h"

int main() {
    edge_lexer_t *lexer = edge_lexer_new("+-*/%");

    edge_token_t *current = edge_lexer_go_next(lexer);

    while(1) {
        if(current->type == _eof) {
            break;
        }
        current = edge_lexer_go_next(lexer);
    }

    edge_free(current);

    edge_lexer_destroy(lexer);

    return 0;
}