#ifndef SHIPS_TESTS_H
#define SHIPS_TESTS_H

#include "ships.h"
#include "constants.h"
#include "test_utils.h"

void TEST_SHIP_singleShipPositions();
void TEST_SHIP_allShipPositions();
void TEST_SHIP_rndShipPos();

void TEST_SHIP_convertShipPositionToBoundingBox();
void TEST_SHIP_convertBoundingboxToShipPosition();

void TEST_SHIP_doShipsCollide();

void TEST_SHIP_operatorEqual();
void TEST_SHIP_operatorRelational();
void TEST_SHIPS_compareShipArray();

void TEST_SHIPS_nextShipPosition();
void TEST_SHIPS_nextShipPosArray();
void TEST_SHIPS_setStartArray();
void TEST_SHIPS_setEndArray();

#endif //SHIPS_TESTS_H