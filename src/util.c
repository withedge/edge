#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include "edge/memory.h"

#include "edge/util.h"

const char *edge_util_sub(const char *source, size_t begin, size_t n) {
    char *result = (char *) edge_alloc(begin + n, sizeof(char));
    strncpy(result, &source[begin - 1], n + 1);
    return result;
}