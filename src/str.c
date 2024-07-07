#include "str.h"

#include <string.h>

int str_starts_with(const char *a, const char *b) {
    return strncmp(a, b, strlen(b)) == 0;
}