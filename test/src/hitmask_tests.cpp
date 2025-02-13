#include "hitmask_tests.h"

bool TEST_HITMASK_initHitmask() {
    Hitmask h;
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            ASSERT(h.hitmask[x][y] == UNKNOWN, "Hitmask should be initialised to UNKNOWN");
        }
    }

    for (int i = 0; i < FLEET_SIZE; i++){
        ASSERT(h.shipSunk[i] == false, "All ships should be initialised as not sunk");
    }

    ENDTEST();
}

bool TEST_HITMASK_hitBoard() {
    Board b = initBlankBoard();

    ShipPosition shipPos[2] = {
        {3, 0, 0, true}, // Horizontal 3 ship at (0,0) (1,0) (2,0)
        {2, 1, 1, false} // Vertical 2 ship at (1,1) (1,2)
    };

    drawBoard(b, shipPos, 2);

    Hitmask h;
    hitBoard(b, h, 1, 2);
    ASSERT(h.hitmask[1][2] == HIT, "Hitmask should record a hit at the given position");

    ASSERT(h.hitmask[1][1] == UNKNOWN, "Hitmask should only update the given site");
    ASSERT(h.hitmask[0][0] == UNKNOWN, "Hitmask should only update the given site");
    ASSERT(h.hitmask[0][2] == UNKNOWN, "Hitmask should only update the given site");

    ASSERT(h.shipSunk[1] == false, "Ship should not be sunk with a single hit");

    hitBoard(b, h, 1, 1);
    hitBoard(b, h, 1, 2);

    ASSERT(h.hitmask[1][1] == SUNK, "Fully hitting a ship should record it as sunk");
    ASSERT(h.hitmask[1][2] == SUNK, "Fully hitting a ship should record it as sunk");

    ASSERT(h.shipSunk[1] == true, "Ship should be sunk after all segments are hit");
    ASSERT(h.shipSunk[0] == false, "Other ship should not be impacted by hitting the ship");

    ENDTEST();
}

bool TEST_HITMASK_findHitmaskDifference() {
    Hitmask oldHitmask = {};
    Hitmask newHitmask = {};
    int x = 2, y = 3;

    newHitmask.hitmask[x][y] = HIT;

    int xDifference, yDifference;
    findHitmaskDifference(oldHitmask, newHitmask, xDifference, yDifference);

    ASSERT(xDifference == x && yDifference == y, "findHitmaskDifference should find the correct difference");
    // TODO future test for multiple differences and misses/sinks

    ENDTEST();
}

bool TEST_HITMASK_howManyTurnsTaken() {
    Hitmask h = {};
    //TODO some kind of check to see that the hitmask is big enough for the test to be considered valid
    h.hitmask[2][3] = HIT;
    h.hitmask[4][5] = MISS;

    int turns = howManyTurnsTaken(h);

    ASSERT(turns == 2, "howManyTurnsTaken should count the correct number of turns");

    ENDTEST();
}


bool TEST_HITMASK_checkCompatible(){
    Board b = initBlankBoard();

    ShipPosition shipPos[2] = {
        {3, 0, 0, true}, // Horizontal 3 ship at (0,0) (1,0) (2,0)
        {2, 1, 1, false} // Vertical 2 ship at (1,1) (1,2)
    };

    drawBoard(b, shipPos, 2);
    Hitmask h;
    ASSERT(checkCompatible(b, h) == true, "An empty hitmask should always be compatible");

    h.hitmask[0][0] = HIT;
    h.hitmask[1][0] = MISS;
    h.hitmask[1][1] = HIT;

    ASSERT(checkCompatible(b, h) == false, "Marking a ship as missed should make the hitmask incompatible");

    h.hitmask[1][0] = HIT;
    ASSERT(checkCompatible(b, h) == true, "Successfully hitting ships should be compatible");

    h.hitmask[0][1] = HIT;
    ASSERT(checkCompatible(b, h) == false, "Hitting an empty cell should not be compatible");

    h.hitmask[0][1] = MISS;
    ASSERT(checkCompatible(b, h) == true, "Successfully missing ships should be compatible");

    h.hitmask[1][2] = SUNK;
    h.hitmask[1][1] = SUNK;
    h.shipSunk[1] = true;
    ASSERT(checkCompatible(b, h) == true, "Sinking a ship should not change compatability");

    ENDTEST();
}


bool TEST_HITMASK_turnsToShotmask(){

    printf("\tNOT IMPLEMENTED turnsToShotmask\n");
    return false;
}

bool TEST_HITMASK_isHitmaskSolved(){
    Hitmask h;
    ASSERT(isHitmaskSolved(h) == false, "An empty hitmask should not be considered solved");

    for (int i = 0; i < FLEET_SIZE; i++){
        h.shipSunk[i] = false;
    }
    ASSERT(isHitmaskSolved(h) == false, "An unsolved hitmask should not be considered solved");

    h.shipSunk[0] = true;
    ASSERT(isHitmaskSolved(h) == false, "A partially solved hitmask should not be considered solved");

    for (int i = 1; i < FLEET_SIZE; i++){
        h.shipSunk[i] = true;
    }
    ASSERT(isHitmaskSolved(h) == true, "A fully solved hitmask should be considered solved");

    ENDTEST();
}


bool TEST_HITMASK_isHit(){
    Hitmask h;
    h.hitmask[2][3] = HIT;
    h.hitmask[4][1] = MISS;
    h.hitmask[0][1] = SUNK;

    ASSERT(isHit(h, 2, 3) == true, "isHit should return true for a hit cell");
    ASSERT(isHit(h, 4, 1) == true, "isHit should return true for a missed cell");
    ASSERT(isHit(h, 0, 1) == true, "isHit should return true for a sunk cell");
    ASSERT(isHit(h, 0, 0) == false, "isHit should return false for an unknown cell");

    ENDTEST();
}


bool TEST_HITMASK_operatorEqual(){
    Hitmask h1;
    Hitmask h2;

    ASSERT(h1 == h2, "Empty hitmasks should be equal");

    h1.hitmask[2][3] = HIT;
    ASSERT(h1 != h2, "Hitmasks should not be equal if they have different hits");

    h2.hitmask[2][3] = HIT;
    ASSERT(h1 == h2, "Hitmasks should be equal if they have the same hits");

    h1.hitmask[0][0] = MISS;
    ASSERT(h1 != h2, "Hitmasks should not be equal if they have different misses");

    h2.hitmask[0][0] = MISS;
    ASSERT(h1 == h2, "Hitmasks should be equal if they have the same misses");

    h1.hitmask[0][0] = SUNK;
    ASSERT(h1 != h2, "Hitmasks should not be equal if they have different status in the same cell");

    h1.hitmask[0][0] = MISS;
    ASSERT(h1 == h2, "Hitmasks should be equal if they have the same sunk ships");

    h1.shipSunk[1] = true;
    ASSERT(h1 != h2, "Hitmasks should not be equal if they don't have the same sunk ships");

    h2.shipSunk[1] = true;
    ASSERT(h1 == h2, "Hitmasks should be equal if they have the same sunk ships");

    ENDTEST();
}
