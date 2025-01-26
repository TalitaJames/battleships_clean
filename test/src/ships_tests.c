#include "ships_tests.h"

// Test Ships
void TEST_SHIP_BOUNDINGBOX(){
    // Test conversion from a (major, minor, orientation) to a ShipPlacement box
    ShipPlacement testShip;
    testShip = makeShipFromMinMaxDir(4, 4, 3, 1);
    ASSERT(testShip.north == 4, "North expected 4");
    ASSERT(testShip.east == 6, "East expected 6");
    ASSERT(testShip.south == 4, "South expected 4");
    ASSERT(testShip.west == 3, "West expected 7");

    testShip = makeShipFromMinMaxDir(2, 2, 2, 0);
    ASSERT(testShip.north == 2, "North expected 2");
    ASSERT(testShip.east == 2, "East expected 2");
    ASSERT(testShip.south == 3, "South expected 3");
    ASSERT(testShip.west == 2, "West expected 2");

    testShip = makeShipFromMinMaxDir(3, 5, 7, 0);
    ASSERT(testShip.north == 7, "North expected 7");
    ASSERT(testShip.east == 5, "East expected 5");
    ASSERT(testShip.south == 9, "South expected 9");
    ASSERT(testShip.west == 5, "West expected 5");

    // printf("N%i, E%i, S%i, W%i\n", testShip.north, testShip.east, testShip.south, testShip.west);
    printf("\tPASSED Bounding Box\n");
}

void TEST_SHIP_COLLISIONS(){
    ShipPlacement shipA = {4,3,4,0};
    ShipPlacement shipB = {1,2,3,2};
    ASSERT(doShipsCollide(shipA,shipB) == false, "Ships A & B should not collide");
    ASSERT(doShipsCollide(shipB, shipA) == false, "Ships B & A should not collide");

    ShipPlacement shipC = {0,3,0,0};
    ASSERT(doShipsCollide(shipC,shipB) == false, "Ships C & B should not collide");
    ASSERT(doShipsCollide(shipB, shipC) == false, "Ships B & C should not collide");

    ShipPlacement shipD = {4,4,4,2};
    ShipPlacement shipE = {2,5,2,1};
    ASSERT(doShipsCollide(shipA,shipD) == true, "Ships A & E should collide");
    ASSERT(doShipsCollide(shipB,shipE) == true, "Ships B & E should collide");

    printf("\tPASSED Collisions\n");
}

