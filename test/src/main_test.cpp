#include <stdio.h>
#include "test_utils.h"
#include "ships_tests.h"
#include "board_tests.h"
#include "hitmask_tests.h"
#include "probabilityGrid_tests.h"
#include "boardIterator_tests.h"

int main(){
    printf("\nTESTING SHIPS\n");
    TEST_SHIP_singleShipPositions();
    TEST_SHIP_allShipPositions();
    TEST_SHIP_rndShipPos();
    TEST_SHIP_convertShipPositionToBoundingBox();
    TEST_SHIP_convertBoundingboxToShipPosition();
    TEST_SHIP_doShipsCollide();
    TEST_SHIP_operatorEqual();
    TEST_SHIP_operatorRelational();
    TEST_SHIPS_nextShipPosition();
    TEST_SHIPS_nextShipPosArray();
    TEST_SHIPS_setStartArray();
    TEST_SHIPS_setEndArray();
    TEST_SHIPS_compareShipArray();

    printf("\nTESTING BOARD\n");
    TEST_BOARD_initBlankBoard();
    TEST_BOARD_wipeBoard();
    TEST_BOARD_drawBoard();
    TEST_BOARD_rndBoard();

    printf("\nTESTING HITMASK\n");
    TEST_HITMASK_initHitmask();
    TEST_HITMASK_hitBoard();
    TEST_HITMASK_findHitmaskDifference();
    TEST_HITMASK_howManyTurnsTaken();
    TEST_HITMASK_checkCompatible();
    TEST_HITMASK_turnsToShotmask();
    TEST_HITMASK_isHitmaskSolved();
    TEST_HITMASK_isHit();
    TEST_HITMASK_operatorEqual();

    printf("\nTESTING PROBABILITYGRID\n");
    TEST_PROBABILITYGRID_initProbabilityGrid();
    TEST_PROBABILITYGRID_calcProbabilityGrid();

    printf("\nTESTING BOARDITERATOR\n");
    TEST_BOARDITERATOR_dividePositions();
    TEST_BOARDITERATOR_appendWorkerToProbGrid();
    TEST_BOARDITERATOR_gatherProbabilityFromWorkers();


    return 0;
}