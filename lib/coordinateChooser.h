#ifndef COORDINATECHOOSER_H
#define COORDINATECHOOSER_H

#include <random>
#include <cstring>
#include <map>

#include "hitmask.h"
#include "probabilityGrid.h"
#include "boardIterator.h"
//TODO make unit tests

/// @brief Selection between the many types of choosing where to shoot
enum CoordinateChooser{
    USER_INPUT,
    RND,
    RND_W_PROB,
    P_MAX,
    P_RND,
    INFOGAIN,
    DIAGONAL,
    FLEXI
};

extern std::map<CoordinateChooser, std::string> coordinateChooserNames;

// -- Coordinate choosing
void coordinate_userInput(int &, int &);
void coordinate_rnd(int &, int &, Hitmask);
void coordinate_rndWProb(int &, int &, ProbabilityGrid, Hitmask); // random, but with probability weighting
void coordinate_pMax(int &, int &, ProbabilityGrid, Hitmask);
void coordinate_pRnd(int &, int &, ProbabilityGrid, Hitmask);
double coordinate_infoGain(int &, int &, ProbabilityGrid &, Hitmask);
void coordinate_diagonal(int &, int &, ProbabilityGrid, Hitmask);



#endif //COORDINATECHOOSER_H
