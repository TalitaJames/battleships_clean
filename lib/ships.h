/**
 * @file
 * @author Talita
 * @brief Information about a single ship and its position
 * @date 2025-02-06
 */
#ifndef SHIPS_H
#define SHIPS_H

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>

#include "constants.h"

/// @brief a ship position, stored as the space the ship takes
typedef struct ShipBoundingBox{
    // Bounding box
    int north;
    int east;
    int south;
    int west;
} ShipBoundingBox;

/// @brief the position of a ship
typedef struct ShipPosition{
    unsigned char length = 0;
    unsigned char x = 0;
    unsigned char y = 0;
    bool direction = 0; // 1 represents horizontal
} ShipPosition;

// Generating ship positions
std::vector<ShipPosition> singleShipPositions(int boardSize, ShipData);
std::vector<std::vector<ShipPosition>> allShipPositions(int boardSize, const ShipData fleet[], int fleetSize);
ShipPosition rndShipPos(int boardSize, ShipData);

// Conversions between various formats
ShipBoundingBox convertShipPositionToBoundingBox(ShipPosition);
ShipPosition convertBoundingboxToShipPosition(ShipBoundingBox);
void shipVectorToArray(std::vector<ShipPosition>, ShipPosition*, int);


// Check for collisions
bool doShipsCollide(ShipPosition shipA, ShipPosition shipB);
bool doShipsCollide(ShipBoundingBox shipA, ShipBoundingBox shipB);

bool doesShipFitOnBoard(ShipPosition shipA); //TODO test me
bool doesShipFitOnBoard(ShipBoundingBox shipA); //TODO test me
bool doesShipFitOnBoard(ShipPosition shipA, int boardSize); //TODO test me
bool doesShipFitOnBoard(ShipBoundingBox shipA, int boardSize); //TODO test me

bool areShipsValid(ShipPosition *fleet, int fleetSize);
bool areShipsValidInBoardArray(ShipPosition *fleet, int fleetSize);
bool areShipsValidInBoardVector(std::vector<ShipPosition> shipFleet);

// Opperator Overloads
std::ostream& operator<<(std::ostream&, const struct ShipPosition&);
std::ostream& operator<<(std::ostream&, const struct ShipPosition*);
std::ostream& operator<<(std::ostream&, const struct ShipBoundingBox&);

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