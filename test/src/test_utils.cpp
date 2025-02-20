#include "test_utils.h"

/**
 * @brief Generic testing function for a batch (eg file) of tests
 *
 * @param testFunctions the vector of functions to be tested
 * @param name name of group of functions to be tested
 * @return true if none failed, else false
 */
bool TEST_ALL(const std::vector<TestFunction>& testFunctions, std::string name) {
    std::cout << "\e[0;1m==================================================\e[0m\n";
    std::cout << "\e[0;1m\tTESTING " << name << " \e[0m\n";

    int passedTests = 0;
    int failedTests = 0;

    for (const auto& testFunction : testFunctions) {
        if (testFunction()) {
            passedTests++;
        } else {
            failedTests++;
        }
    }

    std::cout << "\n\e[0;1m\tDONE " << name << ": \e[32;1m" << passedTests << " PASSED \e[31;1m" << failedTests << " FAILED\e[0m\n";
    std::cout << "\e[0;1m==================================================\e[0m\n\n";

    return 0 == failedTests;
}