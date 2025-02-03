#ifndef SHIPS_TESTS_H
#define SHIPS_TESTS_H

#include "ships.h"
#include "test_utils.h"

void TEST_SHIP_singleShipPositions();
void TEST_SHIP_allShipPositions();
void TEST_SHIP_rndShipPos();

void TEST_SHIP_convertShipPositionToBoundingBox();
void TEST_SHIP_convertBoundingboxToShipPosition();

void TEST_SHIP_doShipsCollide();

void TEST_SHIP_operatorEqual();
void TEST_SHIP_operatorRelational();

#endif //SHIPS_TESTS_H