#include "symmetries.h"

/**
 * @brief rotate the board 90 degrees clockwise
 *
 * @param board board to transform
 */
void rotateBoard90(Board &board){
    // for each boat, find the bottom leftmost point
    ShipPosition rotatedPositions[FLEET_SIZE];

    for (size_t i = 0; i < FLEET_SIZE; i++){
        ShipBoundingBox boundingBox = convertShipPositionToBoundingBox(board.shipPos[i]);

        rotatedPositions[i].length = board.shipPos[i].length;
        rotatedPositions[i].y = boundingBox.west;
        rotatedPositions[i].x = BOARD_SIZE - 1 - boundingBox.south;
        rotatedPositions[i].direction = !board.shipPos[i].direction; //flip direction
    }
    drawBoard(board, rotatedPositions); //update with new values
}

/**
 * @brief rotate the board 180 degrees clockwise
 *
 * @param board board to transform
 */
void rotateBoard180(Board &board){
    rotateBoard90(board);
    rotateBoard90(board);
}

/**
 * @brief rotate the board 270 degrees clockwise
 *
 * @param board board to transform
 */
void rotateBoard270(Board &board){
    rotateBoard90(board);
    rotateBoard90(board);
    rotateBoard90(board);
}

/**
 * @brief reflect the board through the x axis
 *
 * @param board board to transform
 */
void flipBoardX(Board &board){
    ShipPosition flippedPositions[FLEET_SIZE];

    for (size_t i = 0; i < FLEET_SIZE; i++){
        flippedPositions[i].length = board.shipPos[i].length;
        flippedPositions[i].y = board.shipPos[i].y;
        flippedPositions[i].direction = board.shipPos[i].direction;

        flippedPositions[i].x = BOARD_SIZE - board.shipPos[i].x
            - (board.shipPos[i].direction ? board.shipPos[i].length : 1);
    }

    drawBoard(board, flippedPositions); //update with new values
}

/**
 * @brief reflect the board through the Y axis
 *
 * @param board board to transform
 */
void flipBoardY(Board &board){
    ShipPosition flippedPositions[FLEET_SIZE];

    for (size_t i = 0; i < FLEET_SIZE; i++){
        flippedPositions[i].length = board.shipPos[i].length;
        flippedPositions[i].x = board.shipPos[i].x;
        flippedPositions[i].direction = board.shipPos[i].direction;

        flippedPositions[i].y = BOARD_SIZE - board.shipPos[i].y
            - (!board.shipPos[i].direction ? board.shipPos[i].length : 1);
    }

    drawBoard(board, flippedPositions); //update with new values
}

/**
 * @brief reflect the board through the X then Y axis
 *
 * @param board board to transform
 */
void flipBoardXY(Board &board){
    flipBoardX(board);
    flipBoardY(board);
}

/**
 * @brief reflect the board through the Y then X axis
 *
 * @param board board to transform
 */
void flipBoardYX(Board &board){
    flipBoardY(board);
    flipBoardX(board);
}


/**
 * @brief apply a given symmetry to the passed board
 *
 * @param board board to transform
 * @param sym the specified symetry to aply
 */
void applySymmetry(Board &board, Symmetry sym){
    switch (sym){
        case IDENTITY:
            break;
        case ROTATE_90:
            rotateBoard90(board);
            break;
        case ROTATE_180:
            rotateBoard180(board);
            break;
        case ROTATE_270:
            rotateBoard270(board);
            break;
        case FLIP_X:
            flipBoardX(board);
            break;
        case FLIP_Y:
            flipBoardY(board);
            break;
        case FLIP_XY:
            flipBoardXY(board);
            break;
        case FLIP_YX:
            flipBoardYX(board);
            break;
    }
}