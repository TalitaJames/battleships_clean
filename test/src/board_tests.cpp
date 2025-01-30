#include "board_tests.h"

void TEST_BOARD_initBlankBoard() {
    Board b = initBlankBoard();

    ASSERT(b.isEmpty == true, "Board should be empty after initialization");
    ASSERT(b.isValid == false, "Board should be invalid after initialization");
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            ASSERT(b.board[x][y] == BOARD_DEFAULT, "Board cells should be set to BOARD_DEFAULT");
        }
    }

    ASSERT(b.dimensions.height == BOARD_SIZE, "Board height should be set to BOARD_SIZE");
    ASSERT(b.dimensions.width == BOARD_SIZE, "Board width should be set to BOARD_SIZE");

    printf("\tPASSED initBlankBoard\n");
}

void TEST_BOARD_wipeBoard() {
    Board b;
    b.board[0][0] = 1; // Set a cell to non-default value
    wipeBoard(b);
    ASSERT(b.isEmpty == true, "Board should be empty after wiping");
    ASSERT(b.isValid == false, "Board should be invalid after wiping");
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            ASSERT(b.board[x][y] == BOARD_DEFAULT, "Board cells should be set to BOARD_DEFAULT");
        }
    }
    ASSERT(b.dimensions.height == BOARD_SIZE, "Board height should be set to BOARD_SIZE");
    ASSERT(b.dimensions.width == BOARD_SIZE, "Board width should be set to BOARD_SIZE");
    printf("\tPASSED wipeBoard\n");
}

void TEST_BOARD_drawBoard() {
    Board b = initBlankBoard();
    ASSERT(b.dimensions.height >= 3, "Board height should be at least 3 to test properly");
    ASSERT(b.dimensions.width >= 3, "Board width should be at least 3 to test properly");

    ShipPosition shipPos[2] = {
        {3, 0, 0, true}, // Horizontal ship at (0,0)
        {2, 1, 1, false} // Vertical ship at (1,1)
    };
    drawBoard(b, shipPos);

    ASSERT(b.isEmpty == false, "Board should not be empty after drawing ships");
    ASSERT(b.board[0][0] == 0, "Ship 0 should be at (0,0)");
    ASSERT(b.board[1][0] == 0, "Ship 0 should be at (1,0)");
    ASSERT(b.board[2][0] == 0, "Ship 0 should be at (2,0)");

    ASSERT(b.board[1][1] == 1, "Ship 1 should be at (1,1)");
    ASSERT(b.board[1][2] == 1, "Ship 1 should be at (1,2)");

    ASSERT(b.board[0][1] == BOARD_DEFAULT, "Empty space should be BOARD_DEFAULT");
    ASSERT(b.board[0][2] == BOARD_DEFAULT, "Empty space should be BOARD_DEFAULT");
    ASSERT(b.board[2][1] == BOARD_DEFAULT, "Empty space should be BOARD_DEFAULT");
    ASSERT(b.board[2][2] == BOARD_DEFAULT, "Empty space should be BOARD_DEFAULT");

    printf("\tPASSED drawBoard\n");
}

void TEST_BOARD_rndBoard() {
    Board b = rndBoard();
    ASSERT(b.isEmpty == false, "Random board should not be empty");
    ASSERT(b.isValid == true, "Random board should be valid");

    // TODO add test to ensure random board is actually random
    printf("\tPASSED rndBoard\n");
}
