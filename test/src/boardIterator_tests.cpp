#include "boardIterator_tests.h"


bool TEST_BOARDITERATOR_dividePositions(){
    int threadCount = 4;
    std::vector<Worker> workerVector;

    dividePositions(threadCount, workerVector);
    ASSERT(workerVector.size() == threadCount, "Worker vector should be the same size as the threadCount");

    ShipPosition positionStart[FLEET_SIZE];
    ShipPosition positionEnd[FLEET_SIZE];
    setStartArray(positionStart);
    setEndArray(positionEnd);


    ASSERT(compareShipArray(workerVector[0].start, positionStart) == 0, "First worker should start at 0");
    for(int i = 0; i < threadCount-1; i++){
        ASSERT(compareShipArray(workerVector[i].end, workerVector[i+1].start) == 0, "Workers should be contiguous in start and end");
    }
    ASSERT(compareShipArray(workerVector.back().end, positionEnd) == 0, "Last worker should end at the end");

    ENDTEST();
}


bool TEST_BOARDITERATOR_appendWorkerToProbGrid() {
    ProbabilityGrid p = {};
    Worker w = {};
    w.sub_probGrid.totalGoodBoards = 5;
    w.sub_probGrid.shipGrid[0][0] = 10;
    w.sub_probGrid.infoGain[0][0] = 20;

    appendWorkerToProbGrid(p, w);

    ASSERT(p.totalGoodBoards == 5, "appendWorkerToProbGrid should correctly sum totalGoodBoards");
    ASSERT(p.shipGrid[0][0] == 10, "appendWorkerToProbGrid should correctly sum shipGrid");
    ASSERT(p.infoGain[0][0] == 20, "appendWorkerToProbGrid should correctly sum infoGain");

    ENDTEST();
}

bool TEST_BOARDITERATOR_gatherProbabilityFromWorkers() {
    ProbabilityGrid p = {};
    Worker w1 = {};
    Worker w2 = {};
    w1.sub_probGrid.totalGoodBoards = 5;
    w1.sub_probGrid.shipGrid[0][0] = 10;
    w1.sub_probGrid.infoGain[0][0] = 20;

    w2.sub_probGrid.totalGoodBoards = 3;
    w2.sub_probGrid.shipGrid[0][0] = 15;
    w2.sub_probGrid.infoGain[0][0] = 25;

    std::vector<Worker> sweatshop = {w1, w2};

    gatherProbabilityFromWorkers(p, sweatshop);

    ASSERT(p.totalGoodBoards == 8, "gatherProbabilityFromWorkers should correctly sum totalGoodBoards");
    ASSERT(p.shipGrid[0][0] == 25, "gatherProbabilityFromWorkers should correctly sum shipGrid");
    ASSERT(p.infoGain[0][0] == 45, "gatherProbabilityFromWorkers should correctly sum infoGain");

    ENDTEST();
}
