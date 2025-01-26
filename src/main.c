#include <stdio.h>
#include <stdbool.h>
#include "ships.h"

int main(int argc, char* args[]) {
    Board board = {5, 5};
    Ship shipLengths[] = {5,4,3,3,2};

    allShipPlacements(board, shipLengths);
    return 0;
}


