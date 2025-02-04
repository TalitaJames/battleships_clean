#ifndef BOARDITERATOR_H
#define BOARDITERATOR_H

// #include <algorithm>
// #include <iostream>
// #include <fstream>
// #include <limits>
#include <chrono>
// #include <string>
#include <vector>
#include <thread>
// #include <mutex>

#include "hitmask.h"
#include "probabilityGrid.h"
#include "ships.h"
#include "constants.h"


/// @brief A worker holds the start and end ship positions arrays (a chunk of potential boards) and a probability grid to give data about the chunk of boards
struct Worker{
    ShipPosition start[FLEET_SIZE] = {0, 0, 0, 0};
    ShipPosition end[FLEET_SIZE] = {0, 0, 0, 0};

    ProbabilityGrid sub_probGrid;
};

// -- Thread and bulk bits
void dividePositions(int, std::vector<Worker>&);
void flattenBoardToProbabilityGrid(Board b, ProbabilityGrid &pG);
void checkBoards(Worker &, Hitmask, int);
void iterateBoardsToGenerateProbabilityGrid(Hitmask, ProbabilityGrid &, unsigned int);

void gatherProbabilityFromWorkers(ProbabilityGrid &, std::vector<Worker>);
void appendWorkerToProbGrid(ProbabilityGrid &, Worker);

std::ostream& operator<<(std::ostream&, Worker&);
std::ostream& operator<<(std::ostream&, std::vector<Worker>&);

#endif //BOARDITERATOR_H
