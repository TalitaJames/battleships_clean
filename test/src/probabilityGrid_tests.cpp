#include "probabilityGrid_tests.h"

bool TEST_PROBABILITYGRID_initProbabilityGrid() {
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

    ENDTEST();
}

bool TEST_PROBABILITYGRID_calcProbabilityGrid() {
    ProbabilityGrid probGrid;

    // Give it some numbers
    probGrid.totalGoodBoards = 10;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            probGrid.shipGrid[x][y] = (2*x + y) % 3;
        }
    }

    // Call the function to calculate probabilities
    calcProbabilityGrid(probGrid);

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            double expectedProb = static_cast<double>(probGrid.shipGrid[x][y]) / static_cast<double>(probGrid.totalGoodBoards);
            double expectedPChange = pow(expectedProb, 2) + pow(1 - expectedProb, 2);

            ASSERT(fabs(probGrid.shipProb[x][y] - expectedProb) < 1e-6, "Probability calculation is incorrect");
            ASSERT(fabs(probGrid.pChange[x][y] - expectedPChange) < 1e-6, "Probability change calculation is incorrect");
        }
    }
    ENDTEST();
}


bool TEST_PROBABILITYGRID_flattenBoardToProbabilityGrid(){
    ASSERT(BOARD_SIZE >= 3, "Board size must be at least three to test this");

    // Horizontal ship at [0][0], [1][0], [2][0]
    // Vertical ship at [1][1], [1][2]
    Board board = initBlankBoard();
    board.board[0][0] = 0;
    board.board[1][0] = 0;
    board.board[2][0] = 0;

    board.board[1][1] = 1;
    board.board[1][2] = 1;
    board.isValid = true;

    ProbabilityGrid probGrid;
    probGrid.shipGrid[0][0] = 3;
    probGrid.shipGrid[0][2] = 6;

    flattenBoardToProbabilityGrid(board, probGrid);

    ASSERT(probGrid.totalGoodBoards == 1, "Adding a board should increase the number of good boards");
    ASSERT(probGrid.shipGrid[0][0] == 4, "Adding a ship should add one to the shipgrid here");
    ASSERT(probGrid.shipGrid[1][0] == 1, "Adding a ship should add one to the shipgrid here");
    ASSERT(probGrid.shipGrid[2][0] == 1, "Adding a ship should add one to the shipgrid here");

    ASSERT(probGrid.shipGrid[1][1] == 1, "Adding a ship should add one to the shipgrid here");
    ASSERT(probGrid.shipGrid[1][2] == 1, "Adding a ship should add one to the shipgrid here");

    ASSERT(probGrid.shipGrid[0][1] == 0, "Empty space without a boat should stay zero");
    ASSERT(probGrid.shipGrid[0][2] == 6, "Empty space with preixisting data shouldn't be changed");
    ASSERT(probGrid.shipGrid[2][1] == 0, "Empty space without a boat should stay zero");
    ASSERT(probGrid.shipGrid[2][2] == 0, "Empty space without a boat should stay zero");


    // Set to invalid and ensure it doesn't add anything
    board.isValid = false;
    ASSERT(probGrid.totalGoodBoards == 1, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[0][0] == 4, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[1][0] == 1, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[2][0] == 1, "Probability Grid shouldn't change when board is invalid");

    ASSERT(probGrid.shipGrid[1][1] == 1, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[1][2] == 1, "Probability Grid shouldn't change when board is invalid");

    ASSERT(probGrid.shipGrid[0][1] == 0, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[0][2] == 6, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[2][1] == 0, "Probability Grid shouldn't change when board is invalid");
    ASSERT(probGrid.shipGrid[2][2] == 0, "Probability Grid shouldn't change when board is invalid");


    ENDTEST();
}

bool TEST_PROBABILITYGRID_clearProbabilityGrid(){
    ProbabilityGrid pG;

    // Fill the probability grid with nonsense data
    pG.totalGoodBoards = 124;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            pG.shipGrid[x][y] = 5*x+y;
            pG.shipProb[x][y] = 0.5*x*x;
            pG.pChange[x][y] = 0.25*y;
            pG.infoGain[x][y] = 0.1;
        }
    }

    clearProbabilityGrid(pG);

    ASSERT(pG.totalGoodBoards == 0, "Probability Grid should be zeroed");
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            ASSERT(pG.shipGrid[x][y] == 0, "Probability Grid should be zeroed");
            ASSERT(pG.shipProb[x][y] == 0.0, "Probability Grid should be zeroed");
            ASSERT(pG.pChange[x][y] == 0.0, "Probability Grid should be zeroed");
            ASSERT(pG.infoGain[x][y] == 0.0, "Probability Grid should be zeroed");
        }
    }

    ENDTEST();
}
