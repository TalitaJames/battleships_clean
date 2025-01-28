#include "vector.h"


void vectorInit(Vector *a, size_t initialSize) {
    a->array = (int*) malloc(initialSize * sizeof(int));
    if (a->array == NULL) {
        // Handle memory allocation failure
        a->used = 0;
        a->size = 0;
        return;
    }
    a->used = 0;
    a->size = initialSize;
}

void vectorAppend(Vector *a, int element) {
    // a->used is the number of used entries, because a->array[a->used++]
    // updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (a->used == a->size) {
        size_t newSize = a->size * 2;
        if (newSize == 0) newSize = 1;
        int *newArray = (int*)realloc(a->array, newSize * sizeof(int)); // Explicit cast to int*
        if (newArray == NULL) {
            return; //FIXME throw an error instead?
        }

        a->array = newArray;
        a->size = newSize;
    }
    a->array[a->used++] = element;
}

void vectorDisplay(Vector *a){
    printf("Array: used %li, size %li\n[", a->used, a->size);
    for (size_t i = 0; i < a->used; i++)
    {
        printf("%i,", a->array[i]);
    }
    printf("]\n");
}

void vectorFree(Vector *a) {
    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
}