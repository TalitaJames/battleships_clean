#ifndef PROBABILITYGRID_H
#define PROBABILITYGRID_H

#include <stdbool.h>
#include <iostream>
#include <stdio.h>
#include "board.h"

/// @brief Holds various probabilities to the board locations
struct ProbabilityGrid{
    unsigned long totalGoodBoards = 0;
    unsigned long shipGrid[BOARD_SIZE][BOARD_SIZE] {0}; // number of valid ships in a given cell
    double shipProb[BOARD_SIZE][BOARD_SIZE] {0}; // shipGrid/totalGoodBoards (known as probability of a ship, p)
    double pChange[BOARD_SIZE][BOARD_SIZE] {0}; // p^2+(1-p)^2 (formerly infoGain)
    double infoGain[BOARD_SIZE][BOARD_SIZE] {0}; // Calcualated only when `coordinate_infoGain()` is called. the "Real" info gain
};

void calcProbabilityGrid(ProbabilityGrid &);
std::ostream& operator<<(std::ostream&, ProbabilityGrid&);



#endif //PROBABILITYGRID_H