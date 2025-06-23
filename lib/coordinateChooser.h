/**
 * @file
 * @author Talita
 * @brief Various algorithms for picking the next best shot
 * @date 2025-02-06
 */
#ifndef COORDINATECHOOSER_H
#define COORDINATECHOOSER_H

#include <random>
#include <cstring>
#include <map>

#include "battleship_utils.h"
#include "hitmask.h"
#include "probabilityGrid.h"
#include "boardIterator.h"
//TODO make unit tests

/// @brief Selection between the many types of choosing where to shoot
enum CoordinateChooser{
    USER_INPUT, // Asks the user for (x,y)
    RND, // Chooses a position uniformly at random
    RND_W_PROB, // Chooses randomly, weighted by probability of ship
    P_MAX, // Chooses the position with the highest probability of a ship
    P_RND, // Choses the position with the highest probability of a ship, with some randomness added
    INFOGAIN, // Simulates all posible outcomes of each move, and picks the one that on average will reduce number of posible boards the most
    INFOGAIN_COMBINED, // uses the infogain calculation, until nothing is learnt then uses pMax
    DIAGONAL, // Shoots the diagonal (of size of unshot largest ship)
};

/// @brief A segment to be done for an infogain gathering algorithm
struct InfogainTask{
    Hitmask hitmask;
    ProbabilityGrid probGrid;
    int x;
    int y;
};

extern std::map<CoordinateChooser, std::string> coordinateChooserNames;

// -- Coordinate choosing
void coordinate_userInput(int &, int &);
void coordinate_rnd(int &, int &, Hitmask);
void coordinate_rndWProb(int &, int &, ProbabilityGrid, Hitmask); // random, but with probability weighting
void coordinate_pMax(int &, int &, ProbabilityGrid, Hitmask);
void coordinate_pRnd(int &, int &, ProbabilityGrid, Hitmask);
double coordinate_infoGain(int &, int &, ProbabilityGrid &, Hitmask);
double coordinate_infoGain(int &, int &, ProbabilityGrid &, Hitmask, std::vector<Board>);
void coordinate_diagonal(int &, int &, ProbabilityGrid, Hitmask);



#endif //COORDINATECHOOSER_H
