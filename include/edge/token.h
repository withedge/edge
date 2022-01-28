#ifndef EDGE_TOKEN_H
#define EDGE_TOKEN_H

#include <stdlib.h>

typedef enum {
    _illegal,
    _eof,

    _add,
    _add_assign,
    _increment,

    _sub,
    _sub_assign,
    _decrement,

    _mult,
    _mult_assign,
    
    _div,
    _div_assign,
    
    _mod,
    _mod_assign,

    _equal,
    _assign,

    _bang,
    _bang_equal,

    _greater,
    _greater_equal,

    _less,
    _less_equal,

    _dot,
    _comma,
    _colon,
    _semicolon,
    _pipe,
    _left_brace,
    _right_brace,
    _left_paren,
    _right_paren,
    _left_square,
    _right_square,

    _comment,
    _string,
    _identifier,
    _integer,
    _float
} edge_token_type_t;

typedef struct {
    edge_token_type_t type;
    size_t position;
    const char *literal;
} edge_token_t;

edge_token_t *edge_token_new(edge_token_type_t, size_t, const char *);
void edge_token_destroy(edge_token_t *);

#endif