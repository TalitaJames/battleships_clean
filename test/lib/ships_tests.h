#ifndef SHIPS_TESTS_H
#define SHIPS_TESTS_H

#include "ships.h"
#include "constants.h"
#include "test_utils.h"

bool TEST_SHIPS_singleShipPositions();
bool TEST_SHIPS_allShipPositions();
bool TEST_SHIPS_rndShipPos();

bool TEST_SHIPS_convertShipPositionToBoundingBox();
bool TEST_SHIPS_convertBoundingboxToShipPosition();
bool TEST_SHIPS_shipVectorToArray();

bool TEST_SHIPS_shipPosToInt();
bool TEST_SHIPS_intToShipPos();
bool TEST_SHIPS_shipArrayToLong();
bool TEST_SHIPS_longToShipArray();

bool TEST_SHIPS_doShipsCollide_shipPosition();
bool TEST_SHIPS_doShipsCollide_shipBoundingBox();
bool TEST_SHIPS_areShipsValid();
bool TEST_SHIPS_areShipsValidInBoardArray();
bool TEST_SHIPS_areShipsValidInBoardVector();

bool TEST_SHIPS_operatorEqual();
bool TEST_SHIPS_operatorRelational();
bool TEST_SHIPS_compareShipArray();

bool TEST_SHIPS_nextShipPosition();
bool TEST_SHIPS_nextShipPosArray();
bool TEST_SHIPS_setStartArray();
bool TEST_SHIPS_setEndArray();
bool TEST_SHIPS_setShipLengths();


#endif //SHIPS_TESTS_H