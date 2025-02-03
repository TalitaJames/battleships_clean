#include "ships_tests.h"
#include <set>

void TEST_SHIP_singleShipPositions(){
    BoardDimensions fiveSquare = {5,5};
    BoardDimensions tenSquare = {10, 10};

    std::vector<ShipPosition> allShips_3in5 = singleShipPositions(fiveSquare, 3);
    std::vector<ShipPosition> allShips_5in5 = singleShipPositions(fiveSquare, 5);
    std::vector<ShipPosition> allShips_1in10 = singleShipPositions(tenSquare, 1);


    ASSERT(allShips_3in5.size() == 30, "The wrong number of ships for a size 3 on a 5x5 board");
    ASSERT(allShips_5in5.size() == 10, "The wrong number of ships for a size 5 on a 5x5 board");
    ASSERT(allShips_1in10.size() == 100, "The wrong number of ships for a size 1 on a 10x10 board");

    printf("\tPASSED singleShipPositions\n");
}
void TEST_SHIP_allShipPositions(){
    printf("\tNOT IMPLEMENTED allShipPositions\n");
}

void TEST_SHIP_rndShipPos() {
    BoardDimensions boardSize = {10, 10};

    int numberOfRndShips = 5;
    ShipPosition ships[numberOfRndShips];

    for (size_t i = 0; i < numberOfRndShips; i++) {
        ships[i] = rndShipPos(boardSize, 5);
        ASSERT(ships[i].x >= 0 && ships[i].x < boardSize.width, "Ship x position should be within board bounds");
        ASSERT(ships[i].y >= 0 && ships[i].y < boardSize.height, "Ship y position should be within board bounds");
    }

    // check all the ships are being generated in different positions
    bool isRandom = false;
    for (size_t i = 0; i < numberOfRndShips; i++) {
        for (size_t j = i + 1; j < numberOfRndShips; j++) {
            if (ships[i].x != ships[j].x || ships[i].y != ships[j].y) {
                isRandom = true;
                break;
            }
        }
        if (isRandom) break;
    }

    ASSERT(isRandom, "Ship positions should be random");

    printf("\tPASSED rndShipPos\n");
}

void TEST_SHIP_convertShipPositionToBoundingBox(){

    // Test conversion from a (major, minor, orientation) to a ShipPlacement box
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
    printf("\tPASSED convertShipPositionToBoundingBox\n");
}

void TEST_SHIP_convertBoundingboxToShipPosition(){

}

void TEST_SHIP_doShipsCollide(){
    // Ship Position method
    ShipPosition shipZ = {5, 6, 5, 0};
    ShipPosition shipX = {3, 2, 0, 0};
    ShipPosition shipY = {2, 5, 5, 1};

    ASSERT(doShipsCollide(shipZ, shipX) == false, "Ships with Position Z & X should not collide");
    ASSERT(doShipsCollide(shipX, shipZ) == false, "Ships with Position X & Z should not collide");
    ASSERT(doShipsCollide(shipZ, shipY) == true, "Ships with Position Z & Y should collide");

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

    printf("\tPASSED doShipsCollide\n");
}


void TEST_SHIP_operatorEqual(){
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


    printf("\tPASSED operatorEqual\n");
}

void TEST_SHIP_operatorRelational(){
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


    printf("\tPASSED operatorRelational\n");

}