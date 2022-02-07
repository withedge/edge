#ifndef EDGE_TOKEN_H
#define EDGE_TOKEN_H

#include <stdlib.h>

typedef enum {
    _illegal,
    _eof,
    _bn,
    _bt,

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
    _binary,
    _hex,
    _float,

    _k_i8,
    _k_i16,
    _k_int,
    _k_i64,
    _k_u8,
    _k_u16,
    _k_u32,
    _k_u64,
    _k_f32,
    _k_f64,
    _k_bool,
    _k_char,

    _k_use,
    _k_var,
    _k_let,
    _k_fun,
    _k_return,
    _k_if,
    _k_else,
    _k_elif
} edge_token_type_t;

typedef struct {
    edge_token_type_t type;
    size_t position;
    const char *literal;
} edge_token_t;

typedef struct {
    edge_token_t **data;
    size_t capacity;
    size_t offset;
} edge_list_token_t;

edge_list_token_t *edge_list_token_new();
void edge_list_token_destroy(edge_list_token_t *);

edge_token_t *edge_list_token_get(edge_list_token_t *, size_t);
void edge_list_token_push(edge_list_token_t *, edge_token_t *);
void edge_list_token_remove(edge_list_token_t *, size_t);

edge_token_t *edge_token_new(edge_token_type_t, size_t, const char *);
void edge_token_destroy(edge_token_t *);

#endif