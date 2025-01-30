#include "ships.h"

/*!
@brief Given an empty board, calculates all valid positions for the ship
@param board the dimensions of the grid to place ship on
@param ship length of a single ship
@return //TODO
*/
std::vector<ShipPosition> singleShipPositions(BoardDimensions board, Ship shipLength) {

    int maxPositions = (board.width-shipLength+1)*board.height;
    if (shipLength>1) maxPositions += (board.height-shipLength+1)*board.width;

    std::vector<ShipPosition> allSingleShipPositions;
    allSingleShipPositions.reserve(maxPositions);

    for (int major = 0; major < board.width; major++) {
        for (int minor = 0; minor < board.height - shipLength + 1; minor++) {
            if(shipLength == 1){
                ShipPosition newShip = {shipLength, major, minor, true};
                allSingleShipPositions.push_back(newShip);
                continue; // if the shipLength 1, orientation doesn't matter
            }

            for (int orientation = 0; orientation < 2; orientation++) {
                ShipPosition newShip = {shipLength, major, minor, (bool) orientation};
                allSingleShipPositions.push_back(newShip);
            }
        }
    }
    return allSingleShipPositions;
}


/*!
@brief Given an empty board, calculates all valid positions for all ships
@param board the dimensions of the grid to place ships on
@param ships array with lengths of all ships in the game
@return //TODO
*/
std::vector<std::vector<ShipPosition>> allshipPositions(BoardDimensions board, Ship fleet[])
{
    std::vector<std::vector<ShipPosition>> fixme;
    // int shipsCount = sizeof(ships)/sizeof(ships[0]);
    for (size_t i = 0; i < 5; i++){
        singleShipPositions(board, fleet[i]);
    }
    return fixme;

}


/*!
@breif Generates a random position for a ship
@param len a length of the ship
@return shipPosition a (semi) random shipPosition
*/
ShipPosition rndShipPos(Ship len){
    std::random_device rdDev;
    std::mt19937 rng(rdDev());
    std::uniform_int_distribution<std::mt19937::result_type> udist(0,BOARD_SIZE-len);

    ShipPosition pos;
    pos.length = len;
    pos.x = udist(rng);
    pos.y = udist(rng);
    pos.direction = rand() % 2;

    return pos;
};


/*!
@brief Turn a major, minor and direction into a ship (bounding box)
@param length a ship length
@param major where the ship sits along the non bounded axis
@param minor where the ship sits along the bounded axis
@param direction which way the ship faces (1 for horizontal)
@return ShipBoundingBox
*/
ShipBoundingBox convertShipPositionToBoundingBox(ShipPosition sP){
    ShipBoundingBox shipBounds;
    shipBounds.north = sP.y;
    shipBounds.west = sP.x;

    if(sP.direction){
        shipBounds.east = sP.x + sP.length -1;
        shipBounds.south = sP.y;
    }
    else{
        shipBounds.east = sP.x;
        shipBounds.south = sP.y + sP.length -1;
    }
    return shipBounds;
}

/*!
@brief Determines if the board is valid (ie ship follows placement rules)
@param shipA the first ship in ship position format
@param shipB the second ship in ship position format
@return bool, true if the two ships intersect
*/
bool doShipsCollide(ShipPosition shipA, ShipPosition shipB){
    return doShipsCollide(convertShipPositionToBoundingBox(shipA),
                            convertShipPositionToBoundingBox(shipB));
};

/*!
@brief Determines if the board is valid (ie ship follows placement rules)
@param shipA the first ship
@param shipB the second ship
@return bool, true if the two ships intersect
*/
bool doShipsCollide(ShipBoundingBox shipA, ShipBoundingBox shipB){
    if (shipA.south < shipB.north || // shipA is completely above shipB
        shipA.north > shipB.south || // shipA is completely below shipB
        shipA.west  > shipB.east  || // shipA is completely to the right of shipB
        shipA.east < shipB.west) {   // shipA is completely to the left of shipB
        return false;
    }

    return true;
};


/**
 * @brief toString overload for ship position
 * @param os a stream
 * @param shipPos given ship position
 * @return * toString& ship position converted to string
 */
std::ostream& operator<<(std::ostream& os, ShipPosition& shipPos){
    std::string dirStr = "→";
    if (!shipPos.direction) dirStr = "↓";
    os << "(" << shipPos.x << ", " << shipPos.y << ", " << dirStr << ")";

    return os;
};
