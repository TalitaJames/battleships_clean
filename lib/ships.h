#ifndef SHIPS_H
#define SHIPS_H

#include <stdbool.h>
#include <stdio.h>

typedef int Ship;

typedef struct {
    // Bounding box
    int north;
    int east;
    int south;
    int west;
} ShipPlacement;

typedef struct{
    int width;
    int height;
} Board;

void singleShipPlacements(Board, Ship);
void allShipPlacements(Board, Ship[]);
ShipPlacement makeShipFromMinMaxDir(Ship length, int major, int minor, bool direction);

bool doShipsCollide(ShipPlacement shipA, ShipPlacement shipB);

// void diplayShip(struct Board, struct ShipPlacement[]);


#endif //SHIPS_H