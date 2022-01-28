#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include "edge/memory.h"

#include "edge/util.h"

const char *edge_util_sub(const char *a_1, size_t a_2, size_t a_3) {
    char *v_r = (char *) edge_alloc(a_2 + a_3, sizeof(char));
    strncpy(v_r, &a_1[a_2 - 1], a_3 + 1);
    return v_r;
}