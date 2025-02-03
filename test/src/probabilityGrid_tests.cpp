#include "probabilityGrid_tests.h"

void TEST_PROBABILITYGRID_initProbabilityGrid() {
    ProbabilityGrid p;
    ASSERT(p.totalGoodBoards == 0, "totalGoodBoards should start with value of 0");

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            ASSERT(p.shipGrid[x][y] == 0, "shipGrid should start with value of 0");
            ASSERT(p.shipProb[x][y] == 0, "shipProb should start with value of 0");
            ASSERT(p.pChange[x][y] == 0, "pChange should start with value of 0");
            ASSERT(p.infoGain[x][y] == 0, "infoGain should start with value of 0");
        }
    }

    printf("\tPASSED initProbabilityGrid\n");
}

void TEST_PROBABILITYGRID_calcProbabilityGrid() {
    ProbabilityGrid p;

    // Give it some numbers
    p.totalGoodBoards = 10;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            p.shipGrid[x][y] = (2*x + y) % 3;
        }
    }

    // Call the function to calculate probabilities
    calcProbabilityGrid(p);

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            double expectedProb = static_cast<double>(p.shipGrid[x][y]) / static_cast<double>(p.totalGoodBoards);
            double expectedPChange = pow(expectedProb, 2) + pow(1 - expectedProb, 2);

            ASSERT(fabs(p.shipProb[x][y] - expectedProb) < 1e-6, "Probability calculation is incorrect");
            ASSERT(fabs(p.pChange[x][y] - expectedPChange) < 1e-6, "Probability change calculation is incorrect");
        }
    }
    printf("\tPASSED calcProbabilityGrid\n");
}

