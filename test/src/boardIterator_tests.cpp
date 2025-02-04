#include "boardIterator_tests.h"


void TEST_BOARDITERATOR_dividePositions(){
    int threadCount = 4;
    std::vector<Worker> workerVector;

    for (int threadCount = 1; threadCount < 64; threadCount++) {
        dividePositions(threadCount, workerVector);
        ASSERT(workerVector.size() == threadCount, "Worker vector should be the same size as the threadCount");
    }

    printf("\tPASSED dividePositions\n");
}


void TEST_BOARDITERATOR_appendWorkerToProbGrid() {
    ProbabilityGrid p = {};
    Worker w = {};
    w.sub_probGrid.totalGoodBoards = 5;
    w.sub_probGrid.shipGrid[0][0] = 10;
    w.sub_probGrid.infoGain[0][0] = 20;

    appendWorkerToProbGrid(p, w);

    ASSERT(p.totalGoodBoards == 5, "appendWorkerToProbGrid should correctly sum totalGoodBoards");
    ASSERT(p.shipGrid[0][0] == 10, "appendWorkerToProbGrid should correctly sum shipGrid");
    ASSERT(p.infoGain[0][0] == 20, "appendWorkerToProbGrid should correctly sum infoGain");

    printf("\tPASSED appendWorkerToProbGrid\n");
}

void TEST_BOARDITERATOR_gatherProbabilityFromWorkers() {
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

    printf("\tPASSED gatherProbabilityFromWorkers\n");
}
