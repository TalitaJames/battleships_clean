#include <stdio.h>
#include "test_utils.h"
#include "ships_tests.h"
#include "board_tests.h"
#include "hitmask_tests.h"
#include "probabilityGrid_tests.h"
#include "boardIterator_tests.h"
#include "cartesianProduct_tests.h"

int main(){
    std::vector<TestFunction> testShips = {
        TEST_SHIPS_singleShipPositions,
        TEST_SHIPS_allShipPositions,
        TEST_SHIPS_rndShipPos,

        TEST_SHIPS_convertShipPositionToBoundingBox,
        TEST_SHIPS_convertBoundingboxToShipPosition,
        TEST_SHIPS_shipVectorToArray,

        TEST_SHIPS_doShipsCollide_shipPosition,
        TEST_SHIPS_doShipsCollide_shipBoundingBox,
        TEST_SHIPS_areShipsValid,
        TEST_SHIPS_areShipsValidInBoardArray,
        TEST_SHIPS_areShipsValidInBoardVector,

        TEST_SHIPS_operatorEqual,
        TEST_SHIPS_operatorRelational,
        TEST_SHIPS_compareShipArray,

        TEST_SHIPS_nextShipPosition,
        TEST_SHIPS_nextShipPosArray,
        TEST_SHIPS_setStartArray,
        TEST_SHIPS_setEndArray,
    };
    TEST_ALL(testShips, "Ships");

    // printf("\nTESTING BOARD\n");
    std::vector<TestFunction> testBoard = {
        TEST_BOARD_initBlankBoard,
        TEST_BOARD_wipeBoard,
        TEST_BOARD_drawBoard,
        TEST_BOARD_rndBoard,
    };
    TEST_ALL(testBoard, "Board");

    // printf("\nTESTING HITMASK\n");
    // TEST_HITMASK_initHitmask();
    // TEST_HITMASK_hitBoard();
    // TEST_HITMASK_findHitmaskDifference();
    // TEST_HITMASK_howManyTurnsTaken();
    // TEST_HITMASK_checkCompatible();
    // TEST_HITMASK_turnsToShotmask();
    // TEST_HITMASK_isHitmaskSolved();
    // TEST_HITMASK_isHit();
    // TEST_HITMASK_operatorEqual();

    // printf("\nTESTING PROBABILITYGRID\n");
    // TEST_PROBABILITYGRID_initProbabilityGrid();
    // TEST_PROBABILITYGRID_calcProbabilityGrid();

    // printf("\nTESTING BOARDITERATOR\n");
    // TEST_BOARDITERATOR_dividePositions();
    // TEST_BOARDITERATOR_appendWorkerToProbGrid();
    // TEST_BOARDITERATOR_gatherProbabilityFromWorkers();

    // printf("\nTESTING CARTESIANPRODUCT\n");
    // TEST_CARTESIANPRODUCT_vectorIntoVectorVector();
    // TEST_CARTESIANPRODUCT_cartesianProduct();

    return 0;
}