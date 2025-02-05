#include "board.h"
// #include "ships.h"


/**
 * @brief Create a new blank board
 * @return Board
 */
Board initBlankBoard(void){
    Board b;
    wipeBoard(b);
    return b;
}

/**
 * @brief convert an existing board to empty
 * @param b an exisiting reference to a board
 */
void wipeBoard(Board &b){
    memset(b.board, BOARD_DEFAULT, sizeof(b.board));

    b.isEmpty=true;
    b.isValid=false;

    //FIXME this isn't the most efficient, and they technically have values (of "default")
    ShipPosition zeroPosition = {0,0,0,false};
    for (size_t i = 0; i < FLEET_SIZE; i++) {
        b.shipPos[i] = zeroPosition;
    }

}

/**
 * @brief Draws a list of ship positions onto a board
 * @param board the referenced board
 * @param shipPos a pointer to an array of ship Positions
*/
void drawBoard(Board &board, ShipPosition* shipPos){
    wipeBoard(board);
    board.isEmpty = false;

    // Draw the grid
    for (size_t i = 0; i < FLEET_SIZE; i++){ // for each ship
        for (size_t j = 0; j < shipPos[i].length; j++){ // for the length of each ship
            // early return if a ship already there or if it is out of bounds
            if (shipPos[i].direction){
                if (shipPos[i].x+j>= BOARD_SIZE ||shipPos[i].y>= BOARD_SIZE) { // out of horizonal bounds
                    board.isValid=false;
                    return;
                }
                else if (board.board[shipPos[i].x+j][shipPos[i].y] != BOARD_DEFAULT) { // intersection!
                    board.isValid=false;
                    return;
                }
                board.board[shipPos[i].x+j][shipPos[i].y] = i; // update board value
            }
            else{
                if (shipPos[i].x>= BOARD_SIZE ||shipPos[i].y+j>= BOARD_SIZE) { // out of vertical bounds
                    board.isValid=false;
                    return;
                }
                else if (board.board[shipPos[i].x][shipPos[i].y+j] != BOARD_DEFAULT) { // intersection!
                    board.isValid=false;
                    return;
                }
                board.board[shipPos[i].x][shipPos[i].y+j] = i; // update board value
            }
        }
    }

    // Update the ship positions
    for (size_t i = 0; i < FLEET_SIZE; i++){
        board.shipPos[i] = shipPos[i];
    }

    board.isValid = true;
}

/**
 * @brief Generates a random board
 * @return board a (pseudo) random and guaranteed valid board
*/
Board rndBoard(){
    Board b = initBlankBoard();

    ShipPosition boardPositions[FLEET_SIZE];

    while (!b.isValid){
        for (size_t i = 0; i < FLEET_SIZE; i++){
            boardPositions[i] = rndShipPos(BOARD_SIZE, FLEET[i]);
        }

        drawBoard(b, boardPositions);
    }

    return b;
};


std::ostream& operator<<(std::ostream& os, Board& b){
    os << "Board {" << BOARD_SIZE << ", " << BOARD_SIZE << "}";
    os << "\tempty:"<<b.isEmpty<<" valid: "<<b.isValid<<"\n";
    for (int y = 0; y < BOARD_SIZE; y++){
        os << "[";
        for (int x = 0; x < BOARD_SIZE; x++){
            if (b.board[x][y] == BOARD_DEFAULT) os << " , ";
            else os << b.board[x][y] << ", ";
        }
        os << "]\n";
    }
  return os;
};