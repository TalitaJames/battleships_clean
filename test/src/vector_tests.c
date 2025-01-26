#include "vector_tests.h"

// Test Vector
void TEST_VECTOR_INIT(){
    Vector v;
    vectorInit(&v, 10); //TODO ask someone (alan?) about memory and best practices

    ASSERT(v.size == 10, "Vector should have starting size 10");
    ASSERT(v.used ==  0, "Vector shouldn't have used any elements");
    // ASSERT(v.array[0] == 0 , "Array should be empty when first made"); //TODO how do i test this?

    printf("\tPASSED Vector Initialise\n");
}

void TEST_VECTOR_INSERT(){
    Vector v;
    vectorInit(&v, 10);
    ASSERT(v.size == 10, "Vector should have starting size 10");

    vectorInsert(&v, 2);
    int usedCount = 1; // Test specific count of insertions for comparison
    ASSERT(v.used ==  1, "Inserting into vector should increment used");
    ASSERT(v.size == 10, "Vector size shouldn't change after single insertion");
    ASSERT(v.array[0] ==  2, "Value in array should be set correctly");

    for (size_t i = 1; i < 70; i++){
        vectorInsert(&v, i+2);
        usedCount++;
    }
    ASSERT(v.used == usedCount, "Vector used value should match number of times inserted");

    for (size_t i = 0; i < v.used; i++){
        ASSERT(v.array[i]==i+2, "Values in the array should be set correctly");
    }
    printf("\tPASSED Vector Insertion\n");
}