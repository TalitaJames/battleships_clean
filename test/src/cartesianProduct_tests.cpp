#include "cartesianProduct_tests.h"
#include <iostream>


bool TEST_CARTESIANPRODUCT_cartesianProduct_singleVector(){
    std::vector<std::vector<int>> A = {{0, 1}, {0,1}};
    std::function<bool(std::vector<int>)> trueIfEvenFirst = [](std::vector<int> S){ return S[0] % 2 == 0; };

    std::vector<std::vector<int>> expectedTestAA = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
    };
    auto resultA = cartesianProduct(A);


    ASSERT(resultA == expectedTestAA, "Expected {{0, 1}, {0, 1}} to equal all two bit binary");

    ENDTEST();
}

bool TEST_CARTESIANPRODUCT_cartesianProduct_singleVector_filter(){

    std::vector<std::vector<int>> A = {{0, 1}, {0,1}};
    std::function<bool(std::vector<int>)> trueIfEvenFirst = [](std::vector<int> S){ return S[0] % 2 == 0; };

    std::vector<std::vector<int>> expectedTestAA = {
        {0, 0},
        {0, 1},
    };

    auto resultA = cartesianProduct(A, trueIfEvenFirst);
    ASSERT(resultA == expectedTestAA, "Expected {{0, 1}, {0, 1}} to equal all two bit binary with filter");

    ENDTEST();
}

bool TEST_CARTESIANPRODUCT_cartesianProduct_twoVector(){
    // Test two bit binary (single vectors)
    std::vector<int> A = {0, 1};
    std::vector<std::vector<int>> expectedTestAA = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
    };
    auto resultA = cartesianProduct(A, A);
    ASSERT(resultA == expectedTestAA, "Expected {{0, 1}, {0, 1}} to equal {{0, 0}, {0, 1}, {1, 0}, {1, 1}}");

    ENDTEST();
}

bool TEST_CARTESIANPRODUCT_cartesianProduct_twoVector_filter(){
    // Test integers (single vectors and filter)
    std::function<bool(std::vector<int>)> trueIfEvenFirst = [](std::vector<int> S){ return S[0] % 2 == 0; };
    std::vector<int> C = {2, 3, 4, 5};
    std::vector<int> D = {7, 5, 6};

    std::vector<std::vector<int>> expectedTestCD = {
        {2, 7},
        {2, 5},
        {2, 6},
        {4, 7},
        {4, 5},
        {4, 6}
    };
    auto resultCD = cartesianProduct(C, D, trueIfEvenFirst);
    ASSERT(resultCD == expectedTestCD, "Expected integers to filter based off function");

    ENDTEST();
}

bool TEST_CARTESIANPRODUCT_cartesianProduct_VectorsAndVector(){
    // Test three bit binary (double vector and single)
    std::vector<std::vector<int>> expectedTestAA = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1},
    };
    std::vector<int> A = {0, 1};

    std::vector<std::vector<int>> expectedTestAAA = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    auto resultAAA = cartesianProduct(expectedTestAA, A);
    ASSERT(resultAAA == expectedTestAAA, "Expected 3 times repeated cartesian product of {0, 1} to give all 3-bit binary numbers");


    ENDTEST();
}

bool TEST_CARTESIANPRODUCT_cartesianProduct_VectorsAndVector_filter(){
    // Test three bit binary (double vector and single)
    std::vector<int> A = {0, 1};
    std::vector<std::vector<int>> expectedTestAA = {
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 1},
    };

    std::function<bool(std::vector<int>)> trueIfEvenFirst = [](std::vector<int> S){ return S[0] % 2 == 0; };

    std::vector<std::vector<int>> expectedTestAAA = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
    };
    auto resultAAA = cartesianProduct(expectedTestAA, A, trueIfEvenFirst);
    ASSERT(resultAAA == expectedTestAAA, "Expected 3-bit binary numbers starting with zero");

    ENDTEST();
}