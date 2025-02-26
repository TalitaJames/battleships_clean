/**
 * @file
 * @author Talita
 * @brief Generating, counting and applying symmetries to boards
 * @date 2025-02-24
 */
#ifndef SYMMETRIES_H
#define SYMMETRIES_H

#include "board.h"

enum Symmetry {
    IDENTITY,
    ROTATE_90, // All rotations are clockwise
    ROTATE_180,
    ROTATE_270,
    FLIP_X,
    FLIP_Y,
    FLIP_XY,
    FLIP_YX,
};

/* TODO some symetries aren't "real"
*   ie "same shape" of a board, where the ships are in different positions
*   ie "same board" where the output is identical, except ships of the same
*    length are in switched positions
*
*/


// Function to generate a given symmetry of a board
void rotateBoard90(Board &board);
void rotateBoard180(Board &board);
void rotateBoard270(Board &board);
void flipBoardX(Board &board);
void flipBoardY(Board &board);
void flipBoardXY(Board &board);
void flipBoardYX(Board &board);

void applySymmetry(Board &board, Symmetry sym);





std::vector<Board> generateSymmetries(Board board);




#endif //SYMMETRIES_H
