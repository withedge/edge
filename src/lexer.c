#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

#include "edge/memory.h"
#include "edge/util.h"
#include "edge/token.h"

#include "edge/lexer.h"

edge_lexer_t *edge_lexer_new(const char *source) {
    edge_lexer_t *result = edge_malloc(sizeof(edge_lexer_t));
    result->source = source;
    result->offset = (size_t) 0;

    return result;
}

bool edge_lexer_is_whitespace(char _) {
    return ((_ == ' ') || (_ == '\r') || (_ == '\t') || (_ == '\n'));
}

bool edge_lexer_is_number(char _, bool accept) {
    return (((_ >= 48) && (_ <= 57)) || (accept && ((_ == '.') || (_ == '_'))));
}

bool edge_lexer_is_identifier(char _, bool accept) {
    return (((_ >= 97) && (_ <= 122)) || ((_ >= 65) && (_ <= 90)) || _ == '_' || (accept && (edge_lexer_is_number(_, false))));
}

char edge_lexer_peek_current(edge_lexer_t* lexer) {
    return (lexer->offset >= strlen(lexer->source)) ? '\0' : lexer->source[lexer->offset];
}

char edge_lexer_peek_next(edge_lexer_t* lexer) {
    return ((lexer->offset + 1) >= strlen(lexer->source)) ? '\0' : lexer->source[lexer->offset + 1];
}

edge_token_t *edge_lexer_tokenize_operator(edge_lexer_t* lexer) {
    edge_token_t *result = edge_malloc(sizeof(edge_token_t));
    char current = edge_lexer_peek_current(lexer);
    size_t begin = lexer->offset;
    lexer->offset++;

    if(current == '+') {
        if(edge_lexer_peek_current(lexer) == '+') {
            lexer->offset++;
            result->type = _increment;
            result->literal = "++";
        } else if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _add_assign;
            result->literal = "+=";
        } else {
            result->type = _add;
            result->literal = "+";
        }
    }
    else if(current == '-') {
        if(edge_lexer_peek_current(lexer) == '-') {
            lexer->offset++;
            result->type = _decrement;
            result->literal = "--";
        } else if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _sub_assign;
            result->literal = "-=";
        }
        else {
            result->type = _sub;
            result->literal = "-";
        }
    }
    else if(current == '*') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _mult_assign;
            result->literal = "*=";
        } else {
            result->type = _mult;
            result->literal = "*";
        }
    }
    else if(current == '/') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _div_assign;
            result->literal = "/=";
        } else {
            result->type = _div;
            result->literal = "/";
        }
    }
    else if(current == '%') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _mod_assign;
            result->literal = "%=";
        } else {
            result->type = _mod;
            result->literal = "%";
        }
    }
    else if(current == '=') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _equal;
            result->literal = "==";
        } else {
            result->type = _assign;
            result->literal = "=";
        }
    }
    else if(current == '!') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _bang_equal;
            result->literal = "!=";
        } else {
            result->type = _bang;
            result->literal = "!";
        }
    }
    else if(current == '>') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _greater_equal;
            result->literal = ">=";
        } else {
            result->type = _greater;
            result->literal = ">";
        }
    }
    else if(current == '<') {
        if(edge_lexer_peek_current(lexer) == '=') {
            lexer->offset++;
            result->type = _less_equal;
            result->literal = "<=";
        } else {
            result->type = _less;
            result->literal = "<";
        }
    }
    else {
        result->type = _illegal;
        result->literal = edge_util_sub(lexer->source, begin, lexer->offset - begin);
    }

    return result;
}

edge_token_t *edge_lexer_tokenize_string(edge_lexer_t* lexer) {
    edge_token_t *result = edge_malloc(sizeof(edge_token_t));
    size_t begin = lexer->offset;

    char symbol = edge_lexer_peek_current(lexer);
    result->type = _string;

    if(edge_lexer_peek_current(lexer) != '\'' && edge_lexer_peek_current(lexer) != '"') {
        printf("Invalid string literal\n");
    }
    lexer->offset++;

    while(edge_lexer_peek_current(lexer) != symbol && edge_lexer_peek_current(lexer) != '\n' && edge_lexer_peek_current(lexer) != '\0') {
        lexer->offset++;
    }

    if(edge_lexer_peek_current(lexer) != symbol) {
        printf("Unfinished string literal\n");
    }
    lexer->offset++;

    result->literal = edge_util_sub(lexer->source, begin + 1, lexer->offset - begin);

    return result;
}

edge_token_t *edge_lexer_tokenize_number(edge_lexer_t* lexer) {
    edge_token_t *result = edge_malloc(sizeof(edge_token_t));
    size_t begin = lexer->offset;

    result->type = _integer;

    if(!(edge_lexer_is_number(edge_lexer_peek_current(lexer), false))) {
        printf("Invalid integer literal\n");
    }
    lexer->offset++;

    while(edge_lexer_is_number(edge_lexer_peek_current(lexer), true)) {
        if(edge_lexer_peek_current(lexer) == '.' || edge_lexer_peek_current(lexer) == '_') {
            if(!(edge_lexer_is_number(edge_lexer_peek_next(lexer), false))) {
                printf("Invalid decimal/float literal\n");
            }

            if(edge_lexer_peek_current(lexer) == '.') {
                if(result->type == _integer) {
                    result->type = _float;
                } else {
                    printf("Invalid decimal/float literal\n");
                }
            }
        }
        lexer->offset++;
    }

    result->literal = edge_util_sub(lexer->source, begin + 1, lexer->offset - begin);

    return result;
}

edge_token_t *edge_lexer_tokenize_identifier(edge_lexer_t* lexer) {
    edge_token_t *result = edge_malloc(sizeof(edge_token_t));
    size_t begin = lexer->offset;

    result->type = _identifier;

    if(!(edge_lexer_is_identifier(edge_lexer_peek_current(lexer), false))) {
        printf("Invalid identifier literal\n");
    }

    lexer->offset++;
    while(edge_lexer_is_identifier(edge_lexer_peek_current(lexer), true)) {
        lexer->offset++;
    }

    result->literal = edge_util_sub(lexer->source, begin + 1, lexer->offset - begin);

    return result;
}

edge_token_t *edge_lexer_tokenize_comment(edge_lexer_t* lexer) {
    edge_token_t *result = edge_malloc(sizeof(edge_token_t));
    size_t begin = lexer->offset;

    result->type = _comment;

    if(edge_lexer_peek_current(lexer) != '#') {
        printf("Invalid comment literal\n");
    }

    lexer->offset++;
    while(edge_lexer_peek_current(lexer) != '\0' && edge_lexer_peek_current(lexer) != '\n') {
        lexer->offset++;
    }

    result->literal = edge_util_sub(lexer->source, begin, lexer->offset - begin);

    return result;
}

edge_token_t *edge_lexer_go_next(edge_lexer_t* lexer) {
    edge_token_t *result = edge_malloc(sizeof(edge_token_t));
    size_t begin = lexer->offset;
    char current = edge_lexer_peek_current(lexer);

    while(edge_lexer_is_whitespace(edge_lexer_peek_current(lexer))) {
        lexer->offset++;
    }

    switch(current) {
        case '\0': {
            result->type = _eof;
            lexer->offset++;

            result->literal = "\0";
            break;
        }
        
        case '+': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '-': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '*': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '/': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '%': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '=': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '!': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '>': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '<': {
            result = edge_lexer_tokenize_operator(lexer);
            break;
        }

        case '.': {
            result->type = _dot;
            lexer->offset++;

            result->literal = ".";
            break;
        }

        case ',': {
            result->type = _comma;
            lexer->offset++;

            result->literal = ",";
            break;
        }

        case ':': {
            result->type = _colon;
            lexer->offset++;

            result->literal = ":";
            break;
        }

        case ';': {
            result->type = _semicolon;
            lexer->offset++;

            result->literal = ";";
            break;
        }

        case '|': {
            result->type = _pipe;
            lexer->offset++;

            result->literal = "|";
            break;
        }

        case '\'': {
            result = edge_lexer_tokenize_string(lexer);
            break;
        }

        case '"': {
            result = edge_lexer_tokenize_string(lexer);
            break;
        }

        case '#': {
            result = edge_lexer_tokenize_comment(lexer);
            break;
        }

        case '{': {
            result->type = _left_brace; 
            lexer->offset++;

            result->literal = "{";
            break;
        }

        case '}': {
            result->type = _right_brace; 
            lexer->offset++;

            result->literal = "}";
            break;
        }

        case '(': {
            result->type = _left_paren; 
            lexer->offset++;

            result->literal = "(";
            break;
        }

        case ')': {
            result->type = _right_paren; 
            lexer->offset++;

            result->literal = ")";
            break;
        }

        case '[': {
            result->type = _left_square; 
            lexer->offset++;

            result->literal = "[";
            break;
        }

        case ']': {
            result->type = _right_square; 
            lexer->offset++;

            result->literal = "]";
            break;
        }

        default: {
            if(edge_lexer_is_number(current, false)) {
                result = edge_lexer_tokenize_number(lexer);
            }
            else if(edge_lexer_is_identifier(current, false)) {
                result = edge_lexer_tokenize_identifier(lexer);
            }
            else {
                result->type = _illegal;
                lexer->offset++;

                result->literal = edge_util_sub(lexer->source, begin, lexer->offset - begin);
            }
            break;
        }
    }

    return result;
}

void edge_lexer_destroy(edge_lexer_t *lexer) {
    edge_free(lexer);
}