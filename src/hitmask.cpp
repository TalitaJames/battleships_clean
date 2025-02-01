#include "hitmask.h"



/**
 * @brief Updates the hitmask with a hit at x&y given a board
 * @param b board with the positions clearly shown
 * @param h hitmask reference to record the shot
 * @param x coordinate for shot
 * @param y cordinate for shot
 */
void hitBoard(Board b, Hitmask &h, int x, int y){
    int cell = b.board[x][y]; // check what is at (x,y) at board
    h.hitmask[x][y] = (cell != BOARD_DEFAULT) ? HIT : MISS; //update the hitmask accordingly (hit/miss)

    // Check if the ship is sunk
    if (h.hitmask[x][y] == HIT){ // if it was a hit
        bool isSunk = true;
        // make an array of ship positions from the board

        int checkX = 0;
        int checkY = 0;
        // for all cells in the ship ship most recently hit

        for (size_t i = 0; i < b.shipPos[cell].length; i++) {
            if (b.shipPos[cell].direction) {
                checkX = b.shipPos[cell].x + i;
                checkY = b.shipPos[cell].y;
            }
            else{
                checkX = b.shipPos[cell].x;
                checkY = b.shipPos[cell].y + i;
            }

            // if the cell isn't recorded as hit or sunk, then the whole boat hasn't been explored yet, so stop checking the rest of the boats
            if (!(h.hitmask[checkX][checkY] == cellStatus::HIT || h.hitmask[checkX][checkY] == cellStatus::SUNK)){
                isSunk = false;
                break;
            }
        }

        // update the hitmask if sunk
        if (isSunk) {
            h.shipSunk[cell] = true; // the ship itself has been sunk
            // for the length of the ship just hit
            for (size_t i = 0; i < b.shipPos[cell].length; i++) {
                // get the location of the next ship segment
                if (b.shipPos[cell].direction) {
                    checkX = b.shipPos[cell].x + i;
                    checkY = b.shipPos[cell].y;
                }
                else{
                    checkX = b.shipPos[cell].x;
                    checkY = b.shipPos[cell].y + i;
                }

                // update that segment to be sunk
                h.hitmask[checkX][checkY] = cellStatus::SUNK;
            }
        }
    }
};

/**
 * @brief Finds the first (left topmost) difference between two hitmasks
 * @param oldHitmask the hitmask before the new shot
 * @param newHitmask the hitmask after the new shot
 * @param xy coordinates returning the position of the new shot
 */
void findHitmaskDifference(Hitmask oldHitmask, Hitmask newHitmask, int &xCoord, int &yCoord){
    for(int x=0; x<BOARD_SIZE; x++){
        for(int y = 0; y<BOARD_SIZE; y++){
            if(oldHitmask.hitmask[x][y] != newHitmask.hitmask[x][y] ){
                xCoord=x;
                yCoord=y;
                return;
            }
        }
    }
};

/**
 * @brief counts the number of turns (non "UNKNOWN" status cells)
 * @param hitmask the board with shot records
 * @return int number of turns taken
 */
int howManyTurnsTaken(Hitmask hitmask){
    int turns = 0;
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (hitmask.hitmask[x][y] != cellStatus::UNKNOWN){
                turns++;
            }
        }
    }
    return turns;
}


/**
 * @brief Checks if a hitmask (h) is compatible with a board (b)
 * @param b board
 * @param h hitmask
 * @return bool true if compatable, else false
 */
bool checkCompatible(Board b,Hitmask h){
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (h.hitmask[x][y] != UNKNOWN){ // if the spot isn't unknown (ie a miss, hit ect)
                if (h.hitmask[x][y]==MISS && b.board[x][y]!=BOARD_DEFAULT) return false; // if hitmask is a miss, and board isn't
                else if (h.hitmask[x][y]==HIT && b.board[x][y]==BOARD_DEFAULT)  return false; // is board empty and hitmask isn't
                else if ((h.hitmask[x][y]==SUNK && (!h.shipSunk[b.board[x][y]]))) return false; // if the ship is sunk, and the boat it claims to be isn't sunk
            }
        }
    }
    return true;
};

/**
 * @brief Convert a hitmask of "Turn" shots into one with an accurate outcome given a board
 * @param b the board to reveal
 * @param turnRecord a hitmask that only has "TURN" rather than the outcome (HIT/MISS/SINK)
 * @return hitmask with history of relevent board
 */
Hitmask turnsToShotmask(Board b, Hitmask turnRecord){
    Hitmask outcomeHitmask; //hitmask with actual outcomes from the turn record board on them
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if(turnRecord.hitmask[x][y] == cellStatus::TURN){
                hitBoard(b,outcomeHitmask,x,y);
            }
        }
    }
    return outcomeHitmask;
};

/**
 * @brief Checks if a hitmask has finished the game (sunk all ships)
 * @param h a hitmask with shots
 * @return bool true if the hitmask has sunk all ships, else false
 */
bool isHitmaskSolved(Hitmask h){
    for (size_t i = 0; i < FLEET_SIZE; i++) {
        //if a ship hasn't been sunk, not solved
        if(!h.shipSunk[i]) return false;
    }
    return true;
};

/**
 * @brief Checks if coordinate (x,y) has been hit
 * @param h a hitmask with shots
 * @param x coordinate for shot
 * @param y cordinate for shot
 * @return bool true if hit, else false
 */
bool isHit(Hitmask h, int x, int y){
    return h.hitmask[x][y] != UNKNOWN;
};

/**
 * @brief Checks if two hitmasks match
 * @param A first hitmask
 * @param B second hitmask
 * @return bool true if equal
 */
bool operator==(const struct Hitmask &A,  const struct Hitmask &B){

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            // std::cout << "(" << x <<","<< y << ") match " << (A.hitmask[x][y] == B.hitmask[x][y]) << std::endl;
            if (A.hitmask[x][y] != B.hitmask[x][y]) return false; // if they don't equal in the grid, not same
        }
    }

    for (int i = 0; i < FLEET_SIZE; i++){
        // std::cout << "(" << i << ") match " << (A.shipSunk[i] == B.shipSunk[i]) << std::endl;
        if (A.shipSunk[i] != B.shipSunk[i]) return false; // one ship is sunk and other isn't, then not equal
    }

    return true;
};

/**
 * @brief Checks if two hitmasks are different
 * @param A first hitmask
 * @param B second hitmask
 * @return bool true if not equal
 */
bool operator!=(const struct Hitmask &A,  const struct Hitmask &B){
    return !(A == B);
};

/**
 * @brief toString for hitmask
 * @param os Output stream
 * @param h hitmask to be displayed
 */
std::ostream& operator<<(std::ostream& os, Hitmask& h){
    os << "--- hitmask ---\nBoats: ";
    for (size_t i = 0; i < FLEET_SIZE; i++) os << h.shipSunk[i] << ", ";
    os << "\n";

    for (int y = 0; y < BOARD_SIZE; y++){
        os << "[";
        for (int x = 0; x < BOARD_SIZE; x++){
            char rep = 'E'; // E for error, initialised value
            switch (h.hitmask[x][y]){
                case UNKNOWN:
                    rep = ' '; //'?';
                    break;
                case MISS:
                    rep='O';
                    break;
                case HIT:
                    rep='X';
                    break;
                case SUNK:
                    rep='S';
                    break;
                case TURN:
                    rep='?';
                    break;
            }
            os <<rep << ", ";
        }
        os << "]\n";
    }
    os << std::flush;

    return os;
};
