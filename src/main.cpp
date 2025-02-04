#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <vector>
#include <stdlib.h>

#include "ships.h"
#include "board.h"
#include "hitmask.h"
#include "probabilityGrid.h"
#include "boardIterator.h"
#include "playGame.h"

int main(int argc, char* args[]) {
    Board board = rndBoard();

    saveGame(CoordinateChooser::P_MAX, board);

    return 0;
}


