#ifndef SHIPS_H
#define SHIPS_H

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>

#include "constants.h"

/// @brief a ship position, stored as the space the ship takes
typedef struct {
    // Bounding box
    int north;
    int east;
    int south;
    int west;
} ShipBoundingBox;

/// @brief the position of a ship
typedef struct ShipPosition{
    unsigned int length;
    int x;
    int y;
    bool direction; // 1 represents horizontal
} ShipPosition;

// Generating ship positions
std::vector<ShipPosition> singleShipPositions(int boardSize, Ship);
std::vector<std::vector<ShipPosition>> allShipPositions(int boardSize, Ship[]);
ShipPosition rndShipPos(int boardSize, Ship);

// Conversions between various formats
ShipBoundingBox convertShipPositionToBoundingBox(ShipPosition);
ShipPosition convertBoundingboxToShipPosition(ShipBoundingBox);

// Check for collisions
bool doShipsCollide(ShipPosition shipA, ShipPosition shipB);
bool doShipsCollide(ShipBoundingBox shipA, ShipBoundingBox shipB);
bool areShipsValid(std::vector<ShipPosition> shipFleet);

// Opperator Overloads
std::ostream& operator<<(std::ostream&, const struct ShipPosition&);
std::ostream& operator<<(std::ostream&, const struct ShipPosition*);

bool operator==(const struct ShipPosition&, const struct ShipPosition&);
bool operator!=(const struct ShipPosition&, const struct ShipPosition&);

bool operator<(const struct ShipPosition&, const struct ShipPosition&);
bool operator>(const struct ShipPosition&, const struct ShipPosition&);

int compareShipArray(ShipPosition *pA, ShipPosition *pB);

// Iterating through ships
void nextShipPosition(ShipPosition &);
void nextShipPosArray(ShipPosition *);

void setStartArray(ShipPosition *);
void setEndArray(ShipPosition *);



#endif //SHIPS_H