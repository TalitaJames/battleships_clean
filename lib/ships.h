#ifndef SHIPS_H
#define SHIPS_H

#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "board.h"

typedef unsigned int Ship;

const Ship FLEET[] = {5, 5, 7};
const short FLEET_SIZE = sizeof(FLEET)/sizeof(FLEET[0]);

typedef struct {
    // Bounding box
    int north;
    int east;
    int south;
    int west;
} ShipBoundingBox;

typedef struct {
    unsigned int length;
    int x;
    int y;
    bool direction; // 1 represents horizontal
} ShipPosition;

// Generating ship positions
std::vector<ShipPosition> singleShipPositions(BoardDimensions, Ship);
std::vector<std::vector<ShipPosition>> allShipPositions(BoardDimensions, Ship[]);
ShipPosition rndShipPos(Ship);

// Conversions between various formats
ShipBoundingBox convertShipPositionToBoundingBox(ShipPosition);
ShipPosition convertBoundingboxToShipPosition(ShipBoundingBox);

// Check for collisions
bool doShipsCollide(ShipPosition shipA, ShipPosition shipB);
bool doShipsCollide(ShipBoundingBox shipA, ShipBoundingBox shipB);

std::ostream& operator<<(std::ostream&, ShipPosition&);

// int compareShipPositions(ShipPosition, ShipPosition);
// int compareShipArray(ShipPosition *, ShipPosition *);

// unsigned long shipPosToInt(ShipPosition);
// unsigned long shipArrayToInt(ShipPosition *);
// void intToShipPos(unsigned long, ShipPosition &);
// void intToShipArray(unsigned long, ShipPosition *);
// board intToBoard(unsigned long);

// void nextShipPosition(ShipPosition &);
// void nextShipPosition(ShipPosition &, ship);
// void nextShipPosArray(ShipPosition *, ship const);

// bool isStartPos(ShipPosition);
// bool isStartArray(ShipPosition *);
// void setEndArray(ShipPosition *);
// void setStartArray(ShipPosition *);


#endif //SHIPS_H