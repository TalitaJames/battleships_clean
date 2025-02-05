#include "cartesianProduct_tests.h"
#include <iostream>

void TEST_CARTESIANPRODUCT_cartesianProduct(){
    // void TEST_CARTESIANPRODUCT_cartesianProduct(std::vector<T> setA, std::vector<T> setB, std::function<bool(std::vector<T>)> filter);
    // void TEST_CARTESIANPRODUCT_cartesianProduct(std::vector<std::vector<T>> setA, std::vector<T> setB,std::function<bool(std::vector<T>)> filter);

    // Test two bit binary (single vectors)
    std::vector<int> A = {0, 1};
    std::vector<std::vector<int>> expectedTestA = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    auto resultA = cartesianProduct(A, A);
    ASSERT(resultA == expectedTestA, "Expected {{0, 1}, {0, 1}} to equal {{0, 0}, {0, 1}, {1, 0}, {1, 1}}");

    // Test three bit binary (double vector and single)
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
    auto resultAAA = cartesianProduct(expectedTestA, A);
    ASSERT(resultAAA == expectedTestAAA, "Expected 3 times repeated cartesian product of {0, 1} to give all 3-bit binary numbers");

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

    printf("\tPASSED cartesianProduct\n");
}

void TEST_CARTESIANPRODUCT_vectorIntoVectorVector(){
    // void TEST_CARTESIANPRODUCT_vectorIntoVectorVector(std::vector<T> set);
    std::vector<int> standardVector_in = {1,4,9};
    std::vector<std::vector<int>> standardVector_out = vectorIntoVectorVector(standardVector_in);
    ASSERT(standardVector_in.size() == standardVector_out.size(), "Vector size shouldn't change");

    for (size_t i = 0; i < standardVector_out.size(); i++){
        ASSERT(standardVector_in[i] == standardVector_out[i][0], "Element out should be identical to in");
    }

    printf("\tPASSED vectorIntoVectorVector\n");
}



