#include "ships.h"

/*!
@brief Given an empty board, calculates all valid positions for the ship
@param board the dimensions of the grid to place ship on
@param ship length of a single ship
@return //TODO implement single ship positions
*/
std::vector<ShipPosition> singleShipPositions(int boardSize, Ship shipLength) {

    int maxPositions = (boardSize-shipLength+1)*boardSize;
    if (shipLength>1) maxPositions += (boardSize-shipLength+1)*boardSize;

    std::vector<ShipPosition> allSingleShipPositions;
    allSingleShipPositions.reserve(maxPositions);

    for (int major = 0; major < boardSize; major++) {
        for (int minor = 0; minor < boardSize - shipLength + 1; minor++) {
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
@return //TODO implement this function
*/
std::vector<std::vector<ShipPosition>> allshipPositions(int boardSize, Ship fleet[])
{
    std::vector<std::vector<ShipPosition>> fixme;
    // int shipsCount = sizeof(ships)/sizeof(ships[0]);
    for (size_t i = 0; i < 5; i++){
        singleShipPositions(boardSize, fleet[i]);
    }
    return fixme;

}


/**
 * @brief  Generates a random position for a ship
 * @param len a length of the ship
 * @bug this is known to only generate ships stating in the top left corner
 * @return shipPosition a (semi) random shipPosition
 */
ShipPosition rndShipPos(int boardSize, Ship len){
    std::random_device rdDev;
    std::mt19937 rng(rdDev());

    int max = std::max(0, boardSize - (int)(len));

    std::uniform_int_distribution<std::mt19937::result_type> udist(0,boardSize-len);

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
 * @return the stream
 */
std::ostream& operator<<(std::ostream& os,  const struct ShipPosition& shipPos){
    std::string dirStr = "→";
    if (!shipPos.direction) dirStr = "↓";

    os << "len:" << shipPos.length << " (" << shipPos.x << ", " << shipPos.y << ", " << dirStr << ")";

    return os;
};

/**
 * @brief toString overload for an array of ship positions
 * @param os a stream
 * @param shipPos given ship position
 * @return the stream with the array
 */
std::ostream& operator<<(std::ostream& os,  const struct ShipPosition* shipArray){
    for (size_t i = 0; i < FLEET_SIZE; i++){
        os << shipArray[i] << "\t";
    }
    return os;
};


/**
 * @brief Checks if two ShipPositions match.
 * Note that length isn't checked, as it is negligible for considering the same positions
 * 
 * @param A first ship position
 * @param B second ship position
 * @return bool true if equal
 */
bool operator==(const struct ShipPosition &A,  const struct ShipPosition &B){

    if (A.x != B.x) return false;
    if (A.y != B.y) return false;
    if (A.direction != B.direction) return false;

    return true;
};

/**
 * @brief Checks if two ShipPositions aren't equal
 * @param A first ship position
 * @param B second ship position
 * @return bool true if not equal
 */
bool operator!=(const struct ShipPosition &A,  const struct ShipPosition &B){
    return !(A==B);
};

/**
 * @brief Checks if B is greater than A, in priority of direction (vertical < horizontal) and if B is lower and further right.
 * Note that length isn't checked, as it is negligible for considering the same positions
 * @param A First ship position
 * @param B Seccond ship position
 * @return true if A is greater than B
 */
bool operator<(const struct ShipPosition &A, const struct ShipPosition &B){

    if (A.direction != B.direction){ // if directions aren't equal
        return A.direction < B.direction; // horizontal (true) is greater
    }

    if (A.y != B.y){
        return A.y < B.y;
    }

    if (A.x != B.x){
        return A.x < B.x;
    }

    return false; // if all else fails, they are equal (thus not greater than)
}

/**
 * @brief Checks if A is greater than B, ie is A is closer to the bottom, and further right
 *          (or is vertical and B is not)
 * @param A First ship position
 * @param B Seccond ship position
 * @return true if A is not less than B AND A is not equal to B (thus less than)
 */
bool operator>(const struct ShipPosition &A, const struct ShipPosition &B){
    if (!(A<B) && (A!=B)) return true;
    return false;
}

/**
 * @brief Compares two shipPosition arrays and determines which is "greater".
 * The "greatest" array is the one with a greater ship,
 * compared from left to right in the array
 *
 * @param pA position A
 * @param pB position B
 * @return int comparing the sizes, ie -1 if pA>pB, 0 if pA=pB, 1 if pA<pB
*/
int compareShipArray(ShipPosition *pA, ShipPosition *pB){
    for (size_t i = 0; i < FLEET_SIZE; i++){
        if (pA[i] != pB[i]){
            // if pA>pB return -1, else return 1
            return (pA[i] > pB[i]) ? -1 : 1;
        }
    }
    return 0;
};


/**
 * @brief Given a ship position and a ship, generate the next one in sequence.
 * A ship "starts" in the vertical top left corner,
 * and moves down, then right, then flips direction (to be horizontal)
 *
 * @param shipPos the given ship position
*/
void nextShipPosition(ShipPosition &shipPos){
    shipPos.y++;

    if (shipPos.direction && shipPos.y >= BOARD_SIZE){
        shipPos.y=0;
        shipPos.x++;
    } else if (!shipPos.direction && shipPos.y > BOARD_SIZE - shipPos.length){
        shipPos.y=0;
        shipPos.x++;
    }

    if (shipPos.direction && shipPos.x > BOARD_SIZE - shipPos.length){
        shipPos.x=0;
        shipPos.y=0;
        shipPos.direction = !shipPos.direction;
    } else if (!shipPos.direction && shipPos.x >= BOARD_SIZE){
        shipPos.x=0;
        shipPos.y=0;
        shipPos.direction = !shipPos.direction;
    }
};

/**
 * @brief Generate the next ship position array, from the current position
 * From the last ship (nth) ship to the position will itterate to the next,
 * then check if it has "overflowed" back to the starting position.
 * It continues reseting from right to left until either that position overflows to the start,
 * or all positions in the array have been incremented.
 *
 * @param shipPosArray a pointer to the ship position array
*/
void nextShipPosArray(ShipPosition* shipPosArray){
    ShipPosition startingShipPos = {0,0,0,0};

    for (int i = FLEET_SIZE-1; i >= 0; i--){
        nextShipPosition(shipPosArray[i]);
        if (shipPosArray[i] != startingShipPos){
            return;
        }
    }
};



/**
 * @brief set the given array to have a ship at (0,0)
 * @param shipPosArray the array to be set to {length, 0, 0,0}
 */
void setStartArray(ShipPosition * shipPosArray){
    for (size_t i = 0; i < FLEET_SIZE; i++){
        shipPosArray[i].length = FLEET[i];
        shipPosArray[i].x = 0;
        shipPosArray[i].y = 0;
        shipPosArray[i].direction = 0;
    }
}

/**
 * @brief Sets every value of a ship position array to the end.
 * The last value is the bottom right horizontal position
 *
 * @param shipPosArray a pointer to a ship posion array
*/
void setEndArray(ShipPosition * shipPosArray){
    for (size_t i = 0; i < FLEET_SIZE; i++){
        shipPosArray[i].length = FLEET[i];
        shipPosArray[i].x = BOARD_SIZE - FLEET[i]; // No +1 because that is imbeded in the fact BOARD_SIZE is always one above x
        shipPosArray[i].y = BOARD_SIZE - 1;
        shipPosArray[i].direction = 1; // true (->) is the last value
    }
}
