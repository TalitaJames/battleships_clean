#include "ships.h"

/**
 * @brief Given an empty board, calculates all valid positions for the ship
 * @param boardSize the dimensions of the grid to place ship on
 * @param ship length of a single ship
 * @return a vector of all legal ship positions
 */
std::vector<ShipPosition> singleShipPositions(int boardSize, ShipData shipLength) {
    if (0 == shipLength || shipLength > boardSize ) return std::vector<ShipPosition>{};

    int maxPositions = (boardSize-shipLength+1)*boardSize;
    if (shipLength>1) maxPositions += (boardSize-shipLength+1)*boardSize;

    std::vector<ShipPosition> allSingleShipPositions;
    allSingleShipPositions.reserve(maxPositions);

    for(int orientation = 0; orientation < 2; orientation++){
        for (ShipData x = 0; x < boardSize; x++) {
            for (ShipData y = 0; y < boardSize; y++) {
                ShipPosition newShip = {shipLength, x, y, (bool) orientation};
                if(doesShipFitOnBoard(newShip, boardSize)){
                    allSingleShipPositions.push_back(newShip);
                }
            }
        }
        if(shipLength == 1) break; // For 1 length ships, orientation doesn't matter
    }
    return allSingleShipPositions;
}


/**
 * @brief Given an empty board, calculates all valid positions for all ships
 * @param board the dimensions of the grid to place ships on
 * @param fleet array with lengths of all ships in the game
 * @param fleetSize number of ships in the fleet array
 * @return a vector of vectors where each vector (0 to fleet) contains a vector of all possible valid positions
 */
std::vector<std::vector<ShipPosition>> allShipPositions(int boardSize, const ShipData fleet[], int fleetSize) {
    std::vector<std::vector<ShipPosition>> allSingleShipPositions;

    for(size_t i = 0; i < fleetSize; i++){
        allSingleShipPositions.push_back(singleShipPositions(boardSize, fleet[i]));
	}

    return allSingleShipPositions;
}


/**
 * @brief  Generates a random position for a ship
 * @param len a length of the ship
 * @bug this is known to only generate ships stating in the top left corner
 * @return shipPosition a (semi) random shipPosition
 */
ShipPosition rndShipPos(int boardSize, ShipData len){
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


/**
 * @brief Turn a ship position into a bounding box
 * @param sP the ship, including length, x, y &direction
 * @return ShipBoundingBox
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

/**
 * @brief Turn a a boundng box into a real ship
 * @param sBB the ship bounding box
 * @return ShipPosition
 */
ShipPosition convertBoundingboxToShipPosition(ShipBoundingBox sBB){
    ShipPosition shipPos;
    shipPos.x = sBB.west;
    shipPos.y = sBB.north;
    shipPos.direction = (sBB.east > sBB.west); // true if horizontal
    shipPos.length = (shipPos.direction) ? (sBB.east - sBB.west + 1) : (sBB.south - sBB.north + 1);

    return shipPos;
}

void shipVectorToArray(std::vector<ShipPosition> shipPosVector, ShipPosition* shipPos, int arraySize){
    for (size_t i = 0; i < arraySize; i++){
        shipPos[i] = shipPosVector[i];
    }
}


/**
 * @brief Determines if the board is valid (ie ship follows placement rules)
 * @param shipA the first ship in ship position format
 * @param shipB the second ship in ship position format
 * @return bool, true if the two ships intersect
 */
bool doShipsCollide(ShipPosition shipA, ShipPosition shipB){
    return doShipsCollide(convertShipPositionToBoundingBox(shipA),
                            convertShipPositionToBoundingBox(shipB));
};

/**
 * @brief Determines if the board is valid (ie ship follows placement rules)
 * @param shipA the first ship
 * @param shipB the second ship
 * @return bool, true if the two ships intersect
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
 * @brief checks if a ship is within the board size
 *
 * @param shipA the ship in question
 * @return true if the ship is within the bounds of the board, else false
 */
bool doesShipFitOnBoard(ShipPosition shipA){
    return doesShipFitOnBoard(convertShipPositionToBoundingBox(shipA), BOARD_SIZE);
};

/**
 * @brief checks if a ship is within the board size
 *
 * @param shipA the ship in question
 * @return true if the ship is within the bounds of the board, else false
 */
bool doesShipFitOnBoard(ShipBoundingBox shipA){
   return doesShipFitOnBoard(shipA, BOARD_SIZE);
};

/**
 * @brief checks if a ship is within the board size
 *
 * @param shipA the ship in question
 * @param boardSize size of the board to test bounds of
 * @return true if the ship is within the bounds of the board, else false
 */
bool doesShipFitOnBoard(ShipPosition shipA, int boardSize){
    return doesShipFitOnBoard(convertShipPositionToBoundingBox(shipA), boardSize);
};

/**
 * @brief checks if a ship is within the board size
 *
 * @param shipA the ship in question
 * @param boardSize size of the board to test bounds of
 * @return true if the ship is within the bounds of the board, else false
 */
bool doesShipFitOnBoard(ShipBoundingBox shipA, int boardSize){
    bool fitOnBoardVertical = ((0 <= shipA.north && shipA.north < boardSize) && ( 0 <= shipA.south && shipA.south < boardSize));
    bool fitOnBoardHorizontal = ((0 <= shipA.east && shipA.east < boardSize) && ( 0 <= shipA.west && shipA.west < boardSize));

    return fitOnBoardVertical && fitOnBoardHorizontal;
};

/**
 * @brief Checks an array of ships to ensure valid positions (no collisions)
 *
 * Iterates through the whole array (all I check all further positions of J)
 * and checks for collisions
 * Note: Does not check the bounds of the board
 *
 * @param fleet an array of ship poisitions
 * @param fleetSize number of ships in the fleet
 * @return true if ships collide, else false
 */
bool areShipsValid(ShipPosition *fleet, int fleetSize){
    if(fleetSize == 0) return true;

    for (size_t i = 0; i < fleetSize-1; i++) {
        for (size_t j = i+1; j < fleetSize; j++) {
            if (doShipsCollide(fleet[i], fleet[j]))
                return false;
        }
    }

    return true;
}

/**
 * @brief checks the array of ships for colisions and ensures the boards fit in the bounds
 *
 * @param fleet the ships to check positional validity
 * @param fleetSize number of ships in fleet
 * @return true if no colisions or out of bounds
 */
bool areShipsValidInBoardArray(ShipPosition *fleet, int fleetSize){
    if(!areShipsValid(fleet, fleetSize)) return false; // if the ships colide

    // check each board doesn't extend past BOARD_SIZE
    for (size_t i = 0; i < fleetSize; i++){ // for each ship
        if (!doesShipFitOnBoard(fleet[i])) return false; //ship doesn't fit on board
    }

    return true;
}

bool areShipsValidInBoardVector(std::vector<ShipPosition> vectorFleet){
    ShipPosition arrayFleet[vectorFleet.size()];
    shipVectorToArray(vectorFleet, arrayFleet, vectorFleet.size());

    return areShipsValidInBoardArray(arrayFleet, vectorFleet.size());
}

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
 * @brief toString overload for ship bounding box
 * @param os a stream
 * @param shipPos given ship box
 * @return the stream
 */
std::ostream& operator<<(std::ostream& os,  const struct ShipBoundingBox& shipBox){

    os << "N:" << shipBox.north << " S: " << shipBox.south << " E:" << shipBox.east << " W: " << shipBox.west;

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
