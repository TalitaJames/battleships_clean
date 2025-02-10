#include "probabilityGrid.h"

std::ostream& operator<<(std::ostream& os, ProbabilityGrid& p){
    os << "--- total:" << p.totalGoodBoards << " ---\n";

    for (int y = 0; y < BOARD_SIZE; y++){
        os << "[";
        for (int x = 0; x < BOARD_SIZE; x++){
        os << p.shipGrid[x][y] << ", ";
        }
        os << "]\n";
    }
    return os;
};

/**
 * @brief Calculates the probabilities in a partially complete ProbabilityGrid
 *
 * This function iterates over each cell in the grid and calculates the probability
 * of a ship being present in that cell based on the number of good boards. It also
 * calculates the probability change (firmally info gain) using the formula p^2 + (1-p)^2,
 * where x is the probability of a ship being present in that cell.
 *
 * @param p Reference to a ProbabilityGrid object, is assumed the ship grid, and
 *          total number of good boards, are correct information
 */
void calcProbabilityGrid(ProbabilityGrid &p){
    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
        p.shipProb[x][y] = static_cast<double>(p.shipGrid[x][y])/static_cast<double>(p.totalGoodBoards);
        p.pChange[x][y] = pow(p.shipProb[x][y],2)+pow(1-p.shipProb[x][y],2); // x^2+(1-x)^2 (where x=shipProb as above)
        }
    }
};


/**
 * @brief Given a board, if there is a ship in each cell, update the corresponding probability data
 * @param b a board to gather data from
 * @param p reference to a probability grid
*/
void flattenBoardToProbabilityGrid(Board b, ProbabilityGrid &pG){ //TODO add test
    if (!b.isValid) return;

    pG.totalGoodBoards++;

    for (int y = 0; y < BOARD_SIZE; y++){
        for (int x = 0; x < BOARD_SIZE; x++){
            if (b.board[x][y] != BOARD_DEFAULT) pG.shipGrid[x][y]++;
        }
    }

    // TODO possibly fewer checks if we only add from the ship positions?
    // for(int i = 0; i < FLEET_SIZE; i++){
    //     b.shipPos[i];
    //     for (size_t i = 0; i < b.shipPos[i].length; i++){
    //         int xPosition = b.shipPos[i].x;
    //         int yPosition = b.shipPos[i].y;

    //         // Offset the ship by i values (to get each cell)
    //         if(b.shipPos[i].direction){
    //             xPosition += i;
    //         }
    //         else {
    //             yPosition += i;
    //         }

    //         pG.shipGrid[xPosition][yPosition]++;
    //     }
    // }
};