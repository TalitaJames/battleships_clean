#include "ships_tests.h"
#include <set>

bool TEST_SHIPS_singleShipPositions(){
    ASSERT(singleShipPositions(5, 3).size() == 30, "The wrong number of ships for a size 3 on a 5x5 board");
    ASSERT(singleShipPositions(5, 5).size() == 10, "The wrong number of ships for a size 5 on a 5x5 board");
    ASSERT(singleShipPositions(10, 1).size() == 100, "The wrong number of ships for a size 1 on a 10x10 board");
    ASSERT(singleShipPositions(7, 0).size() == 0, "A zero size ship shouldn't have any ship positions");
    ASSERT(singleShipPositions(10, 2).size() == 180, "2 size ship on 10x10 should be 180");
    ASSERT(singleShipPositions(8, 201).size() == 0, "Ships bigger than the board shouldn't have any ship positions");
    ASSERT(singleShipPositions(7, -20).size() == 0, "A negative size ship shouldn't have any ship positions");

    //TODO would a test to check contents?
    // (Possibly put all in a set and check same size, ie no duplicates)

    ENDTEST();
}

bool TEST_SHIPS_allShipPositions(){
    Ship testFleetSingle[] = {2};
    auto resultFleetSingle = allShipPositions(10, testFleetSingle, 1);
    ASSERT(resultFleetSingle.size() == 1, "A single ship should have only one vector of ship positions");
    ASSERT(resultFleetSingle[0].size() == 180, "The single ship first element shound contain the correct number of ship positions");

    Ship testFleetMultiple[] = {4, 7, 5};
    auto resultFleetMultiple = allShipPositions(10, testFleetMultiple, 3);
    ASSERT(resultFleetMultiple.size() == 3, "Many ships should return a vector the same size as the number of input ships");
    ASSERT(resultFleetMultiple[0].size() == 140, "The first element should contain correct number of ships for the first ship");
    ASSERT(resultFleetMultiple[1].size() == 80, "The seccond element should contain correct number of ships for the seccond ship");
    ASSERT(resultFleetMultiple[2].size() == 120, "The third element should contain correct number of ships for the third ship");


    ENDTEST();
}

bool TEST_SHIPS_rndShipPos() {
    int boardSize = 10;

    int numberOfRndShips = 5;
    ShipPosition ships[numberOfRndShips];

    for (size_t i = 0; i < numberOfRndShips; i++) {
        ships[i] = rndShipPos(boardSize, 5);
        ASSERT(ships[i].x >= 0 && ships[i].x < boardSize, "Ship x position should be within board bounds");
        ASSERT(ships[i].y >= 0 && ships[i].y < boardSize, "Ship y position should be within board bounds");
    }

    // compare all the ships to ensure each random ship is distinct
    bool isRandom = false;
    for (size_t i = 0; i < numberOfRndShips - 1; i++) {
        for (size_t j = i + 1; j < numberOfRndShips; j++) {
            if (ships[i].x != ships[j].x || ships[i].y != ships[j].y) {
                isRandom = true;
                break;
            }
        }
        if (isRandom) break;
    }

    ASSERT(isRandom, "Ship positions should be random");

    ENDTEST();
}

bool TEST_SHIPS_convertShipPositionToBoundingBox(){

    // Test conversion from a ship position (with len, x, y, direction) to a ShipBoundingBox (with cardinal directions)
    ShipBoundingBox testShip;
    ShipPosition shipA = {4, 3, 4, 1};
    testShip = convertShipPositionToBoundingBox(shipA);
    ASSERT(testShip.north == 4, "North expected 4");
    ASSERT(testShip.east == 6, "East expected 6");
    ASSERT(testShip.south == 4, "South expected 4");
    ASSERT(testShip.west == 3, "West expected 3");

    ShipPosition shipB = {2, 2, 2, 0};
    testShip = convertShipPositionToBoundingBox(shipB);
    ASSERT(testShip.north == 2, "North expected 2");
    ASSERT(testShip.east == 2, "East expected 2");
    ASSERT(testShip.south == 3, "South expected 3");
    ASSERT(testShip.west == 2, "West expected 2");

    ShipPosition shipC = {3, 5, 7, 0};
    testShip = convertShipPositionToBoundingBox(shipC);
    ASSERT(testShip.north == 7, "North expected 7");
    ASSERT(testShip.east == 5, "East expected 5");
    ASSERT(testShip.south == 9, "South expected 9");
    ASSERT(testShip.west == 5, "West expected 5");

    ShipPosition shipD = {1, 0, 0, 0};
    testShip = convertShipPositionToBoundingBox(shipD);
    ASSERT(testShip.north == 0, "North expected 0");
    ASSERT(testShip.east == 0, "East expected 0");
    ASSERT(testShip.south == 0, "South expected 0");
    ASSERT(testShip.west == 0, "West expected 0");

    // printf("N%i, E%i, S%i, W%i\n", testShip.north, testShip.east, testShip.south, testShip.west);
    ENDTEST();
}

bool TEST_SHIPS_convertBoundingboxToShipPosition(){

    // Test conversion from a bounding box (north, south, east, west) to a ship position
    ShipPosition testShip;
    ShipBoundingBox shipA = {4, 6, 4, 3};
    testShip = convertBoundingboxToShipPosition(shipA);
    ASSERT(testShip.length == 4, "length expected 4");
    ASSERT(testShip.x == 3, "x expected 3");
    ASSERT(testShip.y == 4, "y expected 4");
    ASSERT(testShip.direction == 1, "direction expected 1");

    ShipBoundingBox shipB = {2, 2, 3, 2};
    testShip = convertBoundingboxToShipPosition(shipB);
    ASSERT(testShip.length == 2, "length expected 2");
    ASSERT(testShip.x == 2, "x expected 2");
    ASSERT(testShip.y == 2, "y expected 2");
    ASSERT(testShip.direction == 0, "direction expected 0");

    ShipBoundingBox shipC = {7, 5, 9, 5};
    testShip = convertBoundingboxToShipPosition(shipC);
    ASSERT(testShip.length == 3, "length expected 3");
    ASSERT(testShip.x == 5, "x expected 5");
    ASSERT(testShip.y == 7, "y expected 7");
    ASSERT(testShip.direction == 0, "direction expected 0");

    ShipBoundingBox shipD = {0, 0, 0, 0};
    testShip = convertBoundingboxToShipPosition(shipD);
    ASSERT(testShip.length == 1, "length expected 0");
    ASSERT(testShip.x == 0, "x expected 0");
    ASSERT(testShip.y == 0, "y expected 0");
    ASSERT(testShip.direction == 0, "direction expected 0");

    ENDTEST();
}

bool TEST_SHIPS_shipVectorToArray() {
    // Test with an empty vector
    std::vector<ShipPosition> emptyFleetVector = {};
    ShipPosition emptyFleetArray[emptyFleetVector.size()];
    shipVectorToArray(emptyFleetVector, emptyFleetArray, emptyFleetVector.size());
    ASSERT(emptyFleetVector.size() == 0, "Empty vector should result in an empty array");

    // Test with a single ship
    std::vector<ShipPosition> singleShipVector = {{3, 2, 1, true}};
    ShipPosition singleShipArray[singleShipVector.size()];
    shipVectorToArray(singleShipVector, singleShipArray, singleShipVector.size());
    ASSERT(singleShipArray[0] == singleShipVector[0], "Expected the two ships to be equal");

    // Test with multiple ships
    std::vector<ShipPosition> multipleShipsVector = {
        {4, 3, 4, false},
        {2, 5, 6, true},
        {5, 1, 2, false}
    };
    ShipPosition multipleShipsArray[multipleShipsVector.size()];
    shipVectorToArray(multipleShipsVector, multipleShipsArray, multipleShipsVector.size());
    ASSERT(multipleShipsArray[0] == multipleShipsVector[0], "Expected the two ships to be equal");
    ASSERT(multipleShipsArray[1] == multipleShipsVector[1], "Expected the two ships to be equal");
    ASSERT(multipleShipsArray[2] == multipleShipsVector[2], "Expected the two ships to be equal");

    ENDTEST();
}

bool TEST_SHIPS_doShipsCollide_shipPosition(){
    // Ship Position method
    ShipPosition shipZ = {5, 6, 5, 0};
    ShipPosition shipX = {3, 2, 0, 0};
    ShipPosition shipY = {2, 5, 5, 1};

    ASSERT(doShipsCollide(shipZ, shipX) == false, "Ships with Position Z & X should not collide");
    ASSERT(doShipsCollide(shipX, shipZ) == false, "Ships with Position X & Z should not collide");
    ASSERT(doShipsCollide(shipZ, shipY) == true, "Ships with Position Z & Y should collide");
    ENDTEST();
}

bool TEST_SHIPS_doShipsCollide_shipBoundingBox(){
    // Calling the bounding box method
    ShipBoundingBox shipA = {4,3,4,0};
    ShipBoundingBox shipB = {1,2,3,2};
    ASSERT(doShipsCollide(shipA, shipB) == false, "Ships with BoundingBoxes A & B should not collide");
    ASSERT(doShipsCollide(shipB, shipA) == false, "Ships with BoundingBoxes B & A should not collide");

    ShipBoundingBox shipC = {0,3,0,0};
    ASSERT(doShipsCollide(shipC, shipB) == false, "Ships with BoundingBoxes C & B should not collide");
    ASSERT(doShipsCollide(shipB, shipC) == false, "Ships with BoundingBoxes B & C should not collide");

    ShipBoundingBox shipD = {4,4,4,2};
    ShipBoundingBox shipE = {2,5,2,1};
    ASSERT(doShipsCollide(shipA, shipD) == true, "Ships with BoundingBoxes A & E should collide");
    ASSERT(doShipsCollide(shipB, shipE) == true, "Ships with BoundingBoxes B & E should collide");

    ENDTEST();
}

bool TEST_SHIPS_areShipsValid() {

    ASSERT(BOARD_SIZE <= 11, "The board must be less than 11x11 to do these tests");

    // Test with valid ships
    ShipPosition validFleet[] = {
        {4, 0, 0, true},
        {3, 2, 2, false},
        {2, 5, 5, true}
    };
    ASSERT(areShipsValid(validFleet, 3), "Valid fleet should be considered valid");

    // Test with overlapping ships
    ShipPosition overlappingFleet[] = {
        {4, 0, 0, true},
        {3, 0, 0, false},
        {2, 5, 5, true}
    };
    ASSERT(!areShipsValid(overlappingFleet, 3), "Overlapping fleet should be considered invalid");

    // Test with an empty fleet
    ShipPosition emptyFleet[] = {};
    ASSERT(areShipsValid(emptyFleet, 0), "Empty fleet should be considered valid");

    // Test with a single valid ship
    ShipPosition singleValidShip[] = {
        {10, 0, 0, true}
    };
    ASSERT(areShipsValid(singleValidShip, 1), "Single valid ship should be considered valid");

    ENDTEST();
}

bool TEST_SHIPS_areShipsValidInBoardArray() {
    // Test with valid ships
    ShipPosition validFleet[] = {
        {4, 0, 0, true},
        {3, 2, 2, true},
        {2, 1, 1, true}
    };
    ASSERT(areShipsValidInBoardArray(validFleet, 3), "Valid fleet should be considered valid");

    // Test with overlapping ships
    ShipPosition overlappingFleet[] = {
        {4, 0, 0, true},
        {3, 0, 0, false},
        {2, 5, 5, true}
    };
    ASSERT(!areShipsValidInBoardArray(overlappingFleet, 3), "Overlapping fleet should be considered invalid");

    // Test with ships out of bounds
    ShipPosition outOfBoundsFleet[] = {
        {107, 0, 0, false},
        {2, 5, 5, true}
    };
    ASSERT(!areShipsValidInBoardArray(outOfBoundsFleet, 2), "Fleet with ships out of bounds should be considered invalid");

    // Test with an empty fleet
    ShipPosition emptyFleet[] = {};
    ASSERT(areShipsValidInBoardArray(emptyFleet, 0), "Empty fleet should be considered valid");

    // Test with a single valid ship
    ShipPosition singleValidShip[] = {
        {4, 0, 0, true}
    };
    ASSERT(areShipsValidInBoardArray(singleValidShip, 1), "Single valid ship should be considered valid");

    // Test with a single invalid ship (out of bounds)
    ShipPosition singleInvalidShip[] = {
        {4, 10, 10, true}
    };
    ASSERT(!areShipsValidInBoardArray(singleInvalidShip, 1), "Single invalid ship should be considered invalid");

    ENDTEST();
}

bool TEST_SHIPS_areShipsValidInBoardVector(){
    std::vector<ShipPosition> validShips = {
        {2, 2, 3, false},
        {3, 0, 1, true},
    };
    ASSERT(areShipsValidInBoardVector(validShips), "These ships should be valid");


    std::vector<ShipPosition> outOfBounds = {
        {2, 2, 3, false},
        {4, 4, 1, true},
        {2, 2, 5, true},
        {10, 9, 7, false},
        {5, 0, 8, true}
    };
    ASSERT(!areShipsValidInBoardVector(outOfBounds), "Ships are not valid when they're out of bounds");

    std::vector<ShipPosition> collision = {
        {4, 4, 1, true},
        {2, 2, 5, true},
        {3, 2, 3, false},
    };
    ASSERT(!areShipsValidInBoardVector(collision), "Ships should collide");

    std::vector<ShipPosition> fleet = {};
    ASSERT(areShipsValidInBoardVector(fleet), "Empty fleet should be valid");

    ENDTEST();
}

bool TEST_SHIPS_operatorEqual(){
    // Test if two ship positions are equal
    ShipPosition shipA = {4, 3, 4, 1};
    ShipPosition shipB = {4, 3, 4, 1};

    ShipPosition shipC = {4, 3, 4, 0};
    ShipPosition shipD = {3, 3, 4, 1};
    ShipPosition shipE = {4, 2, 4, 1};
    ShipPosition shipF = {4, 3, 0, 1};

    ASSERT(shipA == shipB, "Ships with the same information should be equal");
    ASSERT(shipA != shipC, "Ships going different directions shouldn't be equal");
    ASSERT(shipA == shipD, "Ships with different lengths at the same position are still considered equal");
    ASSERT(shipA != shipE, "Ships with x positions lengths shouldn't be equal");
    ASSERT(shipA != shipF, "Ships with y positions lengths shouldn't be equal");


    ENDTEST();
}

bool TEST_SHIPS_operatorRelational(){
    // Test if two ship positions are equal
    ShipPosition shipA = {4, 3, 4, 1};
    ShipPosition shipB = {4, 3, 4, 1};

    ShipPosition shipC = {4, 3, 4, 0};
    ShipPosition shipD = {4, 3, 3, 1};
    ShipPosition shipE = {4, 5, 4, 1};
    ShipPosition shipF = {2, 3, 4, 1};

    ASSERT((shipA < shipB) == false, "Identifal ships should not be less than each other");
    ASSERT((shipA > shipB) == false, "Identifal ships should not be greater than each other");

    ASSERT((shipA > shipC) == true, "A ship in the same position in different directions should be greater than the other");
    ASSERT((shipA < shipC) == false, "A ship in the same position in different directions should be greater than the other (2)");

    ASSERT((shipA < shipD) == false, "A ship in the above the other should be less than");
    ASSERT((shipA > shipD) == true, "A ship in the above the other should be less than (2)");

    ASSERT((shipA < shipE) == true, "A ship in the same row further along should be greater than");
    ASSERT((shipA > shipE) == false, "A ship in the same row further along should be greater than (2)");

    ASSERT((shipA < shipF) == false, "Equal positioned ships with different lengths are still considered equal");
    ASSERT((shipA > shipF) == false, "Equal positioned ships with different lengths are still considered equal (2)");


    ENDTEST();
}

bool TEST_SHIPS_compareShipArray() {
    ShipPosition pA[FLEET_SIZE];
    ShipPosition pB[FLEET_SIZE];

    // Initialize pA and pB with some values
    for (int i = 0; i < FLEET_SIZE; i++) {
        pA[i] = {(unsigned int)i, i, i, true};
        pB[i] = {(unsigned int)i, i, i, true};
    }

    // pA == pB
    int result = compareShipArray(pA, pB);
    ASSERT(result == 0, "compareShipArray should return 0 when arrays are equal");

    // pA > pB
    pA[0] = {1, 1, 2, true}; // Make pA greater than pB
    result = compareShipArray(pA, pB);
    ASSERT(result == -1, "compareShipArray should return -1 when pA > pB");

    // pA < pB
    pA[0] = {0, 0, 0, true}; // Reset pA
    pB[1] = {1, 1, 2, true}; // Make pB greater than pA
    result = compareShipArray(pA, pB);
    ASSERT(result == 1, "compareShipArray should return 1 when pA < pB");

    ENDTEST();
}

bool TEST_SHIPS_nextShipPosition() {
    ASSERT(BOARD_SIZE > 4, "Board size must be greater than 4 for valid tests");

    // just change y (no rollover)
    ShipPosition shipPos = {0, 0, 2, true};
    nextShipPosition(shipPos);
    ASSERT(shipPos.x == 0, "Expected x to be 0 when changing y");
    ASSERT(shipPos.y == 3, "Expected y to be 0 when changing y");
    ASSERT(shipPos.direction == true, "Expected direction to be true when changing y");

    // just change x
    shipPos.y = BOARD_SIZE - 1;
    nextShipPosition(shipPos);
    ASSERT(shipPos.x == 1, "Expected x to be 1 when changing x");
    ASSERT(shipPos.y == 0, "Expected y to be 0 when changing x");
    ASSERT(shipPos.direction == true, "Expected direction to be true when changing x");

    // xy at max and direction changes
    ShipPosition xyRollover = {2, BOARD_SIZE-1, BOARD_SIZE-1, false};
    nextShipPosition(xyRollover);
    ASSERT(xyRollover.x == 0, "Expected x to be 0 when changing direction");
    ASSERT(xyRollover.y == 0, "Expected y to be 0 when changing direction");
    ASSERT(xyRollover.direction == true, "Expected direction to be true when changing direction");

    // xy at max and direction rollover to begining
    ShipPosition finalShipPos = {1, BOARD_SIZE-1, BOARD_SIZE-1, true};
    nextShipPosition(finalShipPos);
    ASSERT(finalShipPos.x == 0, "Expected x to be 0 when rolling over x,y,direction");
    ASSERT(finalShipPos.y == 0, "Expected y to be 0 when rolling over x,y,direction");
    ASSERT(finalShipPos.direction == false, "Expected direction to be false when rolling over x,y,direction");

    ENDTEST();
}

bool TEST_SHIPS_nextShipPosArray() {
    ShipPosition shipPosArray[FLEET_SIZE];
    setStartArray(shipPosArray);
    nextShipPosArray(shipPosArray);
    ASSERT(shipPosArray[FLEET_SIZE-1].x == 0, "Expected x to be 0");
    ASSERT(shipPosArray[FLEET_SIZE-1].y == 1, "Expected y to be 1");
    ASSERT(shipPosArray[FLEET_SIZE-1].direction == 0, "Expected direction to be 0");

    //set the whole array to the end value
    for (int i = 0; i < FLEET_SIZE; i++) {
        shipPosArray[i] = {FLEET[i], (int)(BOARD_SIZE - FLEET[i] + 1), (int)(BOARD_SIZE - 1), 1};
    }
    nextShipPosArray(shipPosArray);
    for (int i = 0; i < FLEET_SIZE; i++) {
        ASSERT(shipPosArray[i].x == 0, "Expected x to be 0");
        ASSERT(shipPosArray[i].y == 0, "Expected y to be 0");
        ASSERT(shipPosArray[i].direction == 0, "Expected direction to be 0");
    }

    ENDTEST();
}

bool TEST_SHIPS_setStartArray() {
    ShipPosition shipPosArray[FLEET_SIZE];
    setStartArray(shipPosArray);

    for (size_t i = 0; i < FLEET_SIZE; i++) {
        ASSERT(shipPosArray[i].length == FLEET[i], "Expected length to match FLEET");
        ASSERT(shipPosArray[i].x == 0, "Expected x to be 0");
        ASSERT(shipPosArray[i].y == 0, "Expected y to be 0");
        ASSERT(shipPosArray[i].direction == 0, "Expected direction to be 0");
    }

    ENDTEST();
}

bool TEST_SHIPS_setEndArray() {
    ShipPosition shipPosArray[FLEET_SIZE];
    setEndArray(shipPosArray);

    for (size_t i = 0; i < FLEET_SIZE; i++) {
        ASSERT(shipPosArray[i].length == FLEET[i], "Expected length to match FLEET");
        ASSERT(shipPosArray[i].x == BOARD_SIZE - FLEET[i], "Expected x to match BOARD_SIZE - FLEET[i]");
        ASSERT(shipPosArray[i].y == BOARD_SIZE - 1, "Expected y to be BOARD_SIZE - 1");
        ASSERT(shipPosArray[i].direction == 1, "Expected direction to be 1");
    }

    ENDTEST();
}
