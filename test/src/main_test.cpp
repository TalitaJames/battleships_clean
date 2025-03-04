#include <stdio.h>
#include "test_utils.h"
#include "ships_tests.h"
#include "board_tests.h"
#include "hitmask_tests.h"
#include "probabilityGrid_tests.h"
#include "boardIterator_tests.h"
#include "cartesianProduct_tests.h"

int main(){
    bool testResult;

    std::vector<TestFunction> testShips = {
        TEST_SHIPS_singleShipPositions,
        TEST_SHIPS_allShipPositions,
        TEST_SHIPS_rndShipPos,

        TEST_SHIPS_convertShipPositionToBoundingBox,
        TEST_SHIPS_convertBoundingboxToShipPosition,
        TEST_SHIPS_shipVectorToArray,

        TEST_SHIPS_shipPosToInt,
        TEST_SHIPS_intToShipPos,
        TEST_SHIPS_shipArrayToLong,
        TEST_SHIPS_longToShipArray,

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
        TEST_SHIPS_setShipLengths,
    };
    testResult = TEST_ALL(testShips, "Ships");
    if (!testResult) return 1;

    std::vector<TestFunction> testBoard = {
        TEST_BOARD_initBlankBoard,
        TEST_BOARD_wipeBoard,
        TEST_BOARD_drawBoard,
        TEST_BOARD_rndBoard,
    };
    testResult = TEST_ALL(testBoard, "Board");
    if (!testResult) return 1;

    std::vector<TestFunction> testHistmask = {
        TEST_HITMASK_initHitmask,
        TEST_HITMASK_hitBoard,
        TEST_HITMASK_findHitmaskDifference,
        TEST_HITMASK_howManyTurnsTaken,
        TEST_HITMASK_checkCompatible,
        // TEST_HITMASK_turnsToShotmask,
        TEST_HITMASK_isHitmaskSolved,
        TEST_HITMASK_isHit,
        TEST_HITMASK_operatorEqual,
    };
    testResult = TEST_ALL(testHistmask, "Histmask");
    if (!testResult) return 1;

    std::vector<TestFunction> testProbabilityGrid = {
        TEST_PROBABILITYGRID_initProbabilityGrid,
        TEST_PROBABILITYGRID_calcProbabilityGrid,
        TEST_PROBABILITYGRID_flattenBoardToProbabilityGrid,
        TEST_PROBABILITYGRID_clearProbabilityGrid,
    };
    testResult = TEST_ALL(testProbabilityGrid, "ProbabilityGrid");
    if (!testResult) return 1;

    std::vector<TestFunction> testBoardIterator = {
        TEST_BOARDITERATOR_dividePositions,
        TEST_BOARDITERATOR_appendWorkerToProbGrid,
        TEST_BOARDITERATOR_gatherProbabilityFromWorkers,
        TEST_BOARDITERATOR_checkThenUpdateVectorOfBoards,
    };
    testResult = TEST_ALL(testBoardIterator, "BoardIterator");
    if (!testResult) return 1;

    std::vector<TestFunction> testCartesianProduct = {
        TEST_CARTESIANPRODUCT_cartesianProduct_singleVector,
        TEST_CARTESIANPRODUCT_cartesianProduct_singleVector_filter,
        TEST_CARTESIANPRODUCT_cartesianProduct_twoVector,
        TEST_CARTESIANPRODUCT_cartesianProduct_twoVector_filter,
        TEST_CARTESIANPRODUCT_cartesianProduct_VectorsAndVector,
        TEST_CARTESIANPRODUCT_cartesianProduct_VectorsAndVector_filter,
    };
    testResult = TEST_ALL(testCartesianProduct, "CartesianProduct");
    if (!testResult) return 1;

    return 0;
}