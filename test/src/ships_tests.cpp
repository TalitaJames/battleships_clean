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

}
void TEST_SHIP_rndShipPos(){

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
