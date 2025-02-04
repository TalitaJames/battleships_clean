#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <memory.h>
#include "ships.h"
#include "constants.h"

typedef struct Board{
    BoardDimensions dimensions;
    bool isEmpty;
    bool isValid;
    int board[BOARD_SIZE][BOARD_SIZE] {BOARD_DEFAULT}; // Array of the board in the form [x][y]
    ShipPosition shipPos[FLEET_SIZE] = {};
} Board;

Board initBlankBoard(void);
void wipeBoard(Board &);
void drawBoard(Board &, ShipPosition*);
Board rndBoard(void);

std::ostream& operator<<(std::ostream&, Board&);


#endif //BOARD_H