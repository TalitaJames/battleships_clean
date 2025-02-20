#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <functional>
#include <vector>
#include <iostream>
#include <string>

#define testVerbosity false

/// @brief test a condition and print an appropriate message in the case of a failure
#define ASSERT(cond, message) do { \
    if (!(cond)) { \
        printf("\t\e[31;1mAssertion failed: \e[31m%s\n\e[0m", message); \
        printf("\e[31mFile: %s, Line: %d, Function: %s\n\e[0m", __FILE__, __LINE__, __func__); \
        return false; \
    } \
} while (0)

/// @brief summarise a successfull test
#define ENDTEST() do { \
    if(testVerbosity) printf("\t\e[32mPASSED\e[0m %s\n", __func__); \
    return true; \
} while (0)

using TestFunction = std::function<bool()>;

bool TEST_ALL(const std::vector<TestFunction>& testFunctions, std::string name);

#endif // TEST_UTILS_H
