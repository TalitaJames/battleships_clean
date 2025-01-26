#include <stdio.h>
#include "test_utils.h"
#include "vector_tests.h"
#include "ships_tests.h"

int main(){
    printf("\nTESTING VECTOR\n");
    TEST_VECTOR_INIT();
    TEST_VECTOR_INSERT();

    printf("\nTESTING SHIPS\n");
    TEST_SHIP_BOUNDINGBOX();
    TEST_SHIP_COLLISIONS();

    return 0;
}