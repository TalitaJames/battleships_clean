#ifndef HITMASK_H
#define HITMASK_H

#include <iostream>
#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "ships.h"


/// @brief Types of states a cell may hold
enum cellStatus{
    UNKNOWN,
    MISS,
    HIT,
    SUNK,
    TURN, // For "One of the above", aka a shot without knowing the outcome
};

/// @brief status of the interaction with the board
struct Hitmask{
    cellStatus hitmask[BOARD_SIZE][BOARD_SIZE] {UNKNOWN};
    bool shipSunk[FLEET_SIZE] {false};
} ;


void hitBoard(Board b, Hitmask & h, int x, int y);
void findHitmaskDifference(Hitmask oldHitmask, Hitmask newHitmask, int &xCoord, int &yCoord);
int howManyTurnsTaken(Hitmask hitmask);
bool checkCompatible(Board board, Hitmask hitmask);
Hitmask turnsToShotmask(Board, Hitmask);

bool isHitmaskSolved(Hitmask); // have all the ship positions been hit?
bool isHit(Hitmask, int, int);

bool operator==(const struct Hitmask&, const struct Hitmask&);
bool operator!=(const struct Hitmask&, const struct Hitmask&);
std::ostream& operator<<(std::ostream&, Hitmask&);

#endif //HITMASK_H