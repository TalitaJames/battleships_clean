#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <memory.h>
#include "ships.h"

#define BOARD_SIZE 10
#define BOARD_DEFAULT -1

typedef struct {
    BoardDimensions dimensions;
    bool isEmpty;
    bool isValid;
    int board[BOARD_SIZE][BOARD_SIZE] {BOARD_DEFAULT}; // Array of the board in the form [x][y]
    // int shipPositionsInt = 0; // Int representing the ship position array, aka arangment of boats on the board
    //TODO how to store the board? (just an array of ship positions imo) (bitmask?)
} Board;

Board initBlankBoard(void);
void wipeBoard(Board &);
void drawBoard(Board &, ShipPosition*); //TODO such as this
Board rndBoard(void);

std::ostream& operator<<(std::ostream&, Board&);


#endif //BOARD_H