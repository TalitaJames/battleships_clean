#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>

#define ASSERT(cond, message) do { \
    if (!(cond)) { \
        printf("Assertion failed: %s\n", message); \
        return; \
    } \
} while (0)

#endif // TEST_UTILS_H
