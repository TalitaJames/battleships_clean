/**
 * @file
 * @author Talita
 * @brief Iteration methods for calculating probability grid
 * Everything needed for the traditional approach to 'brute force' a
 * probability grid by using multiple workers to iterate through all boards
 *
 * @date 2025-02-06
 */

#ifndef BOARDITERATOR_H
#define BOARDITERATOR_H

#include <chrono>
#include <vector>
#include <thread>

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
void checkBoards(Worker &, Hitmask, int);
void iterateBoardsToGenerateProbabilityGrid(Hitmask, ProbabilityGrid &, unsigned int);

void gatherProbabilityFromWorkers(ProbabilityGrid &, std::vector<Worker>);
void appendWorkerToProbGrid(ProbabilityGrid &, Worker);

// -- Iterating, storing boards in memory
void checkThenUpdateVectorOfBoards(std::vector<Board>&, ProbabilityGrid&);
void checkThenUpdateVectorOfBoards(std::vector<Board>&, ProbabilityGrid&, Hitmask);
void checkThenUpdateVectorOfBoards(std::vector<Board>&, ProbabilityGrid&, Hitmask, bool);

std::ostream& operator<<(std::ostream&, Worker&);
std::ostream& operator<<(std::ostream&, std::vector<Worker>&);

#endif //BOARDITERATOR_H
