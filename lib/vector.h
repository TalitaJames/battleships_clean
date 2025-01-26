#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Vector;


// Inspired by this https://stackoverflow.com/a/3536261

void vectorInit(Vector *a, size_t initialSize);
void vectorInsert(Vector *a, int element);
void vectorFree(Vector *a);


#endif //VECTOR_H