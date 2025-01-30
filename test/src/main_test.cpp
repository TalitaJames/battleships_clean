#include <stdio.h>
#include "test_utils.h"
#include "vector_tests.h"
#include "ships_tests.h"
#include "board_tests.h"

int main(){
    printf("\nTESTING VECTOR\n");
    TEST_VECTOR_INIT();
    TEST_VECTOR_APPEND();

    printf("\nTESTING SHIPS\n");
    TEST_SHIP_singleShipPositions();
    TEST_SHIP_allShipPositions();
    TEST_SHIP_rndShipPos();

    TEST_SHIP_convertShipPositionToBoundingBox();
    TEST_SHIP_convertBoundingboxToShipPosition();

    TEST_SHIP_doShipsCollide();

    printf("\nTESTING BOARD\n");
    TEST_BOARD_initBlankBoard();
    TEST_BOARD_wipeBoard();
    TEST_BOARD_drawBoard();
    TEST_BOARD_rndBoard();
    return 0;
}