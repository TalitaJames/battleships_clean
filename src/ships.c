#include "ships.h"


/* given an empty board, calculates all valid positions for the ship
@param board the dimensions of the grid to place ship on
@param ship length of a single ship
@return //TODO
*/
void singleShipPlacements(Board board, Ship ship)
{
    int maxPositions = (board.width-ship+1)*board.height;
    if (ship>1) maxPositions += (board.height-ship+1)*board.width;

    printf("There are %i positions for ship %i\n", maxPositions, ship);

    for (size_t major = 0; major < board.width; major++) {
        for (size_t minor = 0; minor < board.height - ship + 1; minor++) {
            if(ship == 1){
                ShipPlacement newShip = makeShipFromMinMaxDir(ship, major, minor, true);
                continue; // if the ship is len 1, orientation doesn't matter
            }

            for(size_t orientation = 0; orientation <= 1; orientation++){
                ShipPlacement newShip = makeShipFromMinMaxDir(ship, major, minor, orientation);
            }
        }
    }
    return;
}


/* turn a major, minor and direction into a ship (bounding box)
@param length a ship length
@param major where the ship sits along the non bounded axis
@param minor where the ship sits along the bounded axis
@param direction which way the ship faces (1 for horizontal)
@return ShipPlacement
*/
ShipPlacement makeShipFromMinMaxDir(Ship length, int major, int minor, bool direction){
    ShipPlacement shipPlace;
    if(direction){
        shipPlace.north = major;
        shipPlace.east = minor + length -1;
        shipPlace.south = major;
        shipPlace.west = minor;
    }
    else{
        shipPlace.north = minor;
        shipPlace.east = major;
        shipPlace.south = minor + length -1;
        shipPlace.west = major;
    }
    return shipPlace;
}


/* given an empty board, calculates all valid positions for all ships
@param board the dimensions of the grid to place ships on
@param ships array with lengths of all ships in the game
@return //TODO
*/
void allShipPlacements(Board board, Ship ships[])
{
    // int shipsCount = sizeof(ships)/sizeof(ships[0]);
    for (size_t i = 0; i < 5; i++){
        singleShipPlacements(board, ships[i]);
    }

}


/*
@brief determines if the board is valid (ie ship follows placement rules)
@param shipA the first ship
@param shipB the second ship
@return bool, true if the two ships intersect
*/
bool doShipsCollide(ShipPlacement shipA, ShipPlacement shipB){
    if (shipA.south < shipB.north || // shipA is completely above shipB
        shipA.north > shipB.south || // shipA is completely below shipB
        shipA.west  > shipB.east  || // shipA is completely to the right of shipB
        shipA.east < shipB.west) {   // shipA is completely to the left of shipB
        return false;
    }

    return true;
}
